#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

class Sphere : public Object
{
public:
    Sphere(const Vector3D &center = Vector3D(),
           VTYPE radius = 1);

    VTYPE radius() const;
    Vector3D center() const;

    void setRadius(VTYPE radius);
    void setCenter(const Vector3D &center);
	
	bool operator==(const Sphere &sphere) const;

    bool intersectsRay(const Ray &ray, Vector3D *result) const;
    bool intersectsCube(const Cube &cube) const;
	bool isInsideOfCube(const Cube &cube) const;

	Cube getBoundingBox() const;
	Vector3D getNormal(const Vector3D &p) const;

	bool isSphere() const;
	
	std::string toString() const;

    void translate(const Vector3D &translation);

private:

    /// Mittelpunkt
    Vector3D m_center;

    /// Radius
    float m_radius;
};

/**
 * Standardkonstruktor
 * Wird kein Mittelpunkt definiert ist dieser der Nullpunkt.
 * Wird kein Radius definiert wird dieser auf Eins gesetzt.
 * @param center Mittelpunkts
 * @param radius Radius der Kugel
 */
inline Sphere::Sphere(const Vector3D &center /*= Vector3D()*/,
           VTYPE radius  /*= 1.0f*/)
    : Object(), m_center(center), m_radius(radius)
{
}

/**
  * Get Methode fuer den Radius
  * @return Radius
  */
inline VTYPE Sphere::radius() const
{
    return m_radius;
}

/**
  * Get Methode fuer den Mittelpunkt
  * @return Mittelpunkt
  */
inline Vector3D Sphere::center() const
{
    return m_center;
}

/**
  * Set Methode fuer den Radius
  * @param radius Neuer Radius
  */
inline void Sphere::setRadius(VTYPE radius)
{
    m_radius = radius;
}

/**
  * Set Methode fuer den Mittelpunkt
  * @param center Neuer Mittelpunkt
  */
inline void Sphere::setCenter(const Vector3D &center)
{
    m_center = center;
}

/**
 * Ueberladener == Operator
 * Vergleicht die beiden Kugeln
 * @param sphere Rechtsseitiger Operand
 * @return Gibt an, ob die beiden Kugeln gleich sind
 */
inline bool Sphere::operator==(const Sphere &sphere) const
{
    return (m_center == sphere.m_center)
		&& (m_radius == sphere.m_radius);
}

/**
 * Rtti fuer Kugelidentifizierung
 * @return true
 */
inline bool Sphere::isSphere() const
{
    return true;
}

/**
 * Gibt die Stringrepraesentation zurueck
 * @return Kugel als String
 */
inline std::string Sphere::toString() const
{
	return std::string("Sphere");
}

/**
 * Verschiebt die Kugel um den translation Vektor.
 * @param translation Translationsvektor
 */
inline void Sphere::translate(const Vector3D &translation)
{
    m_center += translation;
}

/**
 * Erstellt die Objektnormale fuer den Oberflachenpunkt p
 * @param p Punkt auf der Oberflaeche
 * @return Normalisierter Normalenvektor
 */
inline Vector3D Sphere::getNormal(const Vector3D &p) const
{
	return m_center.vectorTo(p).normalize();
}

#endif // SPHERE_H
