#include <stdio.h>
#include <stdarg.h>
#include <math.h>

double avg_geom(int count, ...) {
    double res = 1.0;
    va_list runner;
    va_start(runner, count);
    for (int i  = 0; i < count; i++) {
        res *= va_arg(runner, double);
    }
    va_end(runner);
    if (res < 0.0) {
        return -1;
    }
    return pow(res, 1.0/count);
}

double power(double b, double n) {
    if (n == 0) {
        return 1;  
    } else if (n > 0) {
        return b * power(b, n - 1);
    } else {
        return 1.0 / b * power(b, n + 1);
    }

}

int main() {
    double a;
    a = avg_geom(4, (double) 1.5, (double) 6.8, (double) 12.5, (double) 22.44);
    if (a < 0.0) {
        printf("A negative number was submitted for input\n");
        return 0;
    }
    printf("%f\n", a);
    printf("%f\n", power(2, -10));
    return 0;
}
