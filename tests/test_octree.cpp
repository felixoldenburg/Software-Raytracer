#include <UnitTest++.h>#include "../src/octree.h"#include "../src/triangle.h"#include "../src/rect.h"#include "../src/sphere.h"#include <list>#include <iostream>using std::cout;using std::list;void pv(const Vector3D &v){	cout << "v: " << v.x() << ", " << v.y() << ", " << v.z() << std::endl;}SUITE(Octree){	TEST(Initialization)	{		list<Object*> l;		Octree o(l);		Vector3D empty;		// Keine Objekte		CHECK(o.getObjects()->empty());		// Keine Bounding Box		const Cube *box = o.getBoundingBox();		for (int i = 0; i < 8; ++i)			CHECK((*box)[i] == empty);		// Keine Kindknoten		const Octree*const* children = o.getChildren();		for (int i = 0; i < 8; ++i)			CHECK(children[i] == NULL);	}	TEST(TestScene1)	{
		list<Object*> objs;

		Triangle* t = new Triangle(Vector3D(0,0,-10), Vector3D(0,4,-10), Vector3D(10,0,-10));
		Rect *r = new Rect(Vector3D(0,0,10), Vector3D(0,10,10), Vector3D(10,10,10), Vector3D(10,0,0));
		Sphere *s = new Sphere(Vector3D(-20, 10, 0), 4);
		Sphere *s2 = new Sphere(Vector3D(-12, 5, 6), 0.91f);
		Sphere *s3 = new Sphere(Vector3D(-10, 5, 6), 0.91f);
		
		objs.push_back(t);
		objs.push_back(r);
		objs.push_back(s);
		objs.push_back(s2);
		objs.push_back(s3);		Octree o(objs);		// Bounding Box pruefen		const Cube *box = o.getBoundingBox();		Vector3D vert[8] = {			Vector3D(-24,14,10), Vector3D(10,14,10),			Vector3D(10,0,10), Vector3D(-24,0,10),			Vector3D(-24,14,-10), Vector3D(10,14,-10),			Vector3D(10,0,-10), Vector3D(-24,0,-10)		};		Cube cubeRef(vert);		CHECK(cubeRef == *box);		const list<Object*> *objects = o.getObjects();		const Octree*const* children = o.getChildren();		if (objects->size() == 2)		{			CHECK(objects->front()->isRect());			CHECK(objects->back()->isSphere());			for (int i = 0; i < 8; ++i)				if (i != 3 && i != 6)				{					CHECK(children[i]->isLeave());					CHECK(children[i]->getObjects()->empty());				}			if (children[6]->getObjects()->size() == 1)				CHECK(children[6]->getObjects()->front()->isTriangle());			else				CHECK(false);			const Octree *oc = children[3];			children = oc->getChildren();			for (int i = 0; i < 8; ++i)				if (i != 1)				{					CHECK(children[i]->isLeave());					CHECK(children[i]->getObjects()->empty());				}						objects = children[1]->getObjects();			if (objects->size() == 2)			{				CHECK(objects->front()->isSphere());				CHECK(objects->back()->isSphere());			}			else				CHECK(false); // size != 2		}		else			CHECK(false); // size != 2	}}