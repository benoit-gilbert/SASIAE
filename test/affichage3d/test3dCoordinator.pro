######################################################################
# Automatically generated by qmake (2.01a) sam. févr. 1 14:49:00 2014
######################################################################

TEMPLATE = app
TARGET = vue3d
DEPENDPATH += .
INCLUDEPATH += . /usr/include/bullet /usr/local/include/bullet /usr/local/lib ../../src/coordinator/  ../../../aversive--/include/sasiae ../../src/physical_calculator/
CONFIG += debug
QT += widgets

QMAKE_CXXFLAGS = -std=c++0x
LIBS += -lBulletDynamics -lBulletCollision -lLinearMath -lglut -lGLU 

# Input
HEADERS +=../../src/physical_calculator/wheel.hpp \
 ../../src/physical_calculator/robot.hpp \
 ../../src/physical_calculator/physical_calculator.hpp \
../../src/coordinator/coordinator.hpp \
 ../../src/modules/servo.hpp \
 ../../src/modules/modules.hpp \
 ../../src/modules/encoder.hpp \
 ../../src/modules/motor_wheel.hpp \
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
 test3dCoordinator.hpp \
 
SOURCES += ../../src/physical_calculator/wheel.cpp \
 ../../src/physical_calculator/robot.cpp \
 ../../src/physical_calculator/physical_calculator.cpp \
 ../../src/coordinator/coordinator.cpp \
 ../../src/modules/modules.cpp \
 ../../src/modules/servo.cpp \
 ../../src/modules/encoder.cpp \
 ../../src/modules/motor_wheel.cpp \
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
 test3dCoordinator.cpp \

