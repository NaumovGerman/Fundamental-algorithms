#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

double power(double b, double n) {
    if (n == 0) {
        return 1;  
    }
    return b * power(b, n - 1);
}

int check_figure(int count, ...) {
    if (count % 2 != 0 || count <= 4) {
        return -1;
    } else if (count == 6) {
        return 1;
    }
    double x = 0.0, y = 0.0;
    va_list runner;
    va_start(runner, count);
    double* arr = (double*)malloc(sizeof(double) * count);
    if (arr == NULL) {
        return -2;
    }
    for (int i = 0; i < count; i+= 2) {
        arr[i] = va_arg(runner, double);
        arr[i+1] = va_arg(runner, double);
    }
    double* ls = (double*)malloc(sizeof(double) * (count+2));
    if (ls == NULL) {
        free(arr);
        return -2;
    }
    ls[0] = arr[0] - arr[count - 2];
    ls[1] = arr[1] - arr[count - 1];
    int pos = 2;
    for (int i = 0; i < count - 2; i++) {
        ls[pos++] = arr[i + 2] - arr[i];
    }
    ls[count] = ls[0];
    ls[count+1] = ls[1];
    free(arr);
    for (int i = 0; i < count - 2; i += 2) {
        if (ls[i] * ls[i+3] - ls[i+1] * ls[i+2] > 0) {
            continue;
        } else {
            free(ls);
            return 0;
        }
    }
    free(ls);
    return 1;
}

double calculate(int count, ...) {
    double x, n, res = 0.0;
    va_list runner;
    va_start(runner, count);
    x = va_arg(runner, double);
    n = va_arg(runner, double);
    for (int i = n; i >= 0; i--) {
        res += va_arg(runner, double) * power(x, i);
    }
    va_end(runner);
    return res;
}


int main() {
    int is_conv = check_figure(10, (double) 1, (double) 1, (double) 6, (double) 2, (double) 6, (double) 7, (double) 4, (double) 8, (double) 1, (double) 5);
    // // int is_conv = check_figure(8, (double) 1, (double) 1, (double) 6, (double) 6, (double) 3, (double) 9, (double) -3, (double) 3);
    if (is_conv == 1) {
        printf("The figure is convex\n");
    } else if (is_conv == 0) {
        printf("The figure is not convex\n");
    } else if (is_conv == -2) {
        printf("Memory was not allocated\n");
    } else {
        printf("Invalid input\n");
    }
    double calc = calculate(7, (double) 7.1, (double) 4, (double) 22, (double) -2, (double) 65, (double) 0, (double) -11);
    printf("%f\n", calc);
    return 0;
}
