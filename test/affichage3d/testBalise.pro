TEMPLATE = app
TARGET = vue3d
DEPENDPATH += .
INCLUDEPATH += . /usr/include/bullet /usr/local/include/bullet /usr/local/lib ../../src/physical_calculator/  ../../../aversive--/include/sasiae 


QMAKE_CXXFLAGS = -std=c++0x
LIBS += -lBulletDynamics -lBulletCollision -lLinearMath -lglut -lGLU 

# Input
HEADERS +=../../src/physical_calculator/wheel.hpp \
 ../../src/physical_calculator/robot.hpp \
 ../../src/physical_calculator/balise.hpp \
 ../../src/physical_calculator/physical_calculator.hpp \
 ../../src/physical_calculator/dist_sensor.hpp \
 ../../src/modules/modules.hpp \
 ../../src/modules/RDS.hpp \
 CommandLineArguments.h \
 DebugCastResult.h \ 
 DemoApplication.h \ 
 GLDebugDrawer.h \ 
 GLDebugFont.h \ 
 GL_DialogDynamicsWorld.h \
 GL_DialogWindow.h \
 GL_ShapeDrawer.h \
 GL_Simplex1to4.h \
 GlutDemoApplication.h \
 GlutStuff.h \
 RenderTexture.h \
 stb_image.h \
 Win32DemoApplication.h \
 testBalise.hpp \
 
SOURCES += ../../src/physical_calculator/wheel.cpp \
 ../../src/physical_calculator/robot.cpp \
 ../../src/physical_calculator/balise.cpp \
 ../../src/physical_calculator/physical_calculator.cpp \
 ../../src/physical_calculator/dist_sensor.cpp \
 ../../src/modules/modules.cpp \
 ../../src/modules/RDS.cpp \
 main.cpp \ 
 DemoApplication.cpp \
 GLDebugDrawer.cpp \
 GLDebugFont.cpp \
 GL_DialogDynamicsWorld.cpp \
 GL_DialogWindow.cpp \
 GL_ShapeDrawer.cpp \
 GL_Simplex1to4.cpp \
 GlutDemoApplication.cpp \
 GlutStuff.cpp \
 RenderTexture.cpp \
 stb_image.cpp \
 Win32AppMain.cpp \
 Win32DemoApplication.cpp \
 testBalise.cpp \
