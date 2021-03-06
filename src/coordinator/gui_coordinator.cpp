#include "gui_coordinator.hpp"
#include <QtCore/QDebug>

#include "../physical_calculator/physical_calculator.hpp"
#include "../physical_calculator/printable_mobile_object.hpp"

#include "coordinator.hpp"


GuiCoordinator::GuiCoordinator(void){
  qDebug() << "GuiCoordinator constructor";
  _mainWindow=new MainWindow();

    // MainWindow -> GuiCoordinator : load the Table

    connect(
           _mainWindow,
           SIGNAL(robotFileStl(const QString&,const QString&)),
            this,
            SLOT(forwardRobotNameStl(const QString&,const QString&))
           );

/*
   //to be tested when the connect above is solved.
connect(
       _mainWindow, //how do i link this ?
       SIGNAL(updateTable()),
       this,
       SLOT(updateTable())
       );
*/
}

MainWindow* GuiCoordinator::getMainWindow(void)const{
  return _mainWindow;
}

GuiCoordinator::~GuiCoordinator(void){
}

void GuiCoordinator::forwardRobotNameStl(const QString&name , const QString&path){
    emit forwardRobotFileStl(name, path);
}

void GuiCoordinator::updateTable(){
    foreach(const PrintableMobileObject* it,PrintableMobileObject::getObjectsList()){
        if(it->getItem()->scene()==NULL){
            _mainWindow->getScene()->addItem(it->getItem());
        }
    }
}

void GuiCoordinator::update(){

/*
 * Hugo : ancient version...
        const QVector<const PrintableMobileObject*>& objectsList = PrintableMobileObject::getObjectsList();
        if(!objectsList.isEmpty()){
           qDebug() << "GC update  objectList" << objectsList ;
           const PositionData * posRot=objectsList.first()->getPosition();
           QVector<float> pos=posRot->getQtPosition();
           qDebug() << "GuiCoordinator update pos.x=" << pos.at(0) << "pos.y =" << pos.at(2) ;
           _mainWindow->animateRobot(pos.at(0),pos.at(2));
           }
        else{
            qDebug() << "GuiCoordinator objectList is empty";
           }
*/

           const QVector<const PrintableMobileObject*>& objectsList = PrintableMobileObject::getObjectsList();
           if(!objectsList.isEmpty()){
            qDebug() << "GC update  objectList" << objectsList ;
            foreach (const PrintableMobileObject* it, objectsList) {
              it->update();
        //qDebug() << "GuiCoordinator update pos.x=" << curPosition.at(0) << "pos.y =" << curPosition.at(2) ;
        //mainWindow->animateRobot(curPosition.at(0),curPosition.at(2));
            }
          }
          else{
           qDebug() << "GuiCoordinator objectList is empty";
           }

       }

/*       void GuiCoordinator::forwardTbleFStl(QString file){
        emit forwardTableFileStl(file);
      }
*/
//QVector<const PositionData*>* GuiCoordinator::getAllPositions() const {

//    const QVector<const PrintableMobileObject*>& objectsList = PrintableMobileObject::getObjectsList();
//    QVector<float> & curPosition;
//    for (auto it = objectsList.cbegin(); it < objectsList.cend(); ++it)
//    {
//        curPosition = ((*it)->getPosition())->getQtPosition();
//        _mainWindow->animateRobot(curPosition->at(0),curPosition->at(2));
//        //not tested yet because of compiling problems !!
//    }
//    return result;
//    //TO COPY THAT INTO THE GUI TO SHOW POSITIONS ON THE LIST !!
//}


