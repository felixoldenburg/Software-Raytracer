#include "sphere.h"

#include "vectormath.h"

#include <iostream>
#include <cstdio>

/**
 * Prueft ob der Strahl ray diese Kugel schneidet.
 * Es wird ein effizientes Verfahren verwendet, welches weniger
 * arithmetische Schritte verwendet, als z.B. beim Einsetzen der
 * Strahlengleichung in die Kugelgleichung.
 * Durch Lagetest des Strahlenursprungs (innerhalb/ausserhalb der Kugel)
 * kann u.U. frueher abgebrochen werden und somit noch mehr Operationen eingespart werden.
 * Ausserdem wird nur eine einzige Wurzeloperation benoetigt und auch nur dann,
 * wenn der endgueltige Schnittpunkt berechnet wird.
 * Gibt es einen Tangentialpunkt verweist result darauf.
 * Gibt es zwei Schnittpunkte verweist result auf den dem
 * Strahlenursprung naeheren Schnittpunkt.
 * @param ray Zu testender Strahl
 * @param result Verweist bei Existenz eines Schnittpunkts auf selbigen
 */
bool Sphere::intersectsRay(const Ray &ray, Vector3D *result) const
{
    bool bResult = false;

    // Strahl mit normalisiertem Richtungsvektor
    Ray r = {ray.point, ray.dir.normalize()};

    // Quadrat des Radius
    double rSquare = m_radius * m_radius;
    // Vektor vom Strahlenursprung zum Kugel-Mittelpunkt
    Vector3D om(m_center - r.point);
    // Laengenquadrat von om, bzw. Skalarprodukt mit sich selber
    double omDot = om * om;

    // Gibt an, ob der Strahlenursprung innerhalb der Kugel liegt
    // (in diesem Fall gibt es auf jeden Fall einen Schnittpunkt)
    bool bInner = IS_SMALLER(omDot, rSquare);

    // n sei der Punkt auf dem Strahl, der dem Kugelzentrum
    // am naechsten ist.
    // ln(om * r.dir) sei die Strecke/Vektorlaenge vom Strahlenursprung zu n
    VTYPE ln =  om * r.dir;

    // Entfernungsquadrat von n zur Kugeloberflaeche
    VTYPE hSquare;

    // hSquare nur berechnen, wenn Strahlenursprung innerhalb der Kugel
    // oder Strahl nicht von Kugel wegzeigt (ln >= 0)
    if (bInner || !IS_SMALLER(ln, 0))
    {
        hSquare = rSquare + ln*ln - omDot;
		if(bInner)
			qDebug() << "ATTENTION!ATTENTION!ATTENTION!ATTENTION!ATTENTION!";
        // Lambda: Parameter der Strahlengleichung, ray: ray.point + lambda * ray.dir
        // Lambda muss positiv sein, damit beim rekursiven Ray Tracing
        // der Strahlursprung auf der Kugeloberflaeche nicht als neuer
        // Schnittpunkt erkannt wird
        VTYPE lambda;
        if (IS_GREATER((lambda = (ln + sqrt(hSquare) * (bInner?1:-1))),0))
            // Es gibt einen Schnittpunkt, wenn Strahlenursprung innerhalb Kugel,
            // oder aber der Strahl die Kugel nicht verfehlt(hSquare >= 0)
            if (bResult = (bInner || !IS_SMALLER(hSquare, 0)))
                *result = r.point + lambda * r.dir;
    }
	
	if (bResult && (result->x() == -22.3193626f))
		qDebug() << "RICHTIG:" << r.point << r.dir << ", " << *result;

    return bResult;
}

/**
 * Prueft ob die Kugel den Wuerfel cube in irgendeiner
 * Form raeumlich schneidet. Dabei sind drei Faelle zu unterscheiden:
 * 1.: Der Wuerfel liegt komplett innerhalb der Kugel,
 *     oder ein Eckpunkt des Wuerfels liegt in der Kugel
 * 2.: Eine Kante schneidet/tangiert die Kugel
 * 3.: Der Wuerfel umschliesst die Kugel vollstaendig
 * 
 * @param cube Zu testender Wuerfel
 * @return true bei positivem Schnitttest
 */
bool Sphere::intersectsCube(const Cube &cube) const
{
	// Fall 3:
	bool result = cube.enclosesPoint(m_center);
	
	// Fall 1:
	for (int i = 0; i < 8 &! result; ++i)
		result = !IS_GREATER(m_center.distanceTo(cube[i]), m_radius);
		
	// Fall 2:
	if (!result)
	{
		// Zum zwischenspeichern eines evt. Schnittpunktes
		Vector3D tmp;
		Ray r;
		// Ermittle alle Kanten des Wuerfels
		const Edge *edges = cube.getEdges();

		// Fuer jede Kante...
		for (int i = 0; i < NUMBER_OF_EDGES &! result; ++i, edges++)
		{
			// Erzeuge einen Strahl, kongruent zur Kante
			r.point = edges->start;
			r.point = edges->start.vectorTo(edges->end);
			
			// Schneidet den Strahl die Kugel...
			if (intersectsRay(r, &tmp))
				// Testen, ob der Schnittpunkt auf der Kante liegt
				result = isPointOnLine(edges->start, edges->end, tmp);
		}
	}
	
	return result;
}
#include <qDebug>
/**
 * Testet ob die Kugel vom Wuerfel cube umschlossen wird
 * @param cube Zu testender Wuerfel
 * @return true Wenn der Wuerfel die Kugel komplett umschliesst
 */
bool Sphere::isInsideOfCube(const Cube &cube) const
{
	//static int oi = 0;
	//oi++;
	//if (oi == 2)
	//{
	//qDebug() << "++++++++++++++++++++";
	//qDebug() << *this << m_center;
	//qDebug() << cube.toString().c_str();
	//qDebug() << "++++++++++++++++++++";}
	
	//qDebug() << "cubbi: " << cube[0];
	
	
	bool result = cube.enclosesPoint(m_center);
	//qDebug() << "0:" << result;
	
	Vector3D pX = cube[1].modY(m_center.y()).modZ(m_center.z());
	Vector3D nX = cube[0].modY(m_center.y()).modZ(m_center.z());
	
	Vector3D pY = cube[1].modX(m_center.x()).modZ(m_center.z());
	Vector3D nY = cube[2].modX(m_center.x()).modZ(m_center.z());
	
	Vector3D pZ = cube[0].modX(m_center.x()).modY(m_center.y());
	Vector3D nZ = cube[4].modX(m_center.x()).modY(m_center.y());
	
	result = result	&& !IS_SMALLER(m_center.vectorTo(pX).length(), m_radius);//if (oi == 2) qDebug() << "res: " << result;
	result = result	&& !IS_SMALLER(m_center.vectorTo(nX).length(), m_radius);//if (oi == 2) qDebug() << "res: " << result;
		
	result = result	&& !IS_SMALLER(m_center.vectorTo(pY).length(), m_radius);//if (oi == 2) qDebug() << "res: " << result;
	result = result	&& !IS_SMALLER(m_center.vectorTo(nY).length(), m_radius);//if (oi == 2) qDebug() << "res: " << result;
	//VTYPE r1 = m_center.vectorTo(pZ).length();
	//VTYPE r2 = m_radius;
	//VTYPE t1 = (float)r1+EPSILON, t2 = r2;
	//VTYPE ra = 0.91f;
	//VTYPE rb = 0.91f;
	//std::cout << "lkjlkjljlk" << r1 << ", " << r2  << "Eps: " << EPSILON << "Smaller2: " << (((float)(r1+EPSILON))<r2) << std::endl;
	//printf("is %lf < %lf == %d diff: %E\n", r1, r2, ((r2-r1)>EPSILON), r2-r1);
	//printf("is %lf > %lf == %d\n", (r2-r1), EPSILON, ((r2-r1)>EPSILON));
	
	//printf("JKJ %E, %E, Epsilon: %E  %E\n", r1, r2, EPSILON, (float)(EPSILON+r1));
	//if (oi == 2) qDebug() << "RES: " << (float)m_center.vectorTo(pZ).length() << ", r: " << (float)m_radius
	//<< "::: " << IS_SMALLER(m_center.vectorTo(pZ).length(), m_radius) << "HH2: " << IS_SMALLER(ra, rb) << "u: " << r1 << r2;;
	result = result	&& !IS_SMALLER(m_center.vectorTo(pZ).length(), m_radius);//if (oi == 2) qDebug() << "res: " << result << pZ;
	result = result	&& !IS_SMALLER(m_center.vectorTo(nZ).length(), m_radius);//if (oi == 2) qDebug() << "res: " << result << nZ;
	
	return result;
}

/**
 * Ermittelt die Bounding Box fuer das Viereck
 * @return Bounding Box
 */
Cube Sphere::getBoundingBox() const
{
	Cube c;
	
	static int oi = 0;
	oi++;
	
	// Den kleinsten x Wert ermitteln
	c[0][0] = c[3][0] = c[4][0] = c[7][0] = m_center.x() - m_radius;
	// Den groessten x Wert ermitteln
	c[1][0] = c[2][0] = c[5][0] = c[6][0] = m_center.x() + m_radius;
	
	// Den kleinsten y Wert ermitteln
	c[2][1] = c[3][1] = c[6][1] = c[7][1] = m_center.y() - m_radius;
	// Den groessten y Wert ermitteln
	c[0][1] = c[1][1] = c[4][1] = c[5][1] = m_center.y() + m_radius;
		
	// Den kleinsten z Wert ermitteln
	c[4][2] = c[5][2] = c[6][2] = c[7][2] = m_center.z() - m_radius;
	// Den groessten z Wert ermitteln
	c[0][2] = c[1][2] = c[2][2] = c[3][2] = m_center.z() + m_radius;
	
	if (oi == 2)
	{
		std::cout << "z: " << m_center.z() + m_radius << ", " << c[0][2] << std::endl;
	}

	return c;
}
