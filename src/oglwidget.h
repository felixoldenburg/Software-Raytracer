#ifndef CCSOPENGL
#define CCSOPENGL

#include <QGLWidget>
#include <QtGui/QApplication>
#include <qevent.h>
#include <OpenGL/glu.h>

#include "octree.h"
#include "scene.h"
#include "raytracer.h"

/** RGBA-Farbwert */
typedef GLfloat CGColor4[4];
/** Punkt im 3D-Raum (homogene Koordinaten) */
typedef GLfloat CGPoint4D[4];
/** Punkt im 2D-Raum (homogene Koordinaten) */
typedef GLfloat CGPoint2D[2];

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Triangle;
class Sphere;
class Rect;

/**
 * Basisklasse fuer OpengGL Fenster.
 * - Initialisiert alle OpenGL relevanten
 *   Sachen.
 * - Drehfunktion mit der Maus
 * - Zoomfunktion mit dem Mausrad
 * - glPrint Funktion fuer 3D-Schrift
 */
class OglWidget : public QGLWidget
{
	Q_OBJECT

public:
	OglWidget(QWidget *parent = 0);
	virtual ~OglWidget(void);

	void setScene(Scene* scene) {
		//glDeleteLists(screenList, 1);
		this->scene = scene;
		//generateDisplayLists();
	}
	Scene* getScene() const { return scene; }
	Color **pixel;
	void setPixel(Color** pixel) { this->pixel = pixel; }

	bool getBoundingBoxes() const { return showBBoxes; }
	void setBoundingBoxes(bool visible) { showBBoxes = visible; }

	// Kann man hier auch protected slots verwenden?
public slots:
	void setXRotation(qint32 angle);
	void setYRotation(qint32 angle);
	void setZRotation(qint32 angle);

protected:

	void generateDisplayLists();

	// OpenGL 
	void initializeGL	();
	void paintGL		();
	void resizeGL		(qint32 width, qint32 height);

	// Events
	void mousePressEvent	(QMouseEvent *event);
	void mouseMoveEvent		(QMouseEvent *event);
	void wheelEvent			(QWheelEvent *event);
	void normalizeAngle		(qint32 *angle);

	// Initialisierung
	void initLight ();
        //virtual void generateDisplayLists(){}

	// Zeichnen
	void drawScene();
	void drawContent();
	
	void renderObject	(Object* o, bool box = false) const;
	void renderOctree	(const Octree* o) const;
	void renderTriangle	(Triangle* t, bool box) const;
	void renderSphere	(Sphere* s, bool box) const;
	void renderRect		(Rect* r, bool box) const;
	void renderCube		(const Cube &c) const;
	void drawRay(const Ray &r) const;
	void drawVertex(const Vector3D &p) const;
	void drawLine(const Vector3D &from, const Vector3D &to);
	void drawScreen();
	
	void ocIntersect(const Octree *octree, const Ray &ray);

	qint32 xRot;
	qint32 yRot;
	qint32 zRot;
	qint32 zZoom;
	QPoint lastPos;

	// Der zu zeichnende Octree
	//Octree* octree;
	
	int screenList;
	
	/// Projektion
	Scene* scene;

	// Gibt an, ob die Bounding Boxes gezeichnet werden sollen
	bool showBBoxes;
	
	GLUquadricObj *quadratic;
};

const qreal GL_NEAR = 0.01f;
const qreal GL_FAR  = 600.0f;

#endif
