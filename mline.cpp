#include "mLine.h"
#include <QPainter>
#include <QQuickItem>

MLine::MLine(QQuickItem *parent)
    :QQuickPaintedItem(parent),m_color("black"),m_xStart(10), m_yStart(10),m_xEnd(100-10), m_yEnd(100-10), m_radius(10)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

QString MLine::name() const
{
    return m_name;
}

void MLine::setName (const QString &name)
{
    m_name=name;
}

QColor MLine::color() const
{
    return m_color;
}

void MLine::setColor (const QColor &color)
{
    m_color = color;
    update ();
}

double MLine::xStart() const
{
    return m_xStart;
}

void MLine::setXStart (const double &xStart)
{
    m_xStart = xStart;
}

double MLine::yStart() const
{
    return m_yStart;
}

void MLine::setYStart (const double &yStart)
{
    m_yStart = yStart;
}
double MLine::xEnd() const
{
    return m_xEnd;
}

void MLine::setXEnd (const double &xEnd)
{
    m_xStart = xEnd;
}

double MLine::yEnd() const
{
    return m_yEnd;
}

void MLine::setYEnd (const double &yEnd)
{
    m_yStart = yEnd;
}

void MLine::paint (QPainter *painter)
{
    QPen pen(m_color,2);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    line = new QLineF(m_xStart, m_yStart, m_xEnd, m_yEnd);
    pStart = new QPointF(m_xStart, m_yStart);
    pEnd = new QPointF(m_xEnd, m_yEnd);

    painter->drawLine(*line);

    pen.setColor ("red"); pen.setWidth (m_radius);
    painter->setPen (pen);
    painter->drawPoint(*pStart);
    painter->drawPoint(*pEnd);
    //    painter->drawEllipse (QPoint(m_xStart, m_yStart), m_radius, m_radius);
    //    painter->drawEllipse (QPoint(m_xEnd, m_yEnd), m_radius, m_radius);
    setWidth(m_xEnd-m_xStart+m_radius*2); setHeight(m_yEnd-m_yStart+m_radius*2);
}

void MLine::mousePressEvent (QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if (QRectF(m_xStart-m_radius, m_yStart-m_radius, m_radius*2, m_radius*2).contains (event->pos()))
        {
            movable = 1;
            dragPosition = event->globalPos ()-QPoint(x(),y());
            MLine::setColor ("orange");
            event->accept();
        }
    }
}

void MLine::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton & (movable==1)){
        double tempX = event->globalX ()-dragPosition.x ();
        double tempY = event->globalY ()-dragPosition.y ();
        if(tempX>0 && tempX<parentItem()->width()-this->width ())
            setX(tempX);
        if(tempY>0 && tempY<parentItem ()->height ()-this->height ())
            setY(tempY);
        event->accept();
    }
}

void MLine::mouseReleaseEvent (QMouseEvent *event)
{
    Q_UNUSED(event);
    MLine::setColor ("blue");
    movable = 0;
    event->accept ();
}
