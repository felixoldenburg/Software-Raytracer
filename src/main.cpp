#include <QtGui/QApplication>
#include "mainwindow.h"

#include "vector3d.h"
#include "triangle.h"
#include "rect.h"
#include "sphere.h"
#include "octree.h"
#include "object.h"
#include "cube.h"
#include "color.h"

#include <ctime>
#include <list>
#include <iostream>
#include <string.h>

#include <QString>

#include <QDebug>

using std::list;
using std::cout;

void printCube(const Cube &cube)
{
    qDebug() << "cube: " << cube[0] << cube[1] << cube[2] << cube[3] << "\n"
            << cube[4] << cube[5] << cube[6] << cube[7];
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr( QTextCodec::codecForName("UTF-8") );
	
	/*Sphere sp(Vector3D(-20, 10, 0), 4);
	Ray r = { Vector3D(-28, 7, 0), Vector3D(1, 1, 0) };
	Vector3D result;
	qDebug() << sp.intersectsRay(r, &result);
	qDebug() << result;
	return 0;*/
	
	/*Color c(1, 0.4f, 0.5f);
	Color c2(1, 0.4f, 0.5f);
	
	c = Color(6, 7, 8);
	c2[0] *= c[0] * 4.5f;
	VTYPE test = c2[0];
	qDebug() << "tesettt: " << test;
	
	return 0;*/
	
	/* Vector3D cube[8];
    cube[0] = Vector3D(0, 1, 1);
    cube[1] = Vector3D(1, 1, 1);
    cube[2] = Vector3D(1, 0, 1);
    cube[3] = Vector3D(0, 0, 1); //
    cube[4] = Vector3D(0, 1, 0);
    cube[5] = Vector3D(1, 1, 0);
    cube[6] = Vector3D(1, 0, 0);
    cube[7] = Vector3D(0, 0, 0);
	Cube c(cube);
	Ray r;
	r.point = Vector3D(-1, 0.3f, 0.5f);
	r.dir = Vector3D(1, 0.4f, -0.1f);
	Vector3D res;
	qDebug() << "inter: " << c.intersectsRay(r, &res);
	
	return 0;*/
	
	/*
	Octree* octree = new Octree();
	
	list<Object*> objs;
	
	Triangle* t = new Triangle(Vector3D(0,0,-10), Vector3D(0,10,-10), Vector3D(10,0,-10));
	Rect *r = new Rect(Vector3D(0,0,10), Vector3D(0,10,10), Vector3D(10,10,10), Vector3D(10,0,0));
	Sphere *s = new Sphere(Vector3D(-20, 10, 0), 4);
	
	qDebug() << "-------------------";
	
	objs.push_back(t); objs.push_back(r); objs.push_back(s);
	
	octree->startBSP(&objs);
	
	qDebug() << octree->getBoundingBox().toString().c_str();
	
	delete octree;
	return 0;*/
/*
    Vector3D cube[8];
    cube[0] = Vector3D(0, 1, 1);
    cube[1] = Vector3D(1, 1, 1);
    cube[2] = Vector3D(1, 0, 1);
    cube[3] = Vector3D(0, 0, 1); //
    cube[4] = Vector3D(0, 1, 0);
    cube[5] = Vector3D(1, 1, 0);
    cube[6] = Vector3D(1, 0, 0);
    cube[7] = Vector3D(0, 0, 0);
    //printCube(cube);
    qDebug() << "--";
	
	list<Object*> objs;
	
	Triangle t(Vector3D(0,0,-1), Vector3D(0,1,-1), Vector3D(1,0,-1));

    Octree occi(cube);
	
	occi.addObject(&t);
    printCube(occi.getBoundingBox());
    

    //qDebug() << Triang

    return 0;*/
/*
    Vector3D p,u, x;
    p = Vector3D(0,0,0);
    u = Vector3D(5,0,0);
    x = Vector3D(2.5f,0.0000001f,0);

    qDebug() << "Point on Line: " << V3D::isPointOnLine(p, u, x);

    return 0;
    Rect rei;
    Vector3D cub[8];
    qDebug() << "addi von 2: " << cub+2;
    rei.intersectCube(cub);

    return 0;

VTYPE lal = 0;
    Vector3D vec(1, 0, 0);
    Vector3D veb(12.23, 53.12332, -23.23132);

    clock_t start = clock();

    for (int i = 0; i < 99999999; ++i)
    {
        vec = Vector3D(i, i, i);
        vec *= (1/vec.length());

        lal = vec * veb;
    }

    qDebug() << lal;
    //qDebug() << vec << lol[0] << lol[1] << lol[2];

    clock_t end = clock();
    int time_elapsed = end - start;
    qDebug() << "time: " << start << end << ":" << time_elapsed;
    return 0;

    Vector3D v0(0, 0, 0);

    Vector3D v2(0, 0, 1);
    Vector3D v3(0, 0, 1);

    Sphere s(v0, 1);
    Ray r;
    r.point = Vector3D(15,0,15);
    r.dir = Vector3D(-15, 0, -15);

    Vector3D res;
    qDebug() << s.intersect(r, &res);
    qDebug() << res;
    Triangle t1(t0);
    Triangle t2;
    Triangle t(v1, v2, v3);

    qDebug() << t0;
    qDebug() << t1;
    qDebug() << t2;
    qDebug() << t;

    //qDebug() << (v1 == v3);
    //qDebug() << v1.vectorTo(v2).length();
//    qDebug() << v1;
*/
qDebug("testi0");
    MainWindow w;
    w.show();
	qDebug("testi1");
    return a.exec();
}
