#ifndef MLINE_H
#define MLINE_H

#include <QQuickPaintedItem>
#include <QColor>

class MLine: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(double xStart READ xStart WRITE setXStart NOTIFY xStartChanged)
    Q_PROPERTY(double yStart READ yStart WRITE setYStart NOTIFY yStartChanged)
    Q_PROPERTY(double xEnd READ xEnd WRITE setXEnd NOTIFY xEndChanged NOTIFY xEndChanged)
    Q_PROPERTY(double yEnd READ yEnd WRITE setYEnd NOTIFY yEndChanged NOTIFY yEndChanged)

public:
    MLine(QQuickItem *parent=0);

    QString name() const;
    void setName(const QString &name);

    QColor color() const;
    void setColor(const QColor &color);

    double xStart() const;
    void setXStart(const double &xStart);

    double yStart() const;
    void setYStart(const double &yStart);

    double xEnd() const;
    void setXEnd(const double &xEnd);

    double yEnd() const;
    void setYEnd(const double &yEnd);

    void paint(QPainter *painter);

protected:
    void mouseMoveEvent (QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent (QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QString m_name;
    QColor m_color;
    double m_xStart;
    double m_yStart;
    double m_xEnd;
    double m_yEnd;
    int m_radius;
    QLineF* line;
    QPointF* pStart;
    QPointF* pEnd;
    QPoint dragPosition;
    int movable;

signals:
    void colorChanged();
    void xStartChanged();
    void yStartChanged();
    void xEndChanged();
    void yEndChanged();
};

#endif // MLINE_H
