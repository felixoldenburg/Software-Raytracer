#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "color.h"
#include "vector3d.h"

/**
 * Repraesentiert eine einfache Punktlichtquelle mit
 * homogener Abstrahlcharakteristik.
 * Die Lichtquelle hat eine Farbe.
 */
class Lightsource {

public:
	Lightsource() : m_pos(Vector3D()), m_color(Color()) {};
	Lightsource(const Vector3D &pos, const Color &color)
		: m_pos(pos), m_color(color) {};
	~Lightsource();

	Vector3D pos() const;
	void setPos(const Vector3D &pos);
	
	Color color() const;
	void setColor(const Color &color);

protected:
	Vector3D m_pos;
	Color m_color;
};

/**
 * Get Methode fuer Position
 * @return Position des Lichts
 */
inline Vector3D Lightsource::pos() const
{
    return m_pos;
}/**
 * Set Methode fuer Position
 * @param pos Neuer Wert fuer die Position
 */
inline void Lightsource::setPos(const Vector3D &pos)
{
    m_pos = pos;
}

/**
 * Get Methode fuer Farbe
 * @return Farbe des Lichts
 */
inline Color Lightsource::color() const
{
    return m_color;
}

/**
 * Set Methode fuer Farbe
 * @param color Neuer Wert fuer die Farbe
 */
inline void Lightsource::setColor(const Color &color)
{
    m_color = color;
}

#endif // LIGHTSOURCE_H
