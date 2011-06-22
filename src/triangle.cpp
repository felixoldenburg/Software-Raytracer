#include "triangle.h"
#include <iostream>

/**
 * Prueft ob der Strahl ray die Ebene, welche durch das Dreieck
 * triangle definiert ist, schneidet.
 * @param ray Zu testender Strahl
 * @param triangle Dreieck das die Ebene beschreibt
 * @param result Ergebnisvektor: Schneidet der Strahl die Ebene
 * liegt das Ergebnis in result vor
 * @pre result Muss auf ein existierendes Vektor-Objekt zeigen
 */
bool Triangle::rayIntersectsPlane(const Ray &ray,
                                  const Triangle &triangle,
                                  Vector3D *result) const
{
    bool bResult = false;

    // Zwei Seiten des Dreieck fuer die Normalenvektorberechnung
    Vector3D ab(triangle[1] - triangle[0]);
    Vector3D ac(triangle[2] - triangle[0]);
    // Normalenvektor der Ebene, Kreuzprodukt ab x ac
    Vector3D n(ab.crossProduct(ac));
    // Konstante aus der Ebenengleichung in Normalform
    // e: n * (x,y,z) + c = 0
    VTYPE c = n * triangle.A();

    // Ortsvektor des Strahls
    Vector3D o(ray.point);
    // Richtungsvektor des Strahls
    Vector3D d(ray.dir);

    // Geradenparameter t erhaelt man durch Einsetzen der
    // Geradengleichung in die Ebenengleichung(Normalform)
    VTYPE t_denominator = n[0]*d[0] + n[1]*d[1] + n[2]*d[2];

    // Der Nenner muss gueltig(!=0) sein
    if (!IS_EQUAL(t_denominator, 0))
    {
        // Minuszeichen extrahiert, um Gleitkommazahlenungenauigkeit durch
        // Subtraktionen zu verhinden
        VTYPE t_numerator = n[0]*o[0] + n[1]*o[1] + n[2]*o[2] - c;
        VTYPE t = t_numerator / t_denominator;

        // Das extrahierte Minuszeichen wird hier durch Umkehren des
        // > Operators beruecksichtigt. Statt t>=0, also -t<=0.
        // Da jedoch bei rekursivem Raytracing die Strahlen ihren Ursprung auf Objekt-
        // oberflachen haben, muss t != 0 sein, da ansonsten sofort wieder ein
        // Schnittpunkt im Strahlenursprung festgestellt werden wuerde.
        if (IS_SMALLER(t,0)) // Ebene darf nicht hinter dem Strahl liegen
        {
            // Schnittpunkt durch Einsetzen von t in Geradengleichung
            // Auch hier muss wieder das extrahierte Minuszeichen beachtet werden
            *result = o + d * -t;
            bResult = true;
        }
    }

    return bResult;
}

bool Triangle::isPointInTriangle(const Vector3D &p) const
{
	Vector3D v0(m_c - m_a);
	Vector3D v1(m_b - m_a);
	Vector3D v2(p - m_a);

	VTYPE dot00 = v0 * v0;
	VTYPE dot01 = v0 * v1;
	VTYPE dot02 = v0 * v2;
	VTYPE dot11 = v1 * v1;
	VTYPE dot12 = v1 * v2;

	VTYPE invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	VTYPE u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	VTYPE v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	return (!IS_SMALLER(u,0)) && (!IS_SMALLER(v,0)) && (!IS_GREATER(u+v,1));
}

/**
 * Prueft ob der Strahl ray dieses Dreieck schneidet.
 * Gibt es einen Schnittpunkt verweist result darauf.
 * @param ray Zu testender Strahl
 * @param result Hier wird bei Existenz der Schnittpunkt abgelegt
 */
bool Triangle::intersectsRay(const Ray &ray, Vector3D *result) const
{
    bool bResult = false;

    // Schneidet der Strahl die Ebene des Dreiecks?
    // Schnittpunkt des Strahls mit Ebene des Dreiecks
    Vector3D i;
    if (rayIntersectsPlane(ray, *this, &i))
		// Liegt Schnittpunkt zur Ebene im Dreieck?
		if (bResult = isPointInTriangle(i))
			*result = i;

    return bResult;
}

/**
 * Verschiebt das Dreieck um den translation Vektor.
 * @param translation Translationsvektor
 */
void Triangle::translate(const Vector3D &translation)
{
    m_a += translation;
    m_b += translation;
    m_c += translation;
}

/**
 * Prueft ob das Dreieck den Wuerfel cube in irgendeiner
 * Form raumlich schneidet.
 * @param cube Zu testender Wuerfel
 * @return true bei positivem Schnitttest
 */
bool Triangle::intersectsCube(const Cube &cube) const
{
	// Die Seiten des Dreiecks als Strahlen
    Ray rays[] = {{m_a, m_c-m_a}, {m_a, m_b-m_a}, {m_b, m_c-m_b}};
    // Alle Wuerfelseiten
    Triangle cubeSides[] = {
        Triangle(cube[0], cube[1], cube[3]), // Vorne
        Triangle(cube[1], cube[5], cube[2]), // Rechts
        Triangle(cube[5], cube[4], cube[6]), // Hinten
        Triangle(cube[4], cube[0], cube[7]), // Links
        Triangle(cube[4], cube[5], cube[0]), // Oben
        Triangle(cube[3], cube[2], cube[7])  // Unten
    };

    Vector3D res;
    // Fuer jeden Dreiecksseite
    for (int r = 0; r < 3; ++r)
        // Fuer alle 6 Seiten eines Wuerfels
        for (int i = 0; i < 6; ++i)
        {
            // Schneidet eine Gerade, definiert durch die Seite
            // eines Dreiecks eine Seite des Wuerfels?
            if (rayIntersectsPlane(rays[r], cubeSides[i], &res))
                // Schnittpunkt muss auf der Seite des Dreiecks liegen
                if (isPointOnLine(rays[r].point, rays[r].dir, res))
                    return true;
        }

    // Keine Wuerfelseite wurde geschnitte
    // Testen, ob Dreieck innerhalb des Wuerfels liegt
    return cube.enclosesPoint(m_a) ||
           cube.enclosesPoint(m_b) ||
           cube.enclosesPoint(m_c);
}

/**
 * Ermittelt die Bounding Box fuer das Viereck
 * @return Bounding Box
 */
Cube Triangle::getBoundingBox() const
{
	Cube c;
	
	// Den Kleinsten x Wert ermitteln
	c[0][0] = c[3][0] = c[4][0] = c[7][0] =
		MIN(MIN(m_a.x(), m_b.x()), m_c.x());
		
	// Den groessten x Wert ermitteln
	c[1][0] = c[2][0] = c[5][0] = c[6][0] =
		MAX(MAX(m_a.x(), m_b.x()), m_c.x());
	
	// Den kleinsten y Wert ermitteln
	c[2][1] = c[3][1] = c[6][1] = c[7][1] = 
		MIN(MIN(m_a.y(), m_b.y()), m_c.y());
	
	// Den groessten y Wert ermitteln
	c[0][1] = c[1][1] = c[4][1] = c[5][1] = 
		MAX(MAX(m_a.y(), m_b.y()), m_c.y());
		
	// Den kleinsten z Wert ermitteln
	c[4][2] = c[5][2] = c[6][2] = c[7][2] = 
		MIN(MIN(m_a.z(), m_b.z()), m_c.z());
	
	// Den groessten z Wert ermitteln
	c[0][2] = c[1][2] = c[2][2] = c[3][2] = 
		MAX(MAX(m_a.z(), m_b.z()), m_c.z());

	return c;
}
