#ifndef OBJECT_H
#define OBJECT_H

#include "vectormath.h"
#include <string>
#include <list>

/**
 * Schnittstelle fuer Geometrieobjekte.
 * Stellt gemeinsame Funktionen bereit.
 */
class Object
{
public:
    Object() {}
    virtual ~Object() {}

	/// Schnitttest mit einem Strahl
    virtual bool intersectsRay(const Ray &ray, Vector3D *result) const = 0;
	/// Schnitttest mit eine Wuerfel
    virtual bool intersectsCube(const Cube &cube) const = 0;
	/// Prueft ob dieses Objekt komplett innerhalb eines Wuerfels liegt
	virtual bool isInsideOfCube(const Cube &cube) const = 0;
	/// Gibt die BoundingBox fuer das Objekt zurueck
	virtual Cube getBoundingBox() const = 0;
	/// Liefert die Objektnormale im Punkt p
	virtual Vector3D getNormal(const Vector3D &p) const = 0;
	/// Erstellt eine Bounding Box fuer mehrere Objekte
	static Cube  getBoundingBox(const std::list<Object*> &objects);

    virtual bool isTriangle() 	const { return false; }
    virtual bool isRect() 		const { return false; }
    virtual bool isSphere() 	const { return false; }
	
	// Stringrepraesentation des Objekts
	virtual std::string toString() const = 0;
	
	// QDebug Streaming Unterstuetzung
    #ifdef QT_CORE_LIB
    friend QDebug operator<<(QDebug dbg, const Object &o) 
	{
		dbg.nospace()
             << "Object("
			 << (o.isTriangle()?"Triangle":o.isRect()?"Rect":"Sphere")
			 << ")";

        return dbg.space();
	}
    #endif

    /**
      virtual member are somewhat slow when called many times!
      */

    /// Verschieben um einen Vektor
    virtual void translate(const Vector3D &translation) = 0;
    /// Rotation um einen Vektor
    //virtual void translate(const Vector3D &translation) = 0;    
};

#endif // OBJECT_H
