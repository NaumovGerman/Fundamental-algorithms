#include <stdio.h>
#include <math.h>

double fact(double x) {
    return (x < 2) ? 1 : x * fact(x - 1);
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

double calculate_e_lim(double x) {
    double acc = pow(10, -x);
    double e = 0.0;
    double temp1 = 0.0;
    double temp2 = 1.0;
    for (double n = 2;; n+= 10) {
        temp1 = temp2;
        temp2 = pow((1 + 1/n), n);
        if (fabs(temp2 - temp1) < acc) {
            break;
        }
    }
    return temp2;
}

double calculate_e_row(double x) {
    double acc = pow(10, -x);
    double e = 0.0;
    double temp = 0.0;
    for (double n = 0;; n++) {
        temp = e;
        e += 1 / fact(n);
        if (fabs(e - temp) < acc) {
            break;
        }
    }
    return e;
}

double calculate_e_equa(double x) {
    return log(x) - 1;
}

double calculate_pi_row(double x) {
    double acc = pow(10, -x);
    double temp = 0.0;
    double p = 0.0;
    for (double n = 1;; n++) {
        temp = p;
        p += pow((-1), n-1) / (2*n - 1);
        if (fabs(p - temp) < acc) {
            break;
        }
    }
    return 4 * p;
}

double calculate_pi_equa(double x) {
    return sin(x);
}

double calculate_log_lim(double x) {
    double acc = pow(10, -x);
    double temp1 = 0.0;
    double temp2 = 0.0;
    for (double n = 2;; n+= 10) {
        temp1 = temp2;
        temp2 = n * (pow(2, 1/n) - 1);
        if (fabs(temp2 - temp1) < acc) {
            break;
        }
    }
    return temp2;
}

double calculate_log_row(double x) {
    double acc = pow(10, -x);
    double temp = 0.0;
    double ln = 0.0;
    for (double n = 1;; n++) {
        temp = ln;
        ln += pow((-1), n-1) / n;
        if (fabs(ln - temp) < acc) {
            break;
        }
    }
    return ln;
}

double calculate_log_equa(double x) {
    return exp(x) - 2;
}

double calculate_sqr_lim(double x) {
    double acc = pow(10, -x);
    double temp1 = -0.5;
    double temp2 = 0.0;
    for (double n = 0;; n++) {
        temp2 = temp1 - pow(temp1, 2) / 2 + 1;
        if (fabs(temp2 - temp1) < acc) {
            break;
        }
        temp1 = temp2;
    }
    return temp2;
}

double calculate_sqr_row(double x) {
    double acc = pow(10, -x);
    double temp = 0.0;
    double ln = 1.0;
    for (double n = 2;; n++) {
        temp = ln;
        ln *= pow(2, pow(2, -n));
        if (fabs(ln - temp) < acc) {
            break;
        }
    }
    return ln;
}

double calculate_sqr_equa(double x) {
    return pow(x, 2) - 2;
}

double sochet(double m, double k) {
    return fact(m) / (fact(k) * fact(m-k));
}
double calculate_y_lim(double x) {
    double acc = pow(10, -x);
    double temp1 = 0.0;
    double temp2 = 0.0;
    for (int m = 2;; m++) {
        temp1 = temp2;
        temp2 = 0.0;
        for (int k = 1; k <= m; k++) {
            temp2 += sochet(m, k) * (k % 2 == 0 ? 1: -1) * log(fact(k)) / k;
        }
        if (fabs(temp2 - temp1) < acc) {
            break;
        }
    }
    return temp2;
}

double calculate_y_row(double x) {
    double acc = pow(10, -x);
    double temp = 0.0;
    /////////////////
}



int main() {
    printf("e - lim   = %.6f\n", calculate_e_lim(9));
    printf("e - row   = %.6f\n", calculate_e_row(6));
    printf("e - equa  = %.6f\n", dichotomy(calculate_e_equa, 2, 3, 6));
    printf("\n");
    printf("pi - lim  = Empty:(\n");
    printf("pi - row  = %.6f\n", calculate_pi_row(6));
    printf("pi - row  = %.6f\n", dichotomy(calculate_pi_equa, 2, 4, 10));
    printf("\n");
    printf("ln - lim  = %.6f\n", calculate_log_lim(9));
    printf("ln - row  = %.6f\n", calculate_log_row(6));
    printf("ln - equa = %.6f\n", dichotomy(calculate_log_equa, 0, 1, 10));
    printf("\n");
    printf("sq - lim  = %.6f\n", calculate_sqr_lim(9));
    printf("sq - row  = %.6f\n", calculate_sqr_row(7));
    printf("sq - equa = %.6f\n", dichotomy(calculate_sqr_equa, 1, 2, 11));
    printf("\n");
    printf("y - lim   = %.6f\n", calculate_y_lim(4));
    return 0;
}
