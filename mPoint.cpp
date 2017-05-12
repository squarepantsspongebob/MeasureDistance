#include "MPoint.h"
#include <QPainter>
#include <QQuickItem>

MPoint::MPoint(QQuickItem *parent)
    :QQuickPaintedItem(parent)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

QString MPoint::name() const
{
    return m_name;
}

void MPoint::setName (const QString &name)
{
    m_name=name;
}

QColor MPoint::color() const
{
    return m_color;
}

void MPoint::setColor (const QColor &color)
{
    m_color = color;
    update ();
}

double MPoint::xCenter() const
{
    return m_xCenter;
}

void MPoint::setXCenter (const double &xCenter)
{
    m_xCenter = xCenter;
}

double MPoint::yCenter() const
{
    return m_yCenter;
}

void MPoint::setYCenter (const double &yCenter)
{
    m_yCenter = yCenter;
}

void MPoint::paint (QPainter *painter)
{
    QPen pen(m_color,2);
    //    pen.setDashPattern(Qt::DashLine);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
//    painter->drawEllipse (QPoint(m_xCenter, m_yCenter),m_radius,m_radius);
    painter->drawEllipse (QPoint(m_xCenter, m_yCenter),10,10);
}

void MPoint::mousePressEvent (QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        dragPosition = event->globalPos ()-QPoint(x(),y());
        event->accept();
    }
}

void MPoint::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        qDebug()<<"move";
        double tempX = event->globalPos ().x ()-dragPosition.x ();
        double tempY = event->globalPos ().y ()-dragPosition.y ();
        if(tempX>0 && tempX<parentItem()->width()-this->width ())
            setX(event->globalPos().x ()-dragPosition.x ());
        if(tempY>0 && tempY<parentItem ()->height ()-this->height ())
            setY(event->globalPos().y ()-dragPosition.y ());
        event->accept();
    }
}
