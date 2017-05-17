#ifndef GLOBALF_H
#define GLOBALF_H
#include <QPointF>

double max(int a, int b)
{
    return a>b?a:b;
}
double max(int a, int b, int c)
{
    return a>b?(a>c?a:c):(b>c?b:c);
}
double dis(double a, double b, double c)
{
    double max=a>b?(a>c?a:c):(b>c?b:c);
    double min =a<b?(a<c?a:c):(b<c?b:c);
    return max-min;
}
double square(double a)
{
    return a*a;
}

bool lineContains(const QPointF a, QPointF b, QPointF c, int radius)
{
    int x=5;
    double ac = sqrt (square(a.x ()-c.x ())+square(a.y ()-c.y ()));
    double bc = sqrt (square(b.x()-c.x ())+square(b.y ()-c.y ()));
    bool acR = ac>radius;
    bool bcR = bc>radius;

    if(a.y ()==b.y ()) {
        if((a.x ()!=b.x ()) & (abs(c.y ()-a.y ())<x) & acR & bcR ){
            return true;
        }
        return false;
    }
    else if(a.x () == b.x ()){
        if((a.y ()!=b.y ())&(abs(c.x ()-a.x ())<x) & acR & bcR )
        {
            return true;
        }
        return false;
    }
    else{
        double A = (b.y ()-a.y ())/(b.x ()-a.x ());
        double B = -1;
        double C =  A*(-a.x ())+a.y ();
        double dis = abs((A*c.x ()+B*c.y ()+C)/sqrt(square(A)+square(B)));
        if((dis<x) & acR & bcR)
        {
            return true;
        }
        return false;
    }
}

#endif // GLOBALF_H
