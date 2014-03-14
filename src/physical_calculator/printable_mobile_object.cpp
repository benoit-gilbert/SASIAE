#include "printable_mobile_object.hpp"

QVector<PrintableMobileObject*> PrintableMobileObject::objects;

PrintableMobileObject::PrintableMobileObject(QString name, btRigidBody *body) :
    _name(name) /*_pos(new struct position_data)*/,_body(body)
{
    _pos=new PositionData();
    objects.append(this);
}

PrintableMobileObject::PrintableMobileObject(btRigidBody *body):
    _name("unknown") /*_pos(new struct position_data)*/,_body(body)
{
    _pos=new PositionData();
    objects.append(this);
}



PositionData *PrintableMobileObject::getPosition() {
  	btTransform trans;
  	_body->getMotionState()->getWorldTransform(trans);
    _pos->setPosition(trans.getOrigin());
    _pos->setRotation(trans.getRotation());
return _pos;
}
/*
struct position_data * PrintableMobileObject::getPosition() {
	btTransform trans;
	_body->getMotionState()->getWorldTransform(trans);
	btVector3 position =trans.getOrigin();
	_pos->positionTest.replace(0,position.getX());
	_pos->positionTest.replace(1,position.getY());
	_pos->positionTest.replace(2,position.getZ());
	_pos->angle=trans.getRotation();
	return _pos;
}
*/
