#ifndef OCTREE_H
#define OCTREE_H

#include <list>
#include <cstring>
#ifdef QT_CORE_LIB
#include <QDebug>
#endif

#include "vector3d.h"
#include "object.h"

class Octree
{
private:
	Octree(const Cube &box);
public:
    Octree(std::list<Object*> &objects);
	
	~Octree();

    const Cube*					getBoundingBox() const;
	const std::list<Object*>* 	getObjects() const;
	const Octree* const*		getChildren() const;

    bool isLeave() const;

	void startBSP(std::list<Object*> &objects);
	
	std::string toString(int depth = 0) const;
std::list<Object*> backupList;
private:
    /// Der Bounding Box dieses Elements
    Cube box;
    /// Objekte dieses Elements
    std::list<Object*> objects;
	
    /// Kindelemente
    Octree* children[8];
	
	bool alreadySplit;

    /// Unterteilung in 8 weitere Wuerfel
    Cube subCubes[8];
	
	void initChildren();
	bool divide(Object *o);
	void removeEmptyLeaves();

    bool splitCube(Cube *subCubes);
};

/**
 * Get Methode fuer die Bounding Box
 * @return const Bounding Box Reference
 */
inline const Cube* Octree::getBoundingBox() const
{
	return &box;
}

/**
 * Get Methode fuer eine Liste aller Objekte
 * @return Zeiger auf Listen mit Zeigern auf Objekte
 */
inline const std::list<Object*>* Octree::getObjects() const
{ 
	return &objects;
}

/**
 * Get Methode fuer die Kindknoten
 * @return Zeiger auf eine Liste mit Kindknoten
 */
inline const Octree *const *Octree::getChildren() const
{
	return children;
} 

#endif // OCTREE_H
