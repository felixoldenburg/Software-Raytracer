#include "rect.h"/**
 * Ermittelt die Bounding Box fuer das Viereck
 * @return Bounding Box
 */
Cube Rect::getBoundingBox() const
{
	Cube c;
	
	// Den kleinsten x Wert ermitteln
	c[0][0] = c[3][0] = c[4][0] = c[7][0] =
		MIN(MIN(m_a.x(), m_b.x()), MIN(m_c.x(), m_d.x()));
		
	// Den groessten x Wert ermitteln
	c[1][0] = c[2][0] = c[5][0] = c[6][0] =
		MAX(MAX(m_a.x(), m_b.x()), MAX(m_c.x(), m_d.x()));
	
	// Den kleinsten y Wert ermitteln
	c[2][1] = c[3][1] = c[6][1] = c[7][1] = 
		MIN(MIN(m_a.y(), m_b.y()), MIN(m_c.y(), m_d.y()));
	
	// Den groessten y Wert ermitteln
	c[0][1] = c[1][1] = c[4][1] = c[5][1] = 
		MAX(MAX(m_a.y(), m_b.y()), MAX(m_c.y(), m_d.y()));
		
	// Den kleinsten z Wert ermitteln
	c[4][2] = c[5][2] = c[6][2] = c[7][2] = 
		MIN(MIN(m_a.z(), m_b.z()), MIN(m_c.z(), m_d.z()));
	
	// Den groessten z Wert ermitteln
	c[0][2] = c[1][2] = c[2][2] = c[3][2] = 
		MAX(MAX(m_a.z(), m_b.z()), MAX(m_c.z(), m_d.z()));

	return c;
}