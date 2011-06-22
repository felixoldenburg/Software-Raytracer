#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"

class Triangle : public Object
{
public:
    Triangle(const Vector3D &a = Vector3D(),
             const Vector3D &b = Vector3D(),
             const Vector3D &c = Vector3D());
    virtual ~Triangle();

    void setA(const Vector3D &a);
    void setB(const Vector3D &b);
    void setC(const Vector3D &c);

    Vector3D A() const;
    Vector3D B() const;
    Vector3D C() const;

    Vector3D& operator[](unsigned int index);
    Vector3D operator[](unsigned int index) const;
	bool operator==(const Triangle &triangle) const;
	
	bool isPointInTriangle(const Vector3D &p) const;
    bool intersectsRay(const Ray &ray, Vector3D *result) const;
    bool intersectsCube(const Cube &cube) const;
	bool isInsideOfCube(const Cube &cube) const;

	Cube getBoundingBox() const;
	Vector3D getNormal(const Vector3D &p) const;
	
	bool isTriangle() const;
	
	std::string toString() const;

    void translate(const Vector3D &translation);

	// QDebug Streaming Unterstuetzung
    #ifdef QT_CORE_LIB
    friend QDebug operator<<(QDebug dbg, const Triangle &triangle)
    {
        dbg.nospace()
             << "Triangle("
             << triangle.m_a << ", "
             << triangle.m_b << ", "
             << triangle.m_c << ")";

        return dbg.space();
    }
    #endif
	
protected:
	bool rayIntersectsPlane(const Ray &ray,
						const Triangle &triangle,
						Vector3D *result) const;
protected:
    Vector3D m_a;
    Vector3D m_b;
    Vector3D m_c;
};

/**
 * Konstruktor mit Vektorinitialisierung
 * @param a A-Vektor
 * @param b B-Vektor
 * @param c C-Vektor
 */
inline Triangle::Triangle(const Vector3D &a /*= Vector3D()*/,
             const Vector3D &b /*= Vector3D()*/,
             const Vector3D &c /*= Vector3D()*/)
    : Object(), m_a(a), m_b(b), m_c(c)
{
}

inline Triangle::~Triangle()
{
}

/**
  * Set Methode fuer A Vektor
  * @param a Neuer Wert fuer A
  */
inline void Triangle::setA(const Vector3D &a)
{
    m_a = a;
}

/**
  * Set Methode fuer B Vektor
  * @param b Neuer Wert fuer B
  */
inline void Triangle::setB(const Vector3D &b)
{
    m_b = b;
}

/**
  * Set Methode fuer C Vektor
  * @param c Neuer Wert fuer C
  */
inline void Triangle::setC(const Vector3D &c)
{
    m_c = c;
}

/**
  * Get Methode fuer A Vektor
  * @return A Vektor
  */
inline Vector3D Triangle::A() const
{
    return m_a;
}

/**
  * Get Methode fuer B Vektor
  * @return B Vektor
  */
inline Vector3D Triangle::B() const
{
    return m_b;
}

/**
  * Get Methode fuer A Vektor
  * @return A Vektor
  */
inline Vector3D Triangle::C() const
{
    return m_c;
}

/**
 * Ueberladener Array Operator [] Read and Write.
 * Kann fuer den Zugriff auf die Dreicksvektoren
 * [index=0]=A, [index=1]=B und [index=2]=C genutzt werden.
 * Ist index > 2 wird stets der C Vektor zurueckgegeben.
 * @param index Index des Vektors
 * @return Vektor, dem Index entsprechend
 */
inline Vector3D& Triangle::operator[](unsigned int index)
{
    return index > 1 ?
            m_c : index == 1 ?
            m_b :
            m_a;
}

/**
 * Ueberladener Array Operator [] Read-Only.
 * @param index Index des Vektors
 * @return Vektor, dem Index entsprechend
 */
inline Vector3D Triangle::operator[](unsigned int index) const
{
    return index > 1 ?
            m_c : index == 1 ?
            m_b :
            m_a;
}

/**
 * Ueberladener == Operator
 * Vergleicht die beiden Dreiecke Komponentenweise
 * @param triangle Rechtsseitiger Operand
 * @return Gibt an, ob die beiden Dreiecke gleich sind
 */
inline bool Triangle::operator==(const Triangle &triangle) const
{
    return (m_a == triangle.m_a)
		&& (m_b == triangle.m_b)
		&& (m_c == triangle.m_c);
}

/**
 * Testet ob das Dreieck vom Wuerfel cube umschlossen wird
 * @param cube Zu testender Wuerfel
 * @return true Wenn der Wuerfel das Dreieck komplett umschliesst
 */
inline bool Triangle::isInsideOfCube(const Cube &cube) const
{
	return cube.enclosesPoint(m_a)
		&& cube.enclosesPoint(m_b)
		&& cube.enclosesPoint(m_c);
}

/**
 * Erstellt die Objektnormale fuer den Oberflaechenpunkt p
 * @param Parameter wird nicht benoetigt, da Oberflaechennormale fuer
 * jeden Punkt auf dem Dreieck gleich ist.
 * @return Normalisierter Normalenvektor, Unabhaenging ob der Parameter
 * auf dem Dreieck liegt, wird immer die Dreiecksoberflaechennormale
 * zurueckgegeben.
 */
inline Vector3D Triangle::getNormal(const Vector3D&) const
{
	return Vector3D(m_b-m_a).crossProduct(m_c-m_a).normalize();
}

/**
 * Rtti fuer Dreieckidentifizierung
 * @return true
 */
inline bool Triangle::isTriangle() const
{
    return true;
}

/**
 * Gibt die Stringrepraesentation zurueck
 * @return Kugel als String
 */
inline std::string Triangle::toString() const
{
	return std::string("Triangle");
}

#endif // TRIANGLE_H
