##########################################
# codelite's qmake configuration: default
# codelite's qmake exec line    : qmake
##########################################
DESTDIR        = /Users/FOldenburg/dev/CGRayTracer/
TEMPLATE       = app
CONFIG         = release qt lex yacc uic resources warn_on precompile_header
MAKEFILE       = /Users/FOldenburg/dev/CGRayTracer/CGRayTracer.mk
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
             /Users/FOldenburg/dev/CGRayTracer/src/cube.cpp\
             /Users/FOldenburg/dev/CGRayTracer/src/object.cpp\
             /Users/FOldenburg/dev/CGRayTracer/src/rect.cpp\
             /Users/FOldenburg/dev/CGRayTracer/src/sphere.cpp\
             /Users/FOldenburg/dev/CGRayTracer/src/triangle.cpp\
             /Users/FOldenburg/dev/CGRayTracer/src/octree.cpp\
             /Users/FOldenburg/dev/CGRayTracer/src/vector3d.cpp\
             /Users/FOldenburg/dev/CGRayTracer/src/vectormath.cpp\
             /Users/FOldenburg/dev/CGRayTracer/src/scene.cpp\
             /Users/FOldenburg/dev/CGRayTracer/src/raytracer.cpp\
             /Users/FOldenburg/dev/CGRayTracer/src/main.cpp\
             /Users/FOldenburg/dev/CGRayTracer/src/mainwindow.cpp\
             /Users/FOldenburg/dev/CGRayTracer/src/oglwidget.cpp\
             /Users/FOldenburg/dev/CGRayTracer/src/picturebox.cpp\

HEADERS     = \
             /Users/FOldenburg/dev/CGRayTracer/src/cube.h\
             /Users/FOldenburg/dev/CGRayTracer/src/object.h\
             /Users/FOldenburg/dev/CGRayTracer/src/rect.h\
             /Users/FOldenburg/dev/CGRayTracer/src/sphere.h\
             /Users/FOldenburg/dev/CGRayTracer/src/triangle.h\
             /Users/FOldenburg/dev/CGRayTracer/src/octree.h\
             /Users/FOldenburg/dev/CGRayTracer/src/vector3d.h\
             /Users/FOldenburg/dev/CGRayTracer/src/vectormath.h\
             /Users/FOldenburg/dev/CGRayTracer/src/scene.h\
             /Users/FOldenburg/dev/CGRayTracer/src/raytracer.h\
             /Users/FOldenburg/dev/CGRayTracer/src/lightsource.h\
             /Users/FOldenburg/dev/CGRayTracer/src/mainwindow.h\
             /Users/FOldenburg/dev/CGRayTracer/src/oglwidget.h\
             /Users/FOldenburg/dev/CGRayTracer/src/picturebox.h\

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
