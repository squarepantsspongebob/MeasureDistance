#include "mLine.h"
#include <QPainter>
#include <QQuickItem>
#include <QCursor>
#include "globalf.h"

MLine::MLine(QQuickItem *parent)
    :QQuickPaintedItem(parent),m_color("blue"),m_colorHover("orange"),m_radius(10),movable(0)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    QQuickItem::setCursor(QCursor(Qt::OpenHandCursor));
    line = new QLineF(5, 5, 100-5, 100-5);
    textRect = QRect(line->p2().x()+10,line->p2().y()-30,70,30);
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
    return line->p1 ().x ();
}

void MLine::setXStart (const double &xStart)
{
    line->setP1 (QPointF(xStart,line->p1().y ()));
}

double MLine::yStart() const
{
    return line->p1 ().y ();
}

void MLine::setYStart (const double &yStart)
{
    line->setP1 (QPointF(line->p1 ().x (), yStart));
}
double MLine::xEnd() const
{
    return line->p2 ().x ();
}

void MLine::setXEnd (const double &xEnd)
{
    line->setP2(QPointF(xEnd, line->p2 ().y ()));
}

double MLine::yEnd() const
{
    return line->p2 ().y ();
}

void MLine::setYEnd (const double &yEnd)
{
    line->setP2(QPointF(line->p2 ().x (), yEnd));
}

void MLine::paint (QPainter *painter)
{
    // Line
    QPen pen(m_color,2);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawLine(*line);

    //Bezier Curve
    QPainterPath path;
    pen.setStyle (Qt::DotLine); painter->setPen (pen);
    path.moveTo ((line->p1().x()+line->p2().x())/2, (line->p1().y()+line->p2().y())/2);
    path.cubicTo (((textRect.topLeft ().x ()+textRect.topRight ().x ())/2+(line->p1().x()+line->p2().x())/2)/2,(line->p1().y()+line->p2().y())/2,((textRect.topLeft ().x ()+textRect.topRight ().x ())/2+(line->p1().x()+line->p2().x())/2)/2,(textRect.topLeft ().y ()+textRect.bottomLeft ().y ())/2,(textRect.topLeft ().x ()+textRect.topRight ().x ())/2,(textRect.topLeft ().y ()+textRect.bottomLeft ().y ())/2);
    painter->drawPath (path);

    //Points
    pen.setStyle (Qt::SolidLine);
    pen.setColor ("red"); pen.setWidth (m_radius);
    painter->setPen (pen);
    painter->drawPoint(line->p1 ());
    painter->drawPoint(line->p2 ());

    //Lable's Rectangle
    //    if(textRect.contains (this->mapFromGlobal (QCursor::pos()).x (),this->mapFromGlobal (QCursor::pos ()).y ()))
    //    {
    //        pen.setColor("orange");
    //        qDebug()<<"1";
    //    }
    //    else
    //    {
    //        pen.setColor ("blue");
    //        qDebug()<<0;
    //    }
    pen.setColor("blue");
    pen.setWidth(2);
    pen.setStyle (Qt::DotLine);
    painter->setPen (pen);
    painter->setBrush (Qt::white);
    painter->drawRect(textRect);

    //Lable
    painter->setBrush (Qt::transparent);
    font = painter->font();
    font.setPixelSize (16); font.setBold (true);
    painter->setFont (font);
    painter->drawText (textRect,Qt::AlignCenter,"11.50cm");
}

void MLine::mousePressEvent (QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if (QRectF(line->p1().x()-m_radius/2, line->p1().y()-m_radius/2, m_radius, m_radius).contains (event->pos()))
        {
            movable = 1;
            preP1 = line->p1 ();
            dragPosition = event->globalPos ();
            MLine::setColor ("orange");
            event->accept();
        }
        else if(QRectF(line->p2().x()-m_radius/2, line->p2().y()-m_radius/2, m_radius, m_radius).contains (event->pos()))
        {
            movable = 2;
            preP2 = line->p2 ();
            dragPosition = event->globalPos ();
            MLine::setColor ("orange");
            event->accept();
        }
        else if(textRect.contains (event->pos ()))
        {
            movable = 4;
            dragPosition = event->globalPos ()-QPointF(textRect.topLeft ());
            MLine::setColor("orange");
            event->accept ();
        }
        else if(lineContains(line->p1 (), line->p2 (),event->pos (), m_radius))
        {
            movable=3;
            preP1 = line->p1 ();
            preP2 = line->p2 ();
            dragPosition = event->globalPos ();
            MLine::setColor("orange");
            event->accept ();
        }
        else
        {QQuickPaintedItem::mousePressEvent (event);}
    }
    else{
        QQuickPaintedItem::mousePressEvent (event);
    }
}

void MLine::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::ClosedHandCursor);

        if(movable==1){
            QPointF tempP = event->globalPos ()-dragPosition;
            line->setP1(preP1+tempP);
            update();
            event->accept();
        }
        else if(movable ==2)
        {
            QPointF tempP = event->globalPos ()-dragPosition;
            line->setP2(preP2+tempP);
            update();
            event->accept();
        }
        else if(movable==3)
        {
            QPointF tempP = event->globalPos ()-dragPosition;
            line->setP1(preP1+tempP);
            line->setP2(preP2+tempP);
            event->accept();
            update();
        }
        else if(movable == 4)
        {
            textRect.moveTo (QPoint(event->globalX ()-dragPosition.x (), event->globalY ()-dragPosition.y ()));
            event->accept ();
            update();
        }
        else{
            QQuickPaintedItem::mouseMoveEvent (event);
        }
    }
    else{
        QQuickPaintedItem::mouseMoveEvent (event);
    }
}

void MLine::mouseReleaseEvent (QMouseEvent *event)
{
    Q_UNUSED(event);
    MLine::setColor ("blue");
    setCursor(Qt::OpenHandCursor);
    movable = 0;
    event->accept ();
}

void MLine::hoverEnterEvent (QHoverEvent *event)
{
    Q_UNUSED(event);
    if (QRectF(line->p1().x()-m_radius/2, line->p1().y()-m_radius/2, m_radius, m_radius).contains (event->pos()))
    {
        qDebug()<<"p1";
        event->accept();
    }
    else if(QRectF(line->p2().x()-m_radius/2, line->p2().y()-m_radius/2, m_radius, m_radius).contains (event->pos()))
    {
        qDebug()<<"p2";
        event->accept();
    }
    else if(textRect.contains (event->pos ()))
    {
        qDebug()<<"label";
        event->accept ();
    }
    else if(lineContains(line->p1 (), line->p2 (),event->pos (), m_radius))
    {
        qDebug()<<"line";
        event->accept ();
    }
    else
    {
        QQuickPaintedItem::hoverEnterEvent (event);
//        nextItemInFocusChain()->hoverEnterEvent (event);
    }
}

void MLine::hoverMoveEvent (QHoverEvent *event)
{
    Q_UNUSED(event);
    if (QRectF(line->p1().x()-m_radius/2, line->p1().y()-m_radius/2, m_radius, m_radius).contains (event->pos()))
    {
        qDebug()<<"p1";
        event->accept();
    }
    else if(QRectF(line->p2().x()-m_radius/2, line->p2().y()-m_radius/2, m_radius, m_radius).contains (event->pos()))
    {
        qDebug()<<"p2";
        event->accept();
    }
    else if(textRect.contains (event->pos ()))
    {
        qDebug()<<"label";
        event->accept ();
    }
    else if(lineContains(line->p1 (), line->p2 (),event->pos (), m_radius))
    {
        qDebug()<<"line";
    }
    else
    {
//        nextItemInFocusChain ()->hoverMoveEvent (event);
    }
}

void MLine::hoverLeaveEvent (QHoverEvent *event)
{
    Q_UNUSED(event);
    qDebug()<<"leave";
    event->accept ();
}
