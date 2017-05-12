#include "mLine.h"
#include <QPainter>
#include <QQuickItem>

MLine::MLine(QQuickItem *parent)
    :QQuickPaintedItem(parent),m_color("black"),m_xStart(5), m_yStart(5),m_xEnd(100-5), m_yEnd(100-5), m_radius(10)
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
    m_xEnd = xEnd;
}

double MLine::yEnd() const
{
    return m_yEnd;
}

void MLine::setYEnd (const double &yEnd)
{
    m_yEnd = yEnd;
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
    setWidth(abs(m_xEnd-m_xStart)+m_radius); setHeight(abs(m_yEnd-m_yStart)+m_radius);
}

void MLine::mousePressEvent (QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if (QRectF(m_xStart-m_radius/2, m_yStart-m_radius/2, m_radius, m_radius).contains (event->pos()))
        {
            movable = 1;
            preXY=QPointF(x(),y());
            dragPosition = event->globalPos ()-QPointF(m_xStart,m_yStart);
            MLine::setColor ("orange");
            event->accept();
        }
        else if(QRectF(m_xEnd-m_radius/2, m_yEnd-m_radius/2, m_radius, m_radius).contains (event->pos()))
        {
            movable = 2;
            preXY=QPointF(x(),y());
            dragPosition = event->globalPos ()-QPointF(m_xEnd,m_yEnd);
            MLine::setColor("orange");
            event->accept ();
        }
        else {
            movable=3;
            preXY = QPointF(x(),y());
            dragPosition = event->globalPos ()-QPointF(x(),y());
            MLine::setColor("orange");
            event->accept ();
        }
    }
}

void MLine::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if(movable==1){
            double tempxstart = event->globalX ()-dragPosition.x ()+preXY.x ();
            double tempystart = event->globalY ()-dragPosition.y ()+preXY.y ();
            double tempxend = m_xEnd+x();
            double tempyend = m_yEnd+y();
            double newx=tempxstart<tempxend?tempxstart-m_radius/2:tempxend-m_radius/2;
            double newy=tempystart<tempyend?tempystart-m_radius/2:tempyend-m_radius/2;
            if (newx>0 & newx+abs(tempxend-tempxstart)+m_radius<parentItem ()->width ())
            {
                setX(newx);
                setXEnd(tempxend-x());
                setXStart(tempxstart-x());
            }
            if(newy>0 & newy+abs(tempyend-tempystart)+m_radius<parentItem()->height())
            {
                setY(newy);
                setYEnd(tempyend-y());
                setYStart(tempystart-y());
            }
            update();
            event->accept();
        }
        else if(movable ==2)
        {
            double tempxstart = m_xStart+x();
            double tempystart = m_yStart+y();
            double tempxend = event->globalX ()-dragPosition.x ()+preXY.x ();
            double tempyend = event->globalY ()-dragPosition.y ()+preXY.y ();

            double newx=tempxstart<tempxend?tempxstart-m_radius/2:tempxend-m_radius/2;
            double newy=tempystart<tempyend?tempystart-m_radius/2:tempyend-m_radius/2;
            if (newx>0 & newx+abs(tempxend-tempxstart)+m_radius<parentItem ()->width ())
            {
                setX(newx);
                setXEnd(tempxend-x());
                setXStart(tempxstart-x());
            }
            if(newy>0 & newy+abs(tempyend-tempystart)+m_radius<parentItem()->height())
            {
                setY(newy);
                setYEnd(tempyend-y());
                setYStart(tempystart-y());
            }
            update();
            event->accept();
        }
        else if(movable==3)
        {
            double tempX = event->globalX ()-dragPosition.x ();
            double tempY = event->globalY ()-dragPosition.y ();
            if(tempX>0 && tempX<parentItem()->width()-this->width ())
                setX(tempX);
            if(tempY>0 && tempY<parentItem ()->height ()-this->height ())
                setY(tempY);
            event->accept();
        }
    }
}

void MLine::mouseReleaseEvent (QMouseEvent *event)
{
    Q_UNUSED(event);
    MLine::setColor ("blue");
    movable = 0;
    event->accept ();
}
