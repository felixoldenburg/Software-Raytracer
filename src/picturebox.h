#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QWidget>
#include <QtGui>

class PictureBox : public QWidget
{
public:
    PictureBox();

    bool loadImage(const QString &fileName);

protected:
    virtual void paintEvent (QPaintEvent *event);

    QPixmap picture;
};

#endif // PICTUREBOX_H
