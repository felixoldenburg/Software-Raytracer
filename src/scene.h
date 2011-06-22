#ifndef SCENE_H
#define SCENE_H

#include "vector3d.h"
#include "octree.h"
#include "lightsource.h"
#include <list>

class Scene {

public:
	Scene(std::list<Object*> &objects);
	virtual ~Scene();
	
	void start();
	
	Vector3D getEye() const;
	void setEye(const Vector3D &eye);
	
	Vector3D getS() const;
	void setS(const Vector3D &s);
	
	Vector3D getU() const;
	void setU(const Vector3D &u);
	
	Vector3D getV() const;
	void setV(const Vector3D &v);
	
	Vector3D getUpVector() const;
	void setUpVector(const Vector3D &up);
	
	int getXRes() const;
	void setXRes(unsigned int xres);
	
	int getYRes() const;
	void setYRes(unsigned int yres);
	
	Octree* getOctree();
	//void setOctree(Octree *octree);
	
	std::list<Lightsource*>* getLights();
	void setLights(const std::list<Lightsource*> &lights);
	
protected:
	/// Betrachterposition
	Vector3D eye;
	/// Linker, unterer Punkt der Projektionsflaeche
	Vector3D s;
	/// Spannen die Projektionsflaeche auf
	Vector3D u, v;
	/// Definert die 'oben'
	Vector3D up;
	
	/// Horizontale Aufloesung der Projektionsflaeche
	int xres;
	/// Vertikale Aufloesung der Projektionsflaeche
	int yres;
	
	Octree* octree;
	
	std::list<Lightsource*> lights;
};

/**
 * Get Methode fuer Augpunkt.
 * @return Augpunkt
 */
inline Vector3D Scene::getEye() const
{
	return eye;
}

inline void Scene::setEye(const Vector3D &eye)
{
	this->eye = eye;
}

/**
 * Get Methode fuer linken, unteren Punkt der
 * Projektionsflaeche
 * @return unterer, linkerer Punkt der Projektionsflaeche
 */
inline Vector3D Scene::getS() const
{
	return s;
}

inline void Scene::setS(const Vector3D &s)
{
	this->s = s;
}

/**
 * Get Methode fuer horizontal aufspannenden Vektor
 * zur Definition der Projektionsflaeche
 * @return u Vektor der Projektionsflaeche
 */
inline Vector3D Scene::getU() const
{
	return u;
}

inline void Scene::setU(const Vector3D &u)
{
	this->u = u;
}

/**
 * Get Methode fuer vertikal aufspannenden Vektor
 * zur Definition der Projektionsflaeche
 * @return v Vektor der Projektionsflaeche
 */
inline Vector3D Scene::getV() const
{
	return v;
}

inline void Scene::setV(const Vector3D &v)
{
	this->v = v;
}

/**
 * Get Methode fuer den nach oben zeigenden Vektor
 * @return Up-Vektor
 */
inline Vector3D Scene::getUpVector() const
{
	return up;
}

inline void Scene::setUpVector(const Vector3D &up)
{
	this->up = up;
}

/**
 * Get Methode fuer horizontale Aufloesung
 * @return horizontale Aufloesung
 */
inline int Scene::getXRes() const
{
	return xres;
}

inline void Scene::setXRes(unsigned int xres)
{
	this->xres = xres;
}

/**
 * Get Methode fuer vertikale Aufloesung
 * @return vertikale Aufloesung
 */
inline int Scene::getYRes() const
{
	return yres;
}

inline void Scene::setYRes(unsigned int yres)
{
	this->yres = yres;
}

/**
 * Get Methode fuer Octree
 * @return Octree der Szene
 */
inline Octree* Scene::getOctree()
{
	return octree;
}

/*inline void Scene::setOctree(Octree *octree)
{
	this->octree = octree;
}*/

/**
 * Get Methode fuer Lightquellen
 * @return Lichtquellen der Szene
 */
inline std::list<Lightsource*>* Scene::getLights()
{
	return &lights;
}

inline void Scene::setLights(const std::list<Lightsource*> &lights)
{
	std::list<Lightsource*>::const_iterator it;
	for(it = lights.begin(); it != lights.end(); ++it)
		this->lights.push_back(*it);
}

#endif // SCENE_H
