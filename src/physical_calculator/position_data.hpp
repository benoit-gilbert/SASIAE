#ifndef POSITION_DATA_HPP
#define POSITION_DATA_HPP

#include <btBulletDynamicsCommon.h>
#include <QString>
#include <QVector>
#include <QQuaternion>
// #include Mesh
//used as a list in the gui coordinateur to be printed on Qt

class PositionData
{
public:
    PositionData();
    void setPosition(const btVector3 &);
    void setRotation(btQuaternion);
    QVector<float> & getQtPosition(void);
    QQuaternion & getQtRotation(void);
private:
    QVector<float> _QPosition;
    QQuaternion _QRotation;
    btVector3 _btPosition;
    btQuaternion _btRotation;
};

#endif // POSITION_DATA_HPP