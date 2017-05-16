#ifndef GLOBALF_H
#define GLOBALF_H
//double max(int a, int b)
//{
//    return a>b?a:b;
//}
//double max(int a, int b, int c)
//{
//    return a>b?(a>c?a:c):(b>c?b:c);
//}
double dis(double a, double b, double c)
{
    double max=a>b?(a>c?a:c):(b>c?b:c);
    double min =a<b?(a<c?a:c):(b<c?b:c);
    return max-min;
}
#endif // GLOBALF_H
