#ifndef MPOINT_H
#define MPOINT_H

#include <QQuickPaintedItem>
#include <QColor>

class MPoint: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(double xCenter READ xCenter WRITE setXCenter)
    Q_PROPERTY(double yCenter READ yCenter WRITE setYCenter)

public:
    MPoint(QQuickItem *parent=0);

    QString name() const;
    void setName(const QString &name);

    QColor color() const;
    void setColor(const QColor &color);

    double xCenter() const;
    void setXCenter(const double &xCenter);

    double yCenter() const;
    void setYCenter(const double &yCenter);

    void paint(QPainter *painter);

protected:
    void mouseMoveEvent (QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QString m_name;
    QColor m_color;
    double m_xCenter;
    double m_yCenter;
    double m_radius=2;
    QPoint dragPosition;

signals:
    void colorChanged();
};

#endif // MPOINT_H
