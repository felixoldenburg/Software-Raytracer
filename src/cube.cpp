#include "cube.h"
#include "vectormath.h"
#include <sstream>

/**
 * Prueft ob ein Punkt auf einer Strecke liegt.
 * Quelle: http://www.c-plusplus.de/forum/229815 * @param line Die zu testende Linie * @param point Zu pruefender Punkt * @return True, wenn der Punkt im Wuerfel liegt

bool isPointOnLine(const Edge &line, const Vector3D &vPoint)
{
    Vector3D u = line.end - line.start;
    VTYPE s = ((vPoint - line.start) * u) / (u*u);
    Vector3D f = line.start + s * u;
    return IS_ZERO((vPoint - f).length());
} */

Cube::Cube()
{
	// Null Initialisierung
	for (int i = 0; i < 8; ++i)
		m_vertices[i] = Vector3D();
}

/**
 * Ermoeglicht Angabe vordefinierter Eckpunkte
 */
Cube::Cube(const Vector3D (&vertices)[8])
{
	// Wuerfeleckpunkte aus Eingangsparameter uebernehmen
	memcpy(m_vertices, vertices, 8*sizeof(Vector3D));
}

Cube::~Cube()
{
}

/**
 * Gibt an, ob der Punkt point im Wuerfel liegt.
 * @param point Zu testender Punkt
 * @return true wenn Punkt im Wuerfel liegt
 */
bool Cube::enclosesPoint(const Vector3D& point) const
{
	VTYPE x = point.x(), y = point.y(), z = point.z();
		
	return
		!IS_SMALLER(x, m_vertices[0].x()) &&
		!IS_GREATER(x, m_vertices[1].x()) &&
		!IS_SMALLER(y, m_vertices[3].y()) &&
		!IS_GREATER(y, m_vertices[0].y()) &&
		!IS_SMALLER(z, m_vertices[4].z()) &&
		!IS_GREATER(z, m_vertices[0].z());
}

void swap(VTYPE *v1, VTYPE *v2)
{
	VTYPE tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

bool Cube::intersectsRay(const Ray &ray, Vector3D *res) const
{
	Vector3D bL = m_vertices[7];//[7];
	Vector3D bH = m_vertices[1];//[1];
	Ray rai = ray;
	rai.dir = ray.dir * 20;
	
	VTYPE tNear = -MAX_VALUE;
	VTYPE tFar = MAX_VALUE;
	VTYPE t1, t2;
	//int i = 0;
	for (int i = 0; i < 3; ++i)
	{
		if (IS_ZERO(rai.dir[i]))
		{
			if(IS_SMALLER(rai.point[i], bL[i]) || IS_GREATER(rai.point[i], bH[i]))
				return false;
		} else
		{
			t1 = (bL[i] - rai.point[i]) / rai.dir[i];
			t2 = (bH[i] - rai.point[i]) / rai.dir[i];

			if (IS_GREATER(t1, t2))
				swap(&t1, &t2);
				
			if (IS_GREATER(t1, tNear))
				tNear = t1;
				
			if (IS_SMALLER(t2, tFar))
				tFar = t2;
				
			if (IS_GREATER(tNear, tFar))
				return false;
				
			if (IS_SMALLER(tFar, 0))
				return false;
		}
	}
	
	*res = rai.point + rai.dir * tNear;
	
	return true;

	/*VTYPE t1n = (bL[0] - ray.point.x()) / (rai.dir.x() - ray.point.x());
	VTYPE t2n = (bL[1] - ray.point.y()) / (rai.dir.y() - ray.point.y());
	VTYPE t3n = (bL[2] - ray.point.z()) / (rai.dir.z() - ray.point.z());
	
	VTYPE t1f = (bH[0] - ray.point.x()) / (rai.dir.x() - ray.point.x());
	VTYPE t2f = (bH[1] - ray.point.y()) / (rai.dir.y() - ray.point.y());
	VTYPE t3f = (bH[2] - ray.point.z()) / (rai.dir.z() - ray.point.z());
	
	VTYPE tn = MAX(MAX(t1n, t2n), t3n);
	VTYPE tf = MIN(MIN(t1f, t2f), t3f);
	
	if ((tn < tf) && (tf > 0))
	{
		*res = ray.point + ray.dir * tn;
		return true;
	}
	else
		return false;
	*/
}

/**
 * Get Methode fuer die zwoelf Kanten des Wuerfels.
 * Aktualisiert m_edges vor Rueckgabe.
 * @return Zeiger auf Array mit Kanten
 */
Edge const *Cube::getEdges() const
{
	#define v(x) m_vertices[x]
	// Alle Kanten des Wuerfels
	Edge edges[] = {
		{v(0), v(1)}, {v(1), v(2)}, {v(2), v(3)},
		{v(3), v(0)}, {v(4), v(5)}, {v(5), v(6)},
		{v(6), v(7)}, {v(7), v(4)}, {v(0), v(4)},
		{v(1), v(5)}, {v(3), v(7)}, {v(2), v(6)}
	};
	
	// Inhalt nach m_edges kopieren
	memcpy(m_edges, edges, NUMBER_OF_EDGES*sizeof(Edge));
	
	return m_edges;
}

/**
 * Ueberladener == Operator
 * Vergleicht die beiden Wuerfel Komponentenweise
 * @param cube Rechtsseitiger Operand
 * @return Gibt an, ob die beiden Wuerfel gleich sind
 */
bool Cube::operator==(const Cube &cube) const
{
	for (int i = 0; i < 8; ++i)
		if (m_vertices[i] != cube.m_vertices[i])
			return false;
    return true;
}

std::string vecToStr(const Vector3D &v)
{
	std::stringstream buffer;
	buffer << (int)v.x() << "|" << (int)v.y() << "|" << (int)v.z();
	return buffer.str();
}

std::string Cube::toString() const
{ 
	#define v(x) m_vertices[x]
	std::stringstream buffer;
	std::string s[8] = {
		vecToStr(v(0)), vecToStr(v(1)), vecToStr(v(2)), vecToStr(v(3)), 
		vecToStr(v(4)), vecToStr(v(5)), vecToStr(v(6)), vecToStr(v(7))}; 
		 
    buffer << 
		s[4] << " " << s[5] << "\n"
		"       4-------5 \n"
		"      /|      /| \n"
		"     0-------1 |  " << s[1] << "\n"
		"     | |     | | \n"
		"     | |7----|-|6 " << s[6] << "\n"
		"     |/      |/  \n"
		"     3-------2   \n" <<
		s[3] << " " << s[2];
		
	return buffer.str();
}
