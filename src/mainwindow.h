#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "oglwidget.h"
#include "picturebox.h"
#include "raytracer.h"
#include "scene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void createSettingPanel();
	
	//Scene* scene;
	RayTracer* tracer;

    OglWidget *ogl;
    QWidget *settingPanel;

    QLineEdit *txtResX;
    QLineEdit *txtResY;

    QPushButton *btnRender;

    PictureBox *m_pic;
    QPixmap *pix;
    QLabel *lbl;

};

#endif // MAINWINDOW_H

