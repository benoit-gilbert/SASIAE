#include "wheel.hpp"
#include "../../src/modules/encoder.hpp"
#include "../../src/modules/motor_wheel.hpp"
#include "../../src/modules/servo.hpp"
#include "../../src/modules/RDS.hpp"
#include "../../src/modules/balise.hpp"
#include "../../src/physical_calculator/physical_calculator.hpp"
#include <iostream>




#include <QtTest/QtTest>
#include <QObject>

class TestModules : public QObject
{
  Q_OBJECT
  private slots:
    //void modules();
    void encoder_param();
    void encoder_param_data();
    void encoder_rotation_data();
    void encoder_rotation();
    void motor_wheel_param_data();
    void motor_wheel_param();
    void motor_wheel_step_data();
    void motor_wheel_step();
    void servo();
    void balise();

};

void TestModules::encoder_param_data() {
  QTest::addColumn<QString>("param");
  QTest::addColumn<double>("rotation");
  QTest::addColumn<QString>("result");

  QTest::newRow("same as default") << "<accuracy>1024</accuracy>" << 1.<< "value 1024";
  QTest::newRow("more than default") << "<accuracy>10000</accuracy>"<< 1.  << "value 10000";
  QTest::newRow("less than default") << "<accuracy>666</accuracy>"<< 1. << "value 666";
}


void TestModules::encoder_param() {
  QFETCH(QString, param);
  QFETCH(double, rotation);
  QFETCH(QString, result);
  Wheel w;
  w._rotation = rotation;
  Encoder e(&w, param, this);
  //testing send emission
  QSignalSpy spy(&e, SIGNAL(send(QString)));
  //testing accuracy
  e.simulStep();
  QCOMPARE(spy.count(), 1); //signal was emitted exactly one time
  QList<QVariant> arguments = spy.takeFirst(); // take the first signal
//<<<<<<< HEAD
  QVERIFY2(arguments.at(0).toString() == result, qPrintable(arguments.at(0).toString()));
}

void TestModules::encoder_rotation_data() {
  QTest::addColumn<QString>("param");
  QTest::addColumn<double>("rotation");
  QTest::addColumn<QString>("result");

  QTest::newRow("default") << "<accuracy>1024</accuracy>" << 0. << "value 0";
  QTest::newRow("1 turn") << "<accuracy>1024</accuracy>" << 1. << "value 1024";
  QTest::newRow("fraction") << "<accuracy>1024</accuracy>" << 0.5  << "value 512";
  QTest::newRow("more than 1") << "<accuracy>1024</accuracy>" << 2. << "value 2048";
  QTest::newRow("truncated") << "<accuracy>1024</accuracy>" << 2.2 << "value 2252";
  QTest::newRow("negative") << "<accuracy>1024</accuracy>" << -2. << "value -2048";
}

void TestModules::encoder_rotation() {
  QFETCH(QString, param);
  QFETCH(double, rotation);
  QFETCH(QString, result);
  Wheel w;
  w._rotation = rotation;
  Encoder e(&w, param, this);
  //testing send emission
  QSignalSpy spy(&e, SIGNAL(send(QString)));
  //testing accuracy
  e.simulStep();
  QCOMPARE(spy.count(), 1); //signal was emitted exactly one time
  QList<QVariant> arguments = spy.takeFirst(); // take the first signal
  QVERIFY2(arguments.at(0).toString() == result, qPrintable(arguments.at(0).toString()));
}

void TestModules::motor_wheel_step_data() {
  QTest::addColumn<QString>("param");
  QTest::addColumn<QString>("command");
  QTest::addColumn<double>("result");
  QTest::newRow("default") << "<params><gear>1</gear><torque>1000</torque></params>" << "value 1.0" << 1000*1.;
  QTest::newRow("diviseur") << "<params><gear>1</gear><torque>1000</torque></params>" << "value 0.1" << 1000*0.1;
  QTest::newRow("not diviseur, need truncate") << "<params><gear>1</gear><torque>1000</torque></params>" << "value 0.3" << 1000*0.3;
  QTest::newRow("zero") << "<params><gear>1</gear><torque>1000</torque></params>" << "value 0" << 0.;
  //QTest::newRow("more than 1") << "<params><gear>1</gear><torque>1000</torque></params>" << "value 1.1" << 1000*1;
}

void TestModules::motor_wheel_step() {
  QFETCH(QString, param);
  QFETCH(QString, command);
  QFETCH(double, result);
Wheel w;
  MotorWheel m(&w, param, this);
  QVERIFY(m.parent() == this);
  //testing received
  m.received(command);
  m.simulStep();
  QVERIFY2(w._torque == result, qPrintable(QString("%1").arg(w._torque)));
}
void TestModules::motor_wheel_param_data() {
  QTest::addColumn<QString>("param");
  QTest::addColumn<QString>("command");
  QTest::addColumn<double>("result");
  QTest::newRow("default") << "<params><gear>1</gear><torque>1000</torque></params>" << "value 1.0" << 1000*1.;
  QTest::newRow("more torque") << "<params><gear>1</gear><torque>2000</torque></params>" << "value 1.0" << 2000*1.;
  QTest::newRow("gear ratio") << "<params><gear>0.1</gear><torque>1000</torque></params>" << "value 1.0" << 1000*0.1;
  //QTest::newRow("more than 1") << "<params><gear>1</gear><torque>1000</torque></params>" << "value 1.1" << 1000*1;
}
void TestModules::motor_wheel_param() {
  QFETCH(QString, param);
  QFETCH(QString, command);
  QFETCH(double, result);
  Wheel w;
  MotorWheel m(&w, param, this);
  m.received(command);
  m.simulStep();
  QVERIFY2(w._torque == result, qPrintable(QString("%1").arg(w._torque)));
}

void TestModules::servo() {
  Servo *test = new Servo(5,this);
  QStandardItem *info = test->getData();
  QVERIFY2(info!=NULL, qPrintable(QString("faux...")));
}

void TestModules::balise() {
  PhysicalCalculator * ph_cal=new PhysicalCalculator();
  btDiscreteDynamicsWorld * myscene=ph_cal->getScene();


//crée un robot :
  //chassis du  1er robot
      //les coordonnées sont pour un quart de la boite
  btCollisionShape* boxShape = new btBoxShape(btVector3(2,0.5,2));
  btDefaultMotionState* boxMotionState =
  new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0.7,0)));
  btScalar mass = 8;
  btVector3 boxInertial(0,0,0);
  boxShape->calculateLocalInertia(mass, boxInertial);
  btRigidBody::btRigidBodyConstructionInfo boxBodyCI(mass, boxMotionState, boxShape, boxInertial);
  btRigidBody* chassis = new btRigidBody(boxBodyCI);
  myscene->addRigidBody(chassis);
  //fin chassis
  Robot* robot = new Robot(chassis, myscene);
  myscene->addVehicle(robot);

// Création d'une balise.
  Balise *balise_robot = new Balise(robot, this, ph_cal);


  //Création de la RDS :
  RDS *detection = new RDS();
  detection->balise_add(balise_robot);

//test de le balise
  list<btVector3>* positions_detected = detection->get_other_position(NULL);
  for(auto it=positions_detected->begin(); it!=positions_detected->end(); ++it ) {
    std::cout << (*it).getX()
              << (*it).getY()
              << (*it).getZ()
              << std::endl;
  }
}


QTEST_MAIN(TestModules)
#include "test_modules.moc"
