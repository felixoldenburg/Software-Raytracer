#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "scene.h"
#include "color.h"

class RayTracer {

public:
	RayTracer(Scene *scene);
	virtual ~RayTracer();
	
	Scene* getScene() { return scene; }
	Color** getPixel();

	void start();
	
protected:
	Scene *scene;
	Color **pixel;
	
	Object* traverse(const Octree *o, const Ray &ray, Vector3D *result);
	Color raycast(const Vector3D &from, const Vector3D &to);

};

#endif // RAYTRACER_H
