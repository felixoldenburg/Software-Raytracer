#include "oglwidget.h"
#include "triangle.h"
#include "sphere.h"
#include "rect.h"
#include "object.h"
#include "cube.h"

#include <cmath>
#include <list>

using std::list;

namespace {

	// Zeichnen einer Kugel
	// Quelle: OpenGL red book (chapter 2)
	#define X .525731112119133606 
	#define Z .850650808352039932

	static GLfloat vdata[12][3] = {    
		{-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
		{0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
		{Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
	};
	static GLuint tindices[20][3] = { 
		{0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
		{8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
		{7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
		{6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

	void normalize(GLfloat *a) {
		GLfloat d=sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
		a[0]/=d; a[1]/=d; a[2]/=d;
	}

	void drawtri(GLfloat *a, GLfloat *b, GLfloat *c, int div, float r) {
		if (div<=0) {
			glNormal3fv(a); glVertex3f(a[0]*r, a[1]*r, a[2]*r);
			glNormal3fv(b); glVertex3f(b[0]*r, b[1]*r, b[2]*r);
			glNormal3fv(c); glVertex3f(c[0]*r, c[1]*r, c[2]*r);
		} else {
			GLfloat ab[3], ac[3], bc[3];
			for (int i=0;i<3;i++) {
				ab[i]=(a[i]+b[i])/2;
				ac[i]=(a[i]+c[i])/2;
				bc[i]=(b[i]+c[i])/2;
			}
			normalize(ab); normalize(ac); normalize(bc);
			drawtri(a, ab, ac, div-1, r);
			drawtri(b, bc, ab, div-1, r);
			drawtri(c, ac, bc, div-1, r);
			drawtri(ab, bc, ac, div-1, r);  //<--Comment this line and sphere looks really cool!
		}  
	}

	void drawsphere(int ndiv, float radius=1.0) {
		glBegin(GL_TRIANGLES);
		for (int i=0;i<20;i++)
			drawtri(vdata[tindices[i][0]], vdata[tindices[i][1]], vdata[tindices[i][2]], ndiv, radius);
		glEnd();
	}
};

OglWidget::OglWidget(QWidget *parent)
			: QGLWidget(parent),
			xRot(0),
			yRot(0),
			zRot(0),
			zZoom(-150),
			scene(NULL),
			showBBoxes(false)
{
	// Antialiasing
        if (1) {
		QGLFormat f = QGLFormat::defaultFormat();
		f.setSampleBuffers(true);
		setFormat(f);
	}

	setFocusPolicy(Qt::ClickFocus);

	// True: Mouse event fires, without pressing mouse buttons, too.
	setMouseTracking(true);
}

OglWidget::~OglWidget(void)
{
	makeCurrent();
}

void OglWidget::setXRotation(qint32 angle)
{
	normalizeAngle(&angle);
	if (angle != xRot) {
		xRot = angle;
		updateGL();
	}
}

void OglWidget::setYRotation(qint32 angle)
{
	normalizeAngle(&angle);
	if (angle != yRot) {
		yRot = angle;
		updateGL();
	}
}

void OglWidget::setZRotation(qint32 angle)
{
	normalizeAngle(&angle);
	if (angle != zRot) {
		zRot = angle;
		updateGL();
	}
}

void OglWidget::generateDisplayLists()
{
	screenList = glGenLists(1);
	glNewList(screenList, GL_COMPILE);
		drawScreen();
	glEndList();
}

void OglWidget::initializeGL()
{
	/* Standard-OS-Grauton */
	QColor color = QColor(255,255,255);
			//QApplication::palette().color(QPalette::Window);

	qglClearColor(color);

	//generateDisplayLists();

	// Farbverlaeufe aktivieren
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	// Front-/Rueck-Seite einer Flaeche
	// nicht mitzeichnen.
	//glEnable(GL_CULL_FACE);

	setAutoBufferSwap(false);

	//initLight();

	// Blending einstellen
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricDrawStyle(quadratic, GLU_LINE);

	// Drahtgitter- oder Punkte-Modus
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void OglWidget::paintGL()
{
	drawScene();

	// Tauschen des Front- und Back-Buffers
	swapBuffers();
}

/*
void OglWidget::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glTranslated(0.0, 0.0, zZoom);

	glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotated(zRot / 16.0, 0.0, 0.0, 1.0);

	drawContent();

	glPopMatrix();
}*/

void OglWidget::resizeGL(qint32 width, qint32 height)
{
	const float fAspect = ((double)width/(double)height);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, fAspect, GL_NEAR, GL_FAR);
	glMatrixMode(GL_MODELVIEW);
}

/**
 * Initialisierung der Lichtquellen.
 * Setzt Eigenschaften der Lichtquellen (Farbe, Oeffnungswinkel, ...)
 */
void OglWidget::initLight ()
{
  /* Farbe der ersten Lichtquelle */
  CGColor4 lightColor0[3] =
    { {0.5f, 0.5f, 0.5f, 1.0f},
      {0.4f, 0.4f, 0.4f, 1.0f},
      {0.77f, 0.77f, 0.77f, 1.0f}
  };

  CGPoint4D lightPos0 = { 0.0f, 0.0f, 0.0f, 1.0f };

  glEnable (GL_LIGHTING);

  /* Position der ersten Lichtquelle setzen */
  glLightfv (GL_LIGHT0, GL_POSITION, lightPos0);
  /* Erste Lichtquelle aktivieren */
  glEnable (GL_LIGHT0);

  /* Farbe der ersten Lichtquelle setzen */
  glLightfv (GL_LIGHT0, GL_AMBIENT, lightColor0[0]);
  glLightfv (GL_LIGHT0, GL_DIFFUSE, lightColor0[1]);
  glLightfv (GL_LIGHT0, GL_SPECULAR, lightColor0[2]);

  // Mit glColor** gesetzte Farbwerte werden bei der
  // Lichtberechnung beruecksichtigt.
  glEnable(GL_COLOR_MATERIAL);
}

/**
 * Zeichnet die OGL-Szene
 */
void OglWidget::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

        //qDebug("zoom: %d", zZoom);
        //qDebug("%d %d %d", xRot, yRot, zRot);
    glTranslated(0.0, 0.0, zZoom);

    //glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);


    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);

        drawContent();

    glPopMatrix();
}

void OglWidget::drawLine(const Vector3D &from, const Vector3D &to)
{
	glBegin(GL_LINES);
		glVertex3dv(from.xyz());
		glVertex3dv(to.xyz());
	glEnd();
}

void OglWidget::ocIntersect(const Octree *octree, const Ray &ray)
{
	if (octree != NULL)
	{		
		Vector3D res;
		//glColor3ub(255, 0 , 0);
		//	renderCube(*octree->getBoundingBox());
		if (octree->getBoundingBox()->intersectsRay(ray, &res))
		{
			glColor3ub(255, 0 , 0);
			//renderCube(*octree->getBoundingBox());
			//drawVertex(res);
		}
		else
		{
			//glColor3ub(255, 255 , 0);
			//renderCube(*octree->getBoundingBox());
		}
		
		// Rendern der Kindelemente
		if (!octree->isLeave())
		{
			const Octree* const *children = octree->getChildren();
			for (int i = 0; i < 8; ++i)
				if (children[i] != NULL)
					ocIntersect(children[i], ray);
		}
		
		//if (octree->isLeave() && )
		//renderCube(*octree->getBoundingBox());
	}	
}

void OglWidget::drawScreen()
{
	if (scene != NULL)
	{
		Vector3D s = scene->getS();
		Vector3D u = scene->getU();
		Vector3D v = scene->getV();
		Vector3D eye = scene->getEye();
		int xres = scene->getXRes();
		int yres = scene->getYRes();
		drawVertex(s);
		drawLine(s, s+u);
		drawLine(s, s+v);
		drawVertex(eye);
		
		// Gitter der Projektionsebene
		Vector3D xVec, yVec;
		glColor3ub(200, 200, 200);
		for (int x = 1; x < xres+1; ++x)
			for (int y = 1; y < yres+1; ++y)
			{
				xVec = u*((float)x/xres);
				yVec = v*((float)y/yres);
				//drawLine(s + yVec, s + u + yVec);
				//drawLine(s + v + xVec, s + xVec);
			}
		
		// Viewing Frustum strahlen, nur zur Orientierung
		Vector3D s1, s2, s3, s4;
		s1 = eye.vectorTo(s)*10;
		s2 = eye.vectorTo(s+u)*10;
		s3 = eye.vectorTo(s+v)*10;
		s4 = eye.vectorTo(s+u+v)*10;
		
		glColor3ub(200, 100, 100);
		drawLine(eye, eye+s1);
		drawLine(eye, eye+s2);
		drawLine(eye, eye+s3);
		drawLine(eye, eye+s4);
		
		Ray r;
		r.point = eye;
		
		Vector3D res;
		list<Object*> *objects = &scene->getOctree()->backupList;// ->getObjects();
		list<Lightsource*> *lights = scene->getLights();
		Sphere lightSp(lights->front()->pos(), 0.2f);
		renderSphere(&lightSp, false);
		int x = 0;
		int y =173;
		for(int x = 0; x < xres; ++x)
			for(int y = 0; y < yres; ++y)
			{
				Vector3D tp = s + u*((x+.5f)/xres) + v * ((y+.5f)/yres);
				//drawVertex(tp);
				
				r.dir = eye.vectorTo(tp	);
				
				/*list<Object*>::const_iterator it;
				for(it = objects->begin(); it != objects->end(); ++it)
					if ((*it)->intersectsRay(r, &res) && (x%3==0) && (y%3==0))
					{
						//drawVertex(res);
						
						Ray rr = {res, (*it)->getNormal(res)};
						if (x == 51 && y == 189)
						{
							drawRay(rr);
							drawLine(eye, res);
						}
					}*/
				
				  
				//Ray ru;
				//ru.point = Vector3D(-30, 4, 1);
				//ru.dir = Vector3D(1, 0.3, 0);
				//ocIntersect(scene->getOctree(), r);
				//drawRay(r);
				
				
				Vector3D a = s + u*((x+0.f)/xres) + v * ((y+1.f)/yres);
				Vector3D b = s + u*((x+0.f)/xres) + v * ((y+0.f)/yres);
				Vector3D c = s + u*((x+1.f)/xres) + v * ((y+0.f)/yres);
				Vector3D d = s + u*((x+1.f)/xres) + v * ((y+1.f)/yres);
				
				
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBegin(GL_QUADS);
					
					glColor3f(pixel[y][x][0], pixel[y][x][1], pixel[y][x][2]);
					//glColor3ub(0,255,0);
					glVertex3dv(a.xyz());
					glVertex3dv(b.xyz());
					glVertex3dv(c.xyz());
					glVertex3dv(d.xyz());
				glEnd();
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				//qDebug() << pixel[y][x][0] << pixel[y][x][1] << pixel[y][x][2];
			}
	}
}

void OglWidget::drawContent()
{
    // Namestack initialisieren
    //glInitNames();
    // Dummy-ID pushen, damit glLoadIdentity() funktioniert
    //glPushName(0);

#define RANGE 500
    // Koordinatenachsen
    glBegin(GL_LINES);
    // X-Achse
    glColor3ub(0, 0, 255);
    glVertex3f(-RANGE, 0, 0);
    glVertex3f(+RANGE, 0, 0);
    // Y-Achse
    glColor3ub(255, 0, 0);
    glVertex3f(0, -RANGE, 0);
    glVertex3f(0, +RANGE, 0);
    // Z-Achse
    glColor3ub(0, 255, 0);
    glVertex3f(0, 0, -RANGE);
    glVertex3f(0, 0, +RANGE);
    glEnd();
	
	//glColor3ub(255, 0, 0);
	//drawsphere(5);
	//gluSphere(quadratic,5,15,15);
	//glTranslatef(4,2,1);
	//gluSphere(quadratic,2,15,15);
	//gluDisk(quadratic,0.5f,1.5f,32,32);
	//Triangle* t = new Triangle(Vector3D(0,0,-10), Vector3D(0,10,-10), Vector3D(10,0,-10));
	//Rect *r = new Rect(Vector3D(0,0,0), Vector3D(0,10,0), Vector3D(10,10,0), Vector3D(10,0,-10));
	//renderTriangle(t);
	//delete t;
	//renderRect(r);
	renderOctree(scene->getOctree());
	glColor3ub(0, 0, 0);
	
	Ray r; r.point = Vector3D(0,0,10);
	r.dir = Vector3D(1,1,1);
	drawRay(r);
	
	//glCallList(screenList);
	drawScreen();
}

/**
 * Rekursives Rendern des Octree Baums.
 */
void OglWidget::renderOctree(const Octree* octree) const
{
	if (octree != NULL)
	{
		const list<Object*> *objects = octree->getObjects();
		
		if (objects != NULL)
		{
			// Rendern der Objekte
			list<Object*>::const_iterator it;
			for(it = objects->begin(); it != objects->end(); ++it)
				renderObject(*it, false);
		}
		
		// Rendern der Kindelemente
		if (!octree->isLeave())
		{
			const Octree* const *children = octree->getChildren();
			for (int i = 0; i < 8; ++i)
				if (children[i] != NULL)
					renderOctree(children[i]);
		}
		
		//if (octree->isLeave() && )
		glColor3ub(200, 200, 200);
		//renderCube(*octree->getBoundingBox());
	}
}

void OglWidget::renderObject(Object* o, bool box /* = false */) const
{
		if (o->isTriangle())
			renderTriangle(static_cast<Triangle*>(o), box);
		else if (o->isSphere())
			renderSphere(static_cast<Sphere*>(o), box);
		else if (o->isRect())
			renderRect(static_cast<Rect*>(o), box);
}

void OglWidget::renderCube(const Cube &c) const
{
	glBegin(GL_QUADS);
		glVertex3dv(c[0].xyz()); // Front
		glVertex3dv(c[1].xyz());
		glVertex3dv(c[2].xyz());
		glVertex3dv(c[3].xyz());
		glVertex3dv(c[5].xyz()); // Back
		glVertex3dv(c[6].xyz());
		glVertex3dv(c[7].xyz());
		glVertex3dv(c[4].xyz());
		glVertex3dv(c[4].xyz()); // Top
		glVertex3dv(c[0].xyz());
		glVertex3dv(c[1].xyz());
		glVertex3dv(c[5].xyz());
		glVertex3dv(c[3].xyz()); // Bottom
		glVertex3dv(c[2].xyz());
		glVertex3dv(c[6].xyz());
		glVertex3dv(c[7].xyz());
		glVertex3dv(c[4].xyz()); // Left
		glVertex3dv(c[0].xyz());
		glVertex3dv(c[3].xyz());
		glVertex3dv(c[7].xyz());
		glVertex3dv(c[1].xyz()); // Right
		glVertex3dv(c[2].xyz());
		glVertex3dv(c[6].xyz());
		glVertex3dv(c[5].xyz());
	glEnd();
}

void OglWidget::drawVertex(const Vector3D &p) const
{
	glPushMatrix();
		glTranslatef(p.x(), p.y(), p.z());
		gluSphere(quadratic, 0.1f , 8, 8);
	glPopMatrix();
}

void OglWidget::drawRay(const Ray &r) const
{
	drawVertex(r.point);
	Vector3D dir = r.dir;
	dir = dir.normalize();
	dir *= 20;
	Vector3D end = r.point + dir; 
	//glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3dv(r.point.xyz());
	glVertex3dv(end.xyz());
	glEnd();
	//glLineWidth(1);
	
	end = r.point + dir*5;
	glLineStipple(2, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex3dv(r.point.xyz());
	glVertex3dv(end.xyz());
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

void OglWidget::renderTriangle(Triangle* t, bool box) const
{
	glBegin(GL_TRIANGLES);
		glColor3ub(0, 255, 0);
        glVertex3dv(t->A().xyz());
        glVertex3dv(t->B().xyz());
        glVertex3dv(t->C().xyz());
    glEnd();
	
	if (box)
		renderCube(t->getBoundingBox());
}

void OglWidget::renderSphere(Sphere* s, bool box) const
{
	glColor3ub(0, 0, 255);
	glPushMatrix();
		glTranslatef(s->center().x(), s->center().y(), s->center().z());
		gluSphere(quadratic, s->radius() , 8, 8);
	glPopMatrix();
	
	if (box)
		renderCube(s->getBoundingBox());
}

void OglWidget::renderRect(Rect* r, bool box) const
{
	glBegin(GL_POLYGON);
		glColor3ub(255, 0, 0);
		glVertex3dv(r->A().xyz());
		glVertex3dv(r->B().xyz());
		glVertex3dv(r->C().xyz());
		glVertex3dv(r->D().xyz());
		glVertex3dv(r->A().xyz());
	glEnd();

	if (box)
		renderCube(r->getBoundingBox());
}

//void OglWidget::renderScene(const QList<

void OglWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

void OglWidget::wheelEvent(QWheelEvent *event)
{
	if (event->orientation() == Qt::Vertical) {
		// Zoom-Wert inkre-/dekrementieren
		zZoom += (event->delta() > 0) ? 5 : -5;
		//qDebug("zoomie zoomie is: %d", zZoom);
		// Update ausloesen
		emit updateGL();
	}
}


void OglWidget::mouseMoveEvent(QMouseEvent *event)
{
	const qint32 dx = event->x() - lastPos.x();
	const qint32 dy = event->y() - lastPos.y();

	quint8 acht = 8;
	if (event->buttons() & Qt::LeftButton) {

		setXRotation(xRot + acht * dy);
		setYRotation(yRot + acht * dx);

		lastPos = event->pos();
	}
	// Rotieren mit der rechten Maustaste:
	else if (event->buttons() & Qt::RightButton) {
		//setXRotation(xRot + acht * dy);
		//setZRotation(zRot + acht * dx);
	}

}

void OglWidget::normalizeAngle(qint32 *angle)
{
	while (*angle < 0)
		*angle += 360 * 16;
	while (*angle > 360 * 16)
		*angle -= 360 * 16;
}

