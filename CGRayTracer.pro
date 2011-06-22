##########################################
# codelite's qmake configuration: default
# codelite's qmake exec line    : qmake
##########################################
DESTDIR        = ./
TEMPLATE       = app
CONFIG         = release qt lex yacc uic resources warn_on precompile_header
MAKEFILE       = ./CGRayTracer.mk
OBJECTS_DIR    = ./Debug
TARGET         = ./Debug/CGRayTracer
INCLUDEPATH    = .
QMAKE_CFLAGS_RELEASE   = -g
QMAKE_CXXFLAGS_RELEASE = -g
DEFINES                = 
QMAKE_LFLAGS_RELEASE   = 
LIBS           = 
LIBS           += 
LIBS           += 
SOURCES     = \
             ./src/cube.cpp\
             ./src/object.cpp\
             ./src/rect.cpp\
             ./src/sphere.cpp\
             ./src/triangle.cpp\
             ./src/octree.cpp\
             ./src/vector3d.cpp\
             ./src/vectormath.cpp\
             ./src/scene.cpp\
             ./src/raytracer.cpp\
             ./src/main.cpp\
             ./src/mainwindow.cpp\
             ./src/oglwidget.cpp\
             ./src/picturebox.cpp\

HEADERS     = \
             ./src/cube.h\
             ./src/object.h\
             ./src/rect.h\
             ./src/sphere.h\
             ./src/triangle.h\
             ./src/octree.h\
             ./src/vector3d.h\
             ./src/vectormath.h\
             ./src/scene.h\
             ./src/raytracer.h\
             ./src/lightsource.h\
             ./src/mainwindow.h\
             ./src/oglwidget.h\
             ./src/picturebox.h\

FORMS       = \

YACCSOURCES = \

LEXSOURCES  = \

RESOURCES   = \

##########################################
# User section
##########################################

QT += opengl debug
MOC_DIR = ./Debug/moc
CONFIG -= console
SUBDIRS += Debug Debug/moc
