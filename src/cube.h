#ifndef CUBE_H
#define CUBE_H

#include "vector3d.h"
#include <string>

class Ray;

#define NUMBER_OF_EDGES 12

/// Beschreibung einer Kante
typedef struct Edge {
    // Startvektor
    Vector3D start;
    // Endvektor
    Vector3D end;
};

//bool isPointOnLine(const Edge &line, const Vector3D &vPoint);

/**
 * Geometrischer Wuerfel
 * Die Vertices sind in folgender Reihenfolge angeordnet.
 * Selbe Reihenfolge wird vom Konstruktor mit Parameter erwartet.
 *    4-------5
 *   /|      /|
 *  0-------1 |
 *  | |     | |
 *  | |7----|-|6
 *  |/      |/
 *  3-------2
 */
class Cube {

public:
	Cube();
	Cube(const Vector3D (&vertices)[8]);
	virtual ~Cube();
	
	bool enclosesPoint(const Vector3D &point) const;
	bool intersectsRay(const Ray &ray, Vector3D *res) const;
	
	Edge const *getEdges() const;
	
	Vector3D& operator[](unsigned int index);
	Vector3D operator[](unsigned int index) const;
	bool operator==(const Cube &cube) const;
	
	std::string toString() const;
	
	// QDebug Streaming Unterstuetzung
    #ifdef QT_CORE_LIB
    friend QDebug operator<<(QDebug dbg, const Cube &cube)
    {
        dbg.nospace()
             << "Cube(" 
             << cube.m_vertices[0].distanceTo(cube.m_vertices[1]) << ")";

        return dbg.space();
    }
    #endif

protected:
	/// Die acht Eckpunkte
	Vector3D m_vertices[8];
	/// Die zwoelf Kanten
	mutable Edge m_edges[NUMBER_OF_EDGES];
	
  void init();
};

/**
 * Ueberladener Array Operator [].
 * Ermoeglicht direkten Zugriff auf die Eckpunkte.
 * Ist index > 7 wird stets der letzte Eckpunkt zurueckgegeben.
 * @param index Index des Eckpunkts
 * @return Eckpunkt, dem Index entsprechend
 */
inline Vector3D& Cube::operator[](unsigned int index)
{
    return m_vertices[index > 7 ? 7 : index];
}

inline Vector3D Cube::operator[](unsigned int index) const
{
    return m_vertices[index > 7 ? 7 : index];
}

#endif // CUBE_H
