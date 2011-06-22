#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>
#include <limits>

#ifdef QT_CORE_LIB
#include <QDebug>
#endif

// Datentyp der Vektorkomponenten
#define VTYPE double
// Makros zum Vergleichen von Gleitkommawerten
#define EPSILON 2E-07//(std::numeric_limits<VTYPE>::epsilon())
#define IS_EQUAL(a,b) (fabs((a)-(b)) <= EPSILON)
#define IS_SMALLER(a,b) ((a)+EPSILON<(b))
#define IS_GREATER(a,b) ((b)+EPSILON<(a))
#define IS_ZERO(a) (fabs((a))<=EPSILON)
#define IS_GREATER_ZERO(x) ((x) > std::numeric_limits<VTYPE>::epsilon())
#define MIN(a, b) (IS_SMALLER((a), (b))?(a):(b))
#define MAX(a, b) (IS_GREATER((a), (b))?(a):(b))
#define MIN_VALUE (std::numeric_limits<VTYPE>::min())
#define MAX_VALUE (std::numeric_limits<VTYPE>::max())

/**
 * Vektor mit 3 Dimensionen
 * Unterstuetzt einfache Vektorrechnungen:
 * Vektorlaenge, Skalarprodukt, Kreuzprodukt, Distanz zu einem anderen Vektor
 *
 * Saemtliche Methoden sind zwecks Geschwindigkeitsoptimierung inline definiert.
 */
class Vector3D
{
public:
    Vector3D(VTYPE x = 0, VTYPE y = 0, VTYPE z = 0);

    VTYPE x() const;
    VTYPE y() const;
    VTYPE z() const;
    VTYPE* xyz();
	const VTYPE* xyz() const;

    void setX(VTYPE x);
    void setY(VTYPE y);
    void setZ(VTYPE z);
    Vector3D& modX(VTYPE x);
    Vector3D& modY(VTYPE y);
    Vector3D& modZ(VTYPE z);

    Vector3D normalize() const;

    VTYPE length() const;

    VTYPE distanceTo(const Vector3D &vector) const;
    Vector3D vectorTo(const Vector3D &vector) const;

    Vector3D crossProduct(const Vector3D &vector) const;

    Vector3D& operator+=(const Vector3D &vector);
    Vector3D& operator-=(const Vector3D &vector);

    Vector3D& operator*=(VTYPE scale);

    const Vector3D operator+(const Vector3D &vector) const;
    const Vector3D operator-(const Vector3D &vector) const;

    friend inline VTYPE operator*(const Vector3D &vector1, const Vector3D &vector2);
    friend inline Vector3D operator*(const Vector3D &vector, VTYPE scale);
    friend inline Vector3D operator*(VTYPE scale, const Vector3D &vector);

    VTYPE& operator[](unsigned int index);

    bool operator==(const Vector3D &vector) const;
	bool operator!=(const Vector3D &vector) const;

    // QDebug Streaming Unterstuetzung
    #ifdef QT_CORE_LIB
    friend QDebug operator<<(QDebug dbg, const Vector3D &vector)
    {
        dbg.nospace()
             << "V("
             << vector.m_x << ", "
             << vector.m_y << ", "
             << vector.m_z << ")"; //", length: " << vector.length() << ")";

        return dbg.space();
    }
    #endif

protected:

	// Anonymes struct gewaehrleistet gleiche Reihenfolge
	// der Komponenten im Speicher, wie bei der Deklaration
	// und ermoeglicht damit Pointerarithmetik.
	// z.B.: z == *(&m_x+2)
	struct {
		VTYPE m_x;
		VTYPE m_y;
		VTYPE m_z;
	};

};

/**
 * Konstruktor mit Komponenteninitialisierung
 * @param x X-Komponente
 * @param y Y-Komponente
 * @param z Z-Komponente
 */
inline Vector3D::Vector3D(VTYPE x /*=0*/, VTYPE y /*=0*/, VTYPE z /*=0*/)
	: m_x(x), m_y(y), m_z(z) {}

/**
 * Get Methode fuer X Komponente.
 * @return X Komponente des Vektors
 */
inline VTYPE Vector3D::x() const
{
    return m_x;
}

/**
 * Get Methode fuer Y Komponente.
  * @return Y Komponente des Vektors
*/
inline VTYPE Vector3D::y() const
{
    return m_y;
}

/**
 * Get Methode fuer Z Komponente.
 * @return Z Komponente des Vektors
 */
inline VTYPE Vector3D::z() const
{
    return m_z;
}

/**
 * Gibt einen Pointer auf den X-Wert zurueck.
 * Kann fuer vektorbasierten Zugriff verwendet werden.
 * (x,y und z liegen in dieser Reihenfolge im Speicher hintereinander)
 */
inline VTYPE* Vector3D::xyz() 
{
	return &m_x;
}

/**
 * Gibt einen const Pointer auf den X-Wert zurueck.
 * Kann fuer vektorbasierten Zugriff verwendet werden.
 * (x,y und z liegen in dieser Reihenfolge im Speicher hintereinander)
 */
inline const VTYPE* Vector3D::xyz() const
{
	return &m_x;
}

/**
 * Set Methode fuer X Komponente
 * @param x Neuer Wert fuer X
 */
inline void Vector3D::setX(VTYPE x)
{
    m_x = x;
}

/**
 * Set Methode fuer Y Komponente
 * @param y Neuer Wert fuer Y
 */
inline void Vector3D::setY(VTYPE y)
{
    m_y = y;
}

/**
 * Set Methode fuer Z Komponente
 * @param z Neuer Wert fuer Z
 */
inline void Vector3D::setZ(VTYPE z)
{
    m_z = z;
}

/**
 * Wie setX, gibt jedoch den modifizierten Vektor zurueck
 * @param x Neuer Wert fuer X
 * @return Modifizierter Vektor
 */
inline Vector3D& Vector3D::modX(VTYPE x)
{
    m_x = x;
    return *this;
}

/**
 * Wie setY, gibt jedoch den modifizierten Vektor zurueck
 * @param y Neuer Wert fuer Y
 * @return Modifizierter Vektor
 */
inline Vector3D& Vector3D::modY(VTYPE y)
{
    m_y = y;
    return *this;
}

/**
 * Wie setZ, gibt jedoch den modifizierten Vektor zurueck
 * @param z Neuer Wert fuer Z
 * @return Modifizierter Vektor
 */
inline Vector3D& Vector3D::modZ(VTYPE z)
{
    m_z = z;
    return *this;
}

/**
 * Gibt einen normierten Version dieses
 * Vektors zurueck, dessen Betrag eins ist.
 */
inline Vector3D Vector3D::normalize() const
{
    VTYPE d = length();

    return Vector3D(m_x / d, m_y / d, m_z / d);
}

/**
 * Berechnet die Laenge des Vektors.
 * @return Laenge des Vektors
 */
inline VTYPE Vector3D::length() const
{
    return sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

/**
 * Ermittelt die Distanz zu dem Punkt vector
 * @param vector Ortsvektor, bzw. Punkt zu dem der Abstand berechnet werden soll
 * @return Abstand von vector zum diesem Vektor
 */
inline VTYPE Vector3D::distanceTo(const Vector3D &vector) const
{
    return Vector3D(vector - *this).length();
}

/**
 * Ermittelt den Vektor von diesem Vektor zu vector
 * @param vector Ortsvektor, bzw. Punkt zu dem der Vektor berechnet werden soll
 * @return Abstandsvektor
 */
inline Vector3D Vector3D::vectorTo(const Vector3D &vector) const
{
    return vector - *this;
}

/**
 * Berechnet das Kreuzprodukt mit dem Vektor vector
 * @param vector Rechtsseitiger Operator der Kreuzpdoruktberechnung
 * @return Kreuzprodukt
 */
inline Vector3D Vector3D::crossProduct(const Vector3D &vector) const
{
    return Vector3D(
		m_y*vector.m_z - m_z*vector.m_y,
		m_z*vector.m_x - m_x*vector.m_z,
		m_x*vector.m_y - m_y*vector.m_x
	);
}

/**
 * Ueberladener += Operator
 * @param vector Rechtsseitiger Operand
 */
inline Vector3D& Vector3D::operator+=(const Vector3D &vector)
{
    m_x += vector.m_x;
    m_y += vector.m_y;
    m_z += vector.m_z;

    return *this;
}

/**
 * Ueberladener -= Operator
 * @param vector Rechtsseitiger Operand
 */
inline Vector3D& Vector3D::operator-=(const Vector3D &vector)
{
    m_x -= vector.m_x;
    m_y -= vector.m_y;
    m_z -= vector.m_z;

    return *this;
}

/**
 * Ueberladener *= Operator skaliert den Vektor um den Fatkor scale
 * @param vector Rechtsseitiger Operand
 */
inline Vector3D& Vector3D::operator*=(VTYPE scale)
{
    m_x *= scale;
    m_y *= scale;
    m_z *= scale;

    return *this;
}

/**
 * Ueberladener + Operator
 * @param vector Rechtsseitiger Operand
 */
inline const Vector3D Vector3D::operator+(const Vector3D &vector) const
{
    return Vector3D(*this) += vector;
}

/**
 * Ueberladener - Operator
 * @param vector Rechtsseitiger Operand
 */
inline const Vector3D Vector3D::operator-(const Vector3D &vector) const
{
    return Vector3D(*this) -= vector;
}

/**
 * Ueberladener * Operator definiert das Skalarprodukt
 * @param vector1 Linksseitiger Operand
 * @param vector2 Rechtsseitiger Operand
 * @return Skalarprodukt der beiden Vektoren
 */
inline VTYPE operator*(const Vector3D &vector1, const Vector3D &vector2)
{
    return vector1.m_x*vector2.m_x
		 + vector1.m_y*vector2.m_y
		 + vector1.m_z*vector2.m_z;
}

/**
 * Ueberladener * Operator skaliert den Vektor um den Faktor scale
 * @param vector Linksseitiger Operand
 * @param scale Rechtsseitiger Operand
 * @return Skalierter Vektor
 */
inline Vector3D operator*(const Vector3D &vector, VTYPE scale)
{
    return Vector3D(vector) *= scale;
}

/**
 * Ueberladener * Operator skaliert den Vektor um den Faktor scale
 * @param scale Linksseitiger Operand
 * @param vector Rechtsseitiger Operand
 * @return Skalierter Vektor
 */
inline Vector3D operator*(VTYPE scale, const Vector3D &vector)
{
    return Vector3D(vector) *= scale;
}

/**
 * Ueberladener Array Operator [].
 * Kann fuer den Zugriff auf die Vektorkomponenten
 * [index=0]=X, [index=1]=Y und [index=2]=Z genutzt werden.
 * Ist index > 2 wird stets die Z Komponenten zurueckgegeben.
 * @param index Index der Komponente
 * @return Vektorkomponente, dem Index entsprechend
 */
inline VTYPE& Vector3D::operator[](unsigned int index)
{
    return index > 1 ?
		m_z : index == 1 ?
		m_y :
		m_x;
}

/**
 * Ueberladener == Operator
 * Vergleicht die beiden Vektoren Komponentenweise
 * Nutzt EPSILON zur Beruecksichtigung der Gleitkommazahlenungenauigkeit
 * beim Vergleich.
 * @param vector Rechtsseitiger Operand
 * @return Gibt an, ob die beiden Vektoren gleich sind
 */
inline bool Vector3D::operator==(const Vector3D &vector) const
{
    return IS_EQUAL(m_x, vector.m_x)
		&& IS_EQUAL(m_y, vector.m_y)
		&& IS_EQUAL(m_z, vector.m_z);
}

/**
 * Ueberladener != Operator
 * @param vector Rechtsseitiger Operand
 * @return Gibt an, ob die beiden Vektoren ungleich sind
 */
inline bool Vector3D::operator!=(const Vector3D &vector) const
{
    return !(*this == vector);
}

#endif // VECTOR3D_H
