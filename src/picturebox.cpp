#include "picturebox.h"
#include <QPainter>

PictureBox::PictureBox()
{
}

bool PictureBox::loadImage(const QString &fileName)
{
    bool res = picture.load(fileName);

    if (res)
        update();

    return res;
}

void PictureBox::paintEvent (QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, picture);
}
