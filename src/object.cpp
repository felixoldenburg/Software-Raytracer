#include "object.h"

#include <iostream>

using std::list;

/**
 * Erstellt eine Bounding Box welche alle Objekte
 * der Liste umschliesst.
 * @param objects Liste mit zu umschliessenden Objekten
 * @return Erzeugte Bounding Box
 */
Cube Object::getBoundingBox(const list<Object*> &objects)
{
	// Zwischenspeichern der Extremwerte
	VTYPE minX, minY, minZ;
	VTYPE maxX, maxY, maxZ;
	minX = minY = minZ = objects.empty() ? 0 : MAX_VALUE;
	maxX = maxY = maxZ = objects.empty() ? 0 : MIN_VALUE;

	Cube box;
	bool isSphere = false;

	// Alle Objekte durchlaufen
	list<Object*>::const_iterator i;
	for(i = objects.begin(); i != objects.end(); ++i)
	{
		// Bounding Box fuer aktuelles Objekt ermitteln
		box = (*i)->getBoundingBox();
		
		// Wird ein (neuer) Extremwert gefunden: speichern
		minX = MIN(minX, box[0].x());
		maxX = MAX(maxX, box[1].x());
		minY = MIN(minY, box[2].y());
		maxY = MAX(maxY, box[0].y());
		minZ = MIN(minZ, box[4].z());
		maxZ = MAX(maxZ, box[0].z());
		
		if ((*i)->isSphere())
			isSphere = true;
	}
	
	// Erstellen der Bounding Box aus den Extremwerten
	// Kleinster x Wert
	box[0][0] = box[3][0] = box[4][0] = box[7][0] = minX;
	// Groesster x Wert
	box[1][0] = box[2][0] = box[5][0] = box[6][0] = maxX;
	
	// Kleinster y Wert
	box[2][1] = box[3][1] = box[6][1] = box[7][1] = minY;
	// Groesster y Wert
	box[0][1] = box[1][1] = box[4][1] = box[5][1] = maxY;
		
	// Kleinster z Wert
	box[4][2] = box[5][2] = box[6][2] = box[7][2] = minZ;
	// Groesster z Wert
	box[0][2] = box[1][2] = box[2][2] = box[3][2] = maxZ;
	
	if (isSphere)
		std::cout << "maxZ: " << maxZ << std::endl;
	
	return box;
}