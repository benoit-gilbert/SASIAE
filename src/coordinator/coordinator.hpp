//#include "physical_calculator.hpp"
#include "../modules/module.hpp"
#include "../physical_calculator/physical_calculator.hpp"
#include "../modules/modules.hpp"
#include "../physical_calculator/robot.hpp"
//#include "../gui/mainwindow.h"

#include <QtCore/QThread>
#include <QtCore/QProcess>
#include <QtCore/QHash>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QPair>
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>

//#include <cstring>
//#include <iostream>


#include "../gui/mainwindow.h"
#include <QApplication>


#define COORD_BUFFER_SIZE 1024


class Coordinator:public QApplication{
  Q_OBJECT
  
  signals:
  //! \brief Send user message to UI and log file
  void GUISend(QString message);
  void calcNextStep(double, int); 
  void log(QString); 
  //! \brief time for UI sync in ms
  void timer(unsigned long int);

  void modulesNextStep(void);

public:
  enum Slot{MAIN_ROBOT1,SECOND_ROBOT1,MAIN_ROBOT2,SECOND_ROBOT2};
  ~Coordinator();
  /* Hugo : I don't know if this function must be static or not */
  // used in test3dCoordinator
  PhysicalCalculator& getPhysicalCalculatorInstance();


public slots:

  //! \brief coordinator is unique, so we need to get is instance (and create one if it doesn't existe)
  static Coordinator& getInstance(int argc, char* argv[]);

  //! \brief coordinator is unique, so we need to get is instance (and create one if it doesn't existe)
  static Coordinator& getInstance();

  //! \brief start the simulation
  void play();
  //! \brief pause the simulation
  void pause();

  //! \brief Trigger by Calculator, when a step is finished
  void stepDone();
  void openTable(const QString& XMLPath);
  void openRobot(const QString& XMLPath);
  //void openRobot(QProcess * proc, const QString& XMLPath, Slot slot);
  
						  
						   

private slots:
  //! \brief read the message received from the Client Thread
  void CTReceived();
  //! \brief read the message received from the Modules
  /*
    message appearence : one QString without headers. 
    BE AWARE ! 
    This methode HAS to be called from the signal send(QString)
    otherwise sender()==NULL;
  */
  //void MReceived(QString);

  void sendModuleMessage(QString msg);

  void update(void);


//private:
protected:
  QMap<QString /*robot_name*/, Robot* /*robotObject*/> _robotObject;
  QHash<QString/*robot_name*/, QString /*robot_code_name*/> _robotInfo;
  /* The _moduleInfo's key must be ROBOTCODENAMEmodulename */
  QHash<QString/*module_name*/, Modules* /*modules*/> _moduleFromName;
  QHash<QString/*robot_code_name*/, QProcess* /*robot_process*/> _codeInfo;
  QHash<QObject* /* modules*/, 
	QPair<QString/*robot_code_name*/, QString /*module_name*/> > 
  _moduleInfo;

private slots:
  void gotoNextStep(); 
private:
  void sendDeviceMessage(QString name, QString msg, QProcess* p);
  void sendDeviceMessage(QString name, QString msg, QString code);
  void sendMessages(QString msg, QProcess* p);
  
public:
  //! \brief send sync message to all Robot Code Process
  void sendSyncMessages();
  

  void startUpdateTimer(QTimer *);

private:
  void closeRobot(Slot robot);
  void closeRobot(QProcess *robot);
  //! \brief read one line of process output
  /*
   * The line must be a message : 
   * for example : "D TESTER I'm new \n"
   */
  QString readMessage(QProcess * proc)const;

  /*
   * add to _codeInfo a pair
   * (key : codeName, value : processus)
   */
  bool addToRobotCode(QString name, QProcess * proc);

  /*
   * add to _moduleFromName a Pair
   * (key: module's name, value : module)
   */
  bool addModule(QString name, Modules * mod);  

  /*
   * add to _moduleInfo a pair
   * (key : module, value : pair(codeName, moduleName))
   */
  bool addModuleAndCodeName(Modules * key, QString code, QString module );
   

private:
  Coordinator(int argc, char* argv[]);
  static Coordinator* _instance;
  PhysicalCalculator _physic;

  bool _running;
  int _sync; 
  int _codeFactor;
  double _timeStep;
  int _maxSubStep;

};


