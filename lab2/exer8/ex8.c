#include <stdio.h>
#include <math.h>

double equation(double x) {
    return 3 * sin(sqrt(x)) + 0.35 * x - 3.8;
}

double dichotomy(double f(double), double a, double b, int num) {
    double x0;
    double eps = pow(10, -num);
    while(fabs(b - a) >= eps){
        x0 = (a + b) / 2.0;
        if(f(x0) * f(a) < eps){
            b = x0;
        } else {
            a = x0;
        }
    }
    return x0;
}

int main() {
    printf("%lf\n", dichotomy(equation, 2.0, 3.0, 10));
    //2.2985
    return 0;
}
