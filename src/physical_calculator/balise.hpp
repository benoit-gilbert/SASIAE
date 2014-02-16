#ifndef __BALISE_H__
#define __BALISE_H__

#include "modules.hpp"
#include "../physical_calculator/robot.hpp"
#include "../physical_calculator/physical_calculator.hpp"

#include <QObject>
#include <QString>
#include <QStandardItem>
#include <btBulletDynamicsCommon.h>


class Balise : public Modules {
	Q_OBJECT

public:
	Balise(btRigidBody* chassis, QObject* parent, PhysicalCalculator* calculator);
	btVector3 get_position();


	public slots:
	virtual QStandardItem* getData();
	virtual void received(QString message);
	virtual void simulStep();


	signals:
	virtual void send(QString message);


private:
	btVector3 _position;
  btRigidBody* _chassis
	btRigidBody* _sensor_box;
	QStandardItem* _dataRoot;
  btDynamicsWorld* _world;
};


#endif