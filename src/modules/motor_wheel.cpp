#include "motor_wheel.hpp"
#include <QObject>
#include <QString>
#include <QStringList>
#include <QXmlStreamReader>
#include <QDebug>

const QString MotorWheel::xmlGearName = "gear";
const QString MotorWheel::xmlTorqueName = "torque";

MotorWheel::MotorWheel(Wheel* wheel, QString params, QObject* parent)
 : Module(parent), _wheel(wheel) {
  //default params :
  _motorMaxTorque = 1000;
  _gearRatio = 1;
  _inputRatio = 0;
  //read from params :
  QXmlStreamReader xml(params);
  while(!xml.atEnd())
  {
    xml.readNext();
    if(xml.name() == xmlGearName) {
      xml.readNext();
       _gearRatio = xml.text().toString().toDouble();
      xml.readNext();
    }
    else if(xml.name() == xmlTorqueName) {
      xml.readNext();
      _motorMaxTorque = xml.text().toString().toDouble();
      xml.readNext();
    }
  }
  //build data tree for UI
  _dataRoot = new QStandardItem("Motor Wheel");
  _dataRoot->appendRow(QList<QStandardItem*>() << new QStandardItem("Max torque") << new QStandardItem(QString()+ _motorMaxTorque));
  _dataRoot->appendRow(QList<QStandardItem*>() << new QStandardItem("Gear ratio") << new QStandardItem(QString()+ _wheel->getRotation()));
  _dataRoot->appendRow(QList<QStandardItem*>() << new QStandardItem("Command ratio") << new QStandardItem(QString("0")));
  _dataRoot->appendRow(QList<QStandardItem*>() << new QStandardItem("Real torque") << new QStandardItem(QString("0")));
}

QStandardItem* MotorWheel::getGuiItem() {
  return _dataRoot;
}

void MotorWheel::received(QString message) {
  QStringList list = message.split(" ");
  if(list.at(0) == "value") {
    _inputRatio = list.at(1).toDouble();
    qDebug() << "Motor's value !!! ==> " << _inputRatio << endl;
  }
}
void MotorWheel::update(void) {
  _wheel->setTorque(_motorMaxTorque*_gearRatio*_inputRatio / 127.0);
}
