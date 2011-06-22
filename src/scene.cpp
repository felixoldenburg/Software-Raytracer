#include "scene.h"

Scene::Scene(std::list<Object*> &objects)
	: up(Vector3D(0,1,0)), octree(new Octree(objects))
{
	//octree = new Octree(objects);
}

Scene::~Scene()
{
	delete octree;
}

void Scene::start()
{
	if (octree == NULL)
		return;
	
	Ray r;
	r.point = eye;
	
	for(int x = 0; x < xres; ++x)
		for(int y = 0; y < yres; ++y)
		{
			r.dir = eye.vectorTo(
				Vector3D( s + u*((VTYPE)((x+.5f)/xres)) + v * .5f)
			);;
		}
}
