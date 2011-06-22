#ifndef RECT_H
#define RECT_H

#include "object.h"
#include "triangle.h"

class Rect : public Object
{
public:
    Rect(const Vector3D &a = Vector3D(),
         const Vector3D &b = Vector3D(),
         const Vector3D &c = Vector3D(),
         const Vector3D &d = Vector3D());
    virtual ~Rect();

    void setA(const Vector3D &a);
    void setB(const Vector3D &b);
    void setC(const Vector3D &c);
    void setD(const Vector3D &c);

    Vector3D A() const;
    Vector3D B() const;
    Vector3D C() const;
    Vector3D D() const;

    Vector3D& operator[](unsigned int index);
	bool operator==(const Rect &rect) const;

    bool intersectsRay(const Ray &ray, Vector3D *result) const;
    bool intersectsCube(const Cube &cube) const;
	bool isInsideOfCube(const Cube &cube) const;

	Cube getBoundingBox() const;
	Vector3D getNormal(const Vector3D &p) const;

	bool isRect() const;
	
	std::string toString() const;

    void translate(const Vector3D &translation);

     // QDebug Streaming Unterstuetzung
    #ifdef QT_CORE_LIB
    friend QDebug operator<<(QDebug dbg, const Rect &rect)
    {
        dbg.nospace()
             << "Rect("
             << rect.m_a << ", "
             << rect.m_b << ", "
             << rect.m_c << ", "
             << rect.m_d << ")";

        return dbg.space();
    }
    #endif

protected:
    Vector3D m_a;
    Vector3D m_b;
    Vector3D m_c;
    Vector3D m_d;
};

/**
 * Konstruktor mit Vektorinitialisierung
 * @param a A-Vektor
 * @param b B-Vektor
 * @param c C-Vektor
 * @param d D-Vektor
 */
inline Rect::Rect(const Vector3D &a /*= Vector3D()*/,
                 const Vector3D &b /*= Vector3D()*/,
                 const Vector3D &c /*= Vector3D()*/,
                 const Vector3D &d /*= Vector3D()*/)
    : Object(), m_a(a), m_b(b), m_c(c), m_d(d)
{
}

inline Rect::~Rect()
{
}

/**
  * Set Methode fuer A Vektor
  * @param a Neuer Wert fuer A
  */
inline void Rect::setA(const Vector3D &a)
{
    m_a = a;
}

/**
  * Set Methode fuer B Vektor
  * @param b Neuer Wert fuer B
  */
inline void Rect::setB(const Vector3D &b)
{
    m_b = b;
}

/**
  * Set Methode fuer C Vektor
  * @param c Neuer Wert fuer C
  */
inline void Rect::setC(const Vector3D &c)
{
    m_c = c;
}

/**
  * Set Methode fuer D Vektor
  * @param d Neuer Wert fuer D
  */
inline void Rect::setD(const Vector3D &d)
{
    m_d = d;
}

/**
  * Get Methode fuer A Vektor.
  * @return A Vektor
  */
inline Vector3D Rect::A() const
{
    return m_a;
}

/**
  * Get Methode fuer B Vektor.
  * @return B Vektor
  */
inline Vector3D Rect::B() const
{
    return m_b;
}

/**
  * Get Methode fuer A Vektor.
  * @return A Vektor
  */
inline Vector3D Rect::C() const
{
    return m_c;
}

/**
  * Get Methode fuer D Vektor.
  * @return D Vektor
  */
inline Vector3D Rect::D() const
{
    return m_d;
}

/**
 * Ueberladener Array Operator [].
 * Kann fuer den Zugriff auf die Vierecksvektoren
 * [index=0]=A, [index=1]=B, [index=2]=C und [index=3]=D genutzt werden.
 * Ist index > 3 wird stets der D Vektor zurueckgegeben.
 * @param index Index des Vektors
 * @return Vektor, dem Index entsprechend
 */
inline Vector3D& Rect::operator[](unsigned int index)
{
    return index > 2 ?
		m_d : index == 2 ?
		m_c : index == 1 ?
		m_b :
		m_a;
}

/**
 * Ueberladener == Operator
 * Vergleicht die beiden Vierecke Komponentenweise
 * @param rect Rechtsseitiger Operand
 * @return Gibt an, ob die beiden Vierecke gleich sind
 */
inline bool Rect::operator==(const Rect &rect) const
{
    return (m_a == rect.m_a)
		&& (m_b == rect.m_b)
		&& (m_c == rect.m_c)
		&& (m_d == rect.m_d);
}

/**
 * Prueft ob der Strahl ray dieses Viereck schneidet.
 * Gibt es einen Schnittpunkt verweist result darauf.
 * @param ray Zu testender Strahl
 * @param result Hier wird bei Existenz der Schnittpunkt abgelegt
 */
inline bool Rect::intersectsRay(const Ray &ray, Vector3D *result) const
{
    // Wird eines der beiden Dreiecke geschnitten,
    // wird auch das Viereck geschnitten
    return Triangle(m_a, m_b, m_d).intersectsRay(ray, result) ||
		   Triangle(m_b, m_c, m_d).intersectsRay(ray, result);
}

/**
 * Prueft ob das Viereck den Wuerfel cube in irgendeiner
 * Form raumlich schneidet.
 * @param cube Zu testender Wuerfel
 * @return true bei positivem Schnitttest
 */
inline bool Rect::intersectsCube(const Cube &cube) const
{
    return Triangle(m_a, m_b, m_d).intersectsCube(cube) ||
           Triangle(m_b, m_c, m_d).intersectsCube(cube);
}

/**
 * Testet ob das Viereck vom Wuerfel cube umschlossen wird
 * @param cube Zu testender Wuerfel
 * @return true Wenn der Wuerfel das Viereck komplett umschliesst
 */
inline bool Rect::isInsideOfCube(const Cube &cube) const
{
	return Triangle(m_a, m_b, m_d).isInsideOfCube(cube) &&
		   Triangle(m_b, m_c, m_d).isInsideOfCube(cube);
}

/**
 * Erstellt die Objektnormale fuer den Oberflaechenpunkt p
 * @param p Punkt auf der Oberflaeche
 * @return Normalisierter Normalenvektor
 */
inline Vector3D Rect::getNormal(const Vector3D &p) const
{
	//Vector3D n = Vector3D(m_b-m_a).crossProduct(m_c-m_a)
	if (Triangle(m_a, m_b, m_d).isPointInTriangle(p))
		return Vector3D(m_b-m_a).crossProduct(m_d-m_a);
	else if (Triangle(m_b, m_c, m_d).isPointInTriangle(p))
		return Vector3D(m_b-m_c).crossProduct(m_d-m_c);
	else
		return Vector3D();
	
	//return Vector3D();//m_b-m_a).crossProduct(m_c-m_a).normalize();
}

/**
 * Rtti fuer Viereckidentifizierung
 * @return true
 */
inline bool Rect::isRect() const
{
    return true;
}

/**
 * Gibt die Stringrepraesentation zurueck
 * @return Kugel als String
 */
inline std::string Rect::toString() const
{
	return std::string("Rect");
}

/**
 * Verschiebt das Viereck um den translation Vektor.
 * @param translation Translationsvektor
 */
inline void Rect::translate(const Vector3D &translation)
{
    m_a += translation;
    m_b += translation;
    m_c += translation;
    m_d += translation; 
}

#endif // RECT_H
