#include "octree.h"

#include <sstream>

using std::list;
using std::string;

/**
 * Nimmt Liste mit Objekten fuer die Octreeerstellung entgegen
 * @param objects Liste mit Objekten
 * @param maxObjects Maximale Anzahl an Objekten im Knoten
 */
Octree::Octree(list<Object*> &objects)
			: box(box), alreadySplit(false)
{
	initChildren();
	
	startBSP(objects);
}

/**
 * Privater Konstruktor fuer die BSP.
 * @param box Bounding Box dieses Knotens
 */
Octree::Octree(const Cube &box) : box(box), alreadySplit(false)
{
	initChildren();
}

void Octree::initChildren()
{
	for (int i = 0; i < 8; ++i)
		children[i] = NULL;
}

/**
 * Loeschen aller Elemente und Unterknoten.
 */
Octree::~Octree()
{
	// Speicherfreigabe aller Objekte dieses Knotens
	list<Object*>::iterator i;
	for(i = objects.begin(); i != objects.end(); ++i)
		delete *i;
	objects.clear();
	
	// Speicherfreigabe der Unterknoten
	for (int i = 0; i < 8; ++i)
		delete children[i];
}

/**
 * Binary Space Partitioning
 * @param objects Liste mit Objekten 
 * fuer raeumliche Aufteilung
 */
void Octree::startBSP(list<Object*> &objects)
{
	// Bounding Box fuer Objektmenge ermitteln
	box = Object::getBoundingBox(objects);

	// Fuer jedes Objekt
	list<Object*>::iterator i;
	for(i = objects.begin(); i != objects.end(); ++i)
	{
		backupList.push_back(*i);
		if (!
		divide(*i))
			qDebug("ERRROROROROROORROOROROROR");
		objects.erase(i);
	}
	
	removeEmptyLeaves();
	
	#ifdef QT_CORE_LIB
	qDebug() << toString().c_str();
	#endif
}

bool Octree::divide(Object *o)
{
	bool result = false;

	if (o->isInsideOfCube(box))
	{
		result = true;
		
		// Unterteilung in acht Unterknoten
		if (!alreadySplit)
			alreadySplit = splitCube(subCubes);
			
		bool sub = false;
		// Rekursion fuer jeden Unterknoten
		for (int c = 0; c < 8; ++c)
		{
			if (children[c] == NULL)
				children[c] = new Octree(subCubes[c]);
				
			sub = sub || children[c]->divide(o);
		}
		
		if (!sub)
			objects.push_back(o);
	}
	
	return result;
}

void Octree::removeEmptyLeaves()
{
	bool allEmpty = true;
	for (int c = 0; c < 8 && allEmpty; ++c)
		if (children[c] != NULL)
			allEmpty = allEmpty && children[c]->objects.empty();
	
	for (int c = 0; c < 8; ++c)
		if (children[c] != NULL)
		{
			if (allEmpty)
			{
				delete children[c];
				children[c] = NULL;
			}
			else
				children[c]->removeEmptyLeaves();
		}
}

/**
 * Gibt an, ob es sich beim diesem Element
 * um ein Blatt handelt.
 * @return true Wenn Element keine Unterknoten besitzt
 */
bool Octree::isLeave() const
{
	for (int i = 0; i < 8; ++i)
		if (children[i] != NULL)
			return false;
	
	return true;
}

/**
 * Unterteilt die Bounding Box dieses Knotens in
 * 8 weitere Segmente.
 * *
 * cube[8] :
 *    4-------5
 *   /|      /|
 *  0-------1 |
 *  | |     | |
 *  | |7----|-|6
 *  |/      |/
 *  3-------2
 * @param subCubes Ergebnis der Unterteilung
 * @return true
 */
bool Octree::splitCube(Cube *subCubes)
{
    // Mittelpunktkoordinaten des Wuerfels
    VTYPE x,y,z;

    x = box[0].x();
    x = x + (box[1].x() - x) / 2.f;

    y = box[3].y();
    y = y + (box[0].y() - y) / 2.f;

    z = box[4].z();
    z = z + (box[0].z() - z) / 2.f;

#define MODZ(x, b) (b?x.modZ(z):x)

    bool b = false;
    for (int i=0, i1=0, i2=0; i < 4; ++i, b=i!=0, i2=(i%2)*4)
    {
        if (i == 2) i1 = 4;
        if (i == 3) z = box[4].z();

        subCubes[i1+0][i2+0] = MODZ(Vector3D(box[0]), b);
        subCubes[i1+0][i2+1] = MODZ((subCubes[i1+1][i2+0] = box[0]).modX(x), b);
        subCubes[i1+0][i2+2] = subCubes[i1+1][i2+3] = subCubes[i1+2][i2+0]
							= MODZ((subCubes[i1+3][i2+1] = box[2]).modX(x).modY(y), b);
        subCubes[i1+0][i2+3] = MODZ((subCubes[i1+3][i2+0] = box[0]).modY(y), b);

        subCubes[i1+1][i2+1] = MODZ(Vector3D(box[1]), b);
        subCubes[i1+1][i2+2] = MODZ((subCubes[i1+2][i2+1] = box[1]).modY(y), b);

        subCubes[i1+2][i2+2] = MODZ(Vector3D(box[2]), b);
        subCubes[i1+2][i2+3] = MODZ((subCubes[i1+3][i2+2] = box[3]).modX(x), b);

        subCubes[i1+3][i2+3] = MODZ(Vector3D(box[3]), b);
    }
	
	return true;
}

string Octree::toString(int depth /* = 0 */) const
{
	std::stringstream buffer, indent;
	for(int i = 0; i < depth; ++i)
		indent << "\t";
		
	buffer << "O(" << depth << "): ";
	
	if (objects.empty())
		buffer << "---";
	else
	{
		list<Object*>::const_iterator i;
		for(i = objects.begin(); i != objects.end(); ++i)
			buffer << (*i)->toString();			
	}
	buffer << "\n";
		
	for (int i = 0; i < 8; ++i)
	{
		buffer << indent.str() << "c[" << i << "]:"
			<< (children[i] != NULL ? children[i]->toString(depth+1) : " --|");
		buffer << "\n";
	}
	
	return buffer.str();
}
