#include "mainwindow.h"
#include <QDebug>

#include "octree.h"
#include "triangle.h"
#include "rect.h"
#include "sphere.h"
#include "lightsource.h"

#include <list>

using std::list;

Scene* createTestScene()
{
	list<Object*> objs;
	list<Lightsource*> lights;
	
	Lightsource *pointLight = new Lightsource();
	// Position ~mittig ueber allen Objekten
	pointLight->setPos(Vector3D(-10, 15, 10));
	// Roetliches Licht
	pointLight->setColor(Color(1, 1, 1));
	lights.push_back(pointLight);
	
	//Triangle* t = new Triangle(Vector3D(0,0,-1), Vector3D(0,1,-1), Vector3D(1,0,-1));
	Triangle* t = new Triangle(Vector3D(0,0,-10), Vector3D(10,0,-10), Vector3D(0,4,-10));
	Rect *r = new Rect(Vector3D(0,0,10), Vector3D(10,0,0), Vector3D(10,10,10), Vector3D(0,10,10));
	Sphere *sp = new Sphere(Vector3D(-20, 10, 0), 4);
	Sphere *s2 = new Sphere(Vector3D(-12, 5, 6), 0.91f);
	Sphere *s3 = new Sphere(Vector3D(-10, 5, 6), 0.91f);
	
	//Vector3D a(0,1,2), b(3,4,5), c(0,0,0);	//	Triangle *d = new Triangle(a, b, c);
	
	//objs.push_back(d);
	objs.push_back(t);
	//objs.push_back(r);
	//objs.push_back(sp);
	//objs.push_back(s2);
	//objs.push_back(s3);
	
	
	Scene *scene = new Scene(objs);
	scene->setLights(lights);
	
	Vector3D s(-30, 0, 30);
	Vector3D u(12, 0, 10);
	Vector3D v(0, 10, 0);
	Vector3D eye(-36, 5, 54);
	Vector3D up(0, 1, 0);
	int xres = 300;
	int yres = 300;
	
	scene->setS(s);
	scene->setEye(eye);
	scene->setU(u);
	scene->setV(v);
	scene->setXRes(xres);
	scene->setYRes(yres);
	scene->setUpVector(up);
	
	return scene;
}

/**
 * Erstellt einen Octree zum Testen.
 * Wird im dtor von mainwindow wieder geloescht.
 */
Octree* createTestOctree()
{	
	return NULL;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ogl = new OglWidget(this);
	
	tracer = new RayTracer(createTestScene());
	tracer->start();

	ogl->setScene(tracer->getScene());
	ogl->setPixel(tracer->getPixel());
	
    m_pic = new PictureBox();
    //qDebug() << m_pic->loadImage("/Users/FOldenburg/CGRayTracer/test.bmp");

    createSettingPanel();
    //QVBoxLayout *ltInfoLeft = new QVBoxLayout();

	QImage im(tracer->getScene()->getXRes(), tracer->getScene()->getYRes(), QImage::Format_RGB32);
	Color** pixxel = tracer->getPixel();
	// Fuer jeden Pixel
	int xres = tracer->getScene()->getXRes();
	int yres = tracer->getScene()->getYRes();
	for(int x = 0; x < xres; ++x)
		for(int y = 0; y < yres; ++y)
		{
			QRgb value = qRgb(pixxel[y][x][0]*255,pixxel[y][x][1]*255,pixxel[y][x][2]*255); // 0xffbd952
			im.setPixel(QPoint(x,yres-1-y), value);
		
		}

    //pix = new QPixmap("/Users/FOldenburg/CGRayTracer/test.jpg");
	pix = new QPixmap();
	*pix = QPixmap::fromImage(im);
    lbl = new QLabel("ASD");
    lbl->setPixmap(*pix);
	

    QSplitter *splMain = new QSplitter(Qt::Horizontal);
    splMain->setStyle(new QMotifStyle());
    splMain->addWidget(
            ogl
			//lbl
            );
    splMain->addWidget(settingPanel);

    QList<int> lst;
    lst << int(0.8 * width());
    lst << int(0.2 * width());
    splMain->setSizes(lst);

    setCentralWidget(splMain);

    resize(1024, 786);
}

void MainWindow::createSettingPanel()
{
    QLabel *lblResolution = new QLabel(tr("Auflösung"));

    QLabel *lblResX = new QLabel(tr("X:"));
    QLabel *lblResY = new QLabel(tr("Y:"));

    txtResX = new QLineEdit(this);
    txtResY = new QLineEdit(this);
    QHBoxLayout *hBoxRes = new QHBoxLayout();
    hBoxRes->addWidget(lblResX);
    hBoxRes->addWidget(txtResX);
    hBoxRes->addWidget(lblResY);
    hBoxRes->addWidget(txtResY);
    //QWidget *wdtRes = new QWidget();
    //wdtRes->setLayout(hBoxRes);

    QVBoxLayout *vBoxRes = new QVBoxLayout();
    vBoxRes->addWidget(lblResolution);
    vBoxRes->addLayout(hBoxRes);

    btnRender = new QPushButton(tr("Rendern"));

    QVBoxLayout *settingBox = new QVBoxLayout();
    settingBox->addLayout(vBoxRes);
    settingBox->addStretch();
    settingBox->addWidget(btnRender);

    settingPanel = new QWidget();
    settingPanel->setLayout(settingBox);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    statusBar()->showMessage(
            QString("%1, %2").arg(event->size().width()).arg(event->size().height()));
}

MainWindow::~MainWindow()
{
	delete tracer;
}
