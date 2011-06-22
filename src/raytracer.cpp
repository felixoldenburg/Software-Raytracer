#include "raytracer.h"

#include <list>

using std::list;

RayTracer::RayTracer(Scene *scene) : scene(scene)
{
	int x = scene->getXRes();
	int y = scene->getYRes();
	
	pixel = new Color*[y];
	
	for(int i = 0; i < y; ++i)
		*(pixel+i) = new Color[x];
}

RayTracer::~RayTracer()
{
	// 2D Array loeschen
	int y = scene->getYRes();
	for(int i = 0; i < y; ++i)
		delete[] pixel[i];
	delete [] pixel;
	
	delete scene;
}

Object* RayTracer::traverse(const Octree * o, const Ray &ray, Vector3D *result)
{
	Vector3D res;
	Object *target = NULL;
	float distance = MAX_VALUE;
	// Schnittpunkt des Strahls mit einem Objekt
	// Wird atm nicht verwendet 
	Vector3D cubeP;
	
	// Schneidet der Strahl diesen Knoten
	if (o->getBoundingBox()->intersectsRay(ray, &cubeP))
	{
		// Hat dieser Knoten Objekte?
		const list<Object*> *objects = o->getObjects();
		if (!objects->empty())
		{
			// Schnittpunktberechnung mit jedem der Objekte
			list<Object*>::const_iterator it;
			for(it = objects->begin(); it != objects->end(); ++it)
				if((*it)->intersectsRay(ray, &res))
				{
					float d = ray.point.distanceTo(res);
					// Speichere nahestes Objekt
					if (IS_SMALLER(d, distance))
					{
						distance = d;
						*result = res;
						target = *it;
					}
				}
		}
		
		
		const Octree* const *children = o->getChildren();
		// Rekursiv im Octree absteigen
		for (int i = 0; i < 8; ++i)
		{			
			if (children[i] != NULL)
			{
				Object *trgt = traverse(children[i], ray, &res);
				if (trgt != NULL)
				{
					float d = ray.point.distanceTo(res);
					if (IS_SMALLER(d, distance))
					{
						distance = d;
						*result = res;
						target = trgt;
					}
				}
			}
		}
			
		// Ein Schnittpunkt mit einem Objekt wurde gefunden
		return target;
	}
	else // Strahl schneidet diesen Knoten nicht
		return NULL;
		
}

Color** RayTracer::getPixel()
{
	return pixel;
}

/*Color phong(const Vector3D &l, const Vector3D &n)
{
	Color c;
	
	//VTYPE diff = n * l * 
	
	return c;
}*/
#include <qDebug>
Color RayTracer::raycast(const Vector3D &from, const Vector3D &to)
{
	Color cio(0,0,0);
	
	Octree* o = scene->getOctree();
	Ray ray = {from, from.vectorTo(to)};
	Vector3D result;

	Object *prim = traverse(o, ray, &result);
	
	// Objekt getroffen?
	if (prim != NULL)
	{
		// Grundfarbe des Objekts
		cio = Color(0, 0, 1);
		
		// Fuer jede Lichtquelle
		std::list<Lightsource*>::const_iterator it;
		std::list<Lightsource*>* lights = scene->getLights();
		for(it = lights->begin(); it != lights->end(); ++it)
		{
			Ray shadowRay = {result, result.vectorTo((*it)->pos())};
			Vector3D dummy;
			// Ist die Lichtquelle vom Schnittpunkt aus sichtbar?
			if (traverse(o, shadowRay, &dummy) == NULL)
			{
				Vector3D n = prim->getNormal(result);
				VTYPE ortho = n * shadowRay.dir;
				if (IS_GREATER_ZERO(ortho))
				{
					VTYPE diff = ortho * .1f; // 100% diffus
					Color cl = (*it)->color();
				
					cio[0] = (cio[0]+cl[0])/2.0f; cio[0] *= diff ; //* cl[0];
					cio[1] = (cio[1]+cl[1])/2.0f; cio[1] *= diff ;//* cl[1];
					cio[2] = (cio[2]+cl[2])/2.0f; cio[2] *= diff ; //* cl[2];
				//qDebug() << cio[0] << cio[1] << cio[2];
				}
				else
					cio = Color(0, 0, 0);
			}
		
		}
			
		//c = Color(1, 0, 0);
	}
	else
		cio = Color(0, 0, 0);
		
	
		
	// for every lightSource
		// c += raycast(<Schattenstrahl>)
	// c += raycast(<Reflektierter Strahl>)
	// c += raycast(<Transmittierter Strahl>)
	
	return cio;
}

void RayTracer::start()
{
	// Projektionsparameter
	Vector3D s 	= scene->getS();
	Vector3D u 	= scene->getU();
	Vector3D v 	= scene->getV();
	Vector3D eye = scene->getEye();
	int xres = scene->getXRes();
	int yres = scene->getYRes();

	// Fuer jeden Pixel
	for(int x = 0; x < xres; ++x)
		for(int y = 0; y < yres; ++y)
		{
			// Schnittpunkt von Strahl mit Projektionsflaeche
			Vector3D intersection = s + u*((x+.5f)/xres) + v * ((y+.5f)/yres);
			
			//qDebug() << "y: " << y << "x: " << x;
			pixel[y][x] = raycast(eye, intersection);
			//r.dir = eye.vectorTo(tp	);
			
		}
}
