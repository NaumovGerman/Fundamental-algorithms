#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

// int lengh(char *arr) {
//     int len = 0;
//     if (arr[0] == 45) {
//         for (int i = 1; arr[i] != '\0'; i++) {
//             len++;
//         }
//     } else {
//         for (int i = 0; arr[i] != '\0'; i++) {
//             len++;
//         }
//     }
//     return len;
// }

int check_value_double(char *arr) {
    int len = strlen(arr);
    int znak = 0, dot = 0;
    if (arr[0] == '-') {
        znak++;
        for (int i = 1; i < len; i++) {
            if (arr[i] == '.') {
                dot++;
                if (dot > 1) {
                    return 0;
                }
            } else if ((arr[i] >= 48) && (arr[i] <= 57)) {
                continue;
            } else {
                return 0;
            }
        }
    } else {
        for (int i = 0; i < len; i++) {
            if (arr[i] == '.') {
                dot++;
                if (dot > 1) {
                    return 0;
                }
            } else if ((arr[i] >= 48) && (arr[i] <= 57)) {
                continue;
            } else {
                return 0;
            }
        }
    }
    return 1;


}

double convert_double(char *arr) {
    double res = 0, fact = 1;
    int j = 0;
    if (arr[0] == '-'){
        fact = -1;
    }
    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == '.') {
            j = 1; 
            continue;
        }
        int d = arr[i] - '0';
        if (d >= 0 && d <= 9){
            if (j) {
                fact /= 10.0f;
            }
        res = res * 10.0f + (double)d;
        }
    }
    return res * fact;
}


int check_value(char *arr) {
    // возратит 0 если число некорректное, 1 если корректное
    int len = strlen(arr);
    for (int i = 0; i < len; i++) {
        if ((arr[i] >= 48) && (arr[i] <= 57)) {
            continue;
        } else {
            return 0;
        }
    }

    return 1;
}

int convert_int(char *arr) {
    int znak = 1, res = 0;
    if (arr[0] == '-') {
        znak = -1;
        for (int i = 1; arr[i] != '\0'; i++) {
            int d = arr[i] - '0';
            res = res * 10 + d;
        }
    } else {
        for (int i = 0; arr[i] != '\0'; i++) {
            int d = arr[i] - '0';
            res = res * 10 + d;
        }
    }
    return res * znak;
}

int main(int argc, char *argv[]) {

    if (argc != 4 && argc != 5) {
        printf("%s\n", "Неправильный формат ввода");
        return 0;
    }
    // если первое введеное значение - флаг
    if (argv[1][0] != 45 && argv[1][0] != 47) {
        printf("%s\n", "Вы не ввели флаг");
        return 0;
    }


    if ((strcmp(argv[1], "-q") == 0) || (strcmp(argv[1], "/q") == 0)) {
        if (argc != 5) {
            printf("%s\n", "Некорректное число параметров для флага q");
            return 0;
        }
        double a = 0.0, b = 0.0, c = 0.0;

        int check1 = check_value_double(argv[2]);
        if (check1 == 0) {
            printf("%s\n", "Первое введенное вами число оказалось некорректным");
            return 0;
        } else {
            a = convert_double(argv[2]);
        }

        int check2 = check_value_double(argv[3]);
        if (check2 == 0) {
            printf("%s\n", "Второе введенное вами число оказалось некорректным");
            return 0;
        } else {
            b = convert_double(argv[3]);
        }

        int check3 = check_value_double(argv[4]);
        if (check3 == 0) {
            printf("%s\n", "Третье введенное вами число оказалось некорректным");
            return 0;
        } else {
            c = convert_double(argv[4]);
        }

        // a*x^2 + b*x + c = 0
        double x1 = 0.0, x2 = 0.0;
        if (fabs(a - 0.0) < 0.000000001) {
            if (fabs(b - 0.0) < 0.000000001) {
                if (fabs(c - 0.0) < 0.000000001) {
                    printf("%s\n", "Корни уравнения - любые числа");
                } else {
                    printf("%s\n", "Корней уравнения нет");
                }

            } else {
                if (fabs(c - 0.0) < 0.000000001) {
                    if (b - 0.000000001 <= 0.0) x1 = -c / b; // так как при 0.0 -5.5 0.0 корень -0.0000.....
                    else x1 = c / b;
                } else {
                    x1 = -1 * c / b;
                }
                printf("%s %f\n", "Корень уравнения x =", x1);
            }
        } else {
            double d = b * b - 4 * a * c;
            double qq = 2 * a;
            if (fabs(d - 0.0) < 0.000000001) {
                x1 = -1 * b / qq;
                printf("%s %f\n", "Корень уравнения x =", x1);
            } else if (d - 0.000000001 <= 0.0) {
                printf("%s\n", "Действительных корней уравнения нет");
            } else {
                x1 = (-1 * b + sqrt(d)) / qq;
                if (fabs(c - 0.0) < 0.000000001 && a - 0.000000001 <= 0.0) { // так как при -5.5 -2.2 0.0 один из корней -0.0000.....
                    x2 = (-b - sqrt(d)) / -qq;
                } else {
                    x2 = (-b - sqrt(d)) / qq;
                }
                printf("%s %f\n", "Корень уравнения x1 =", x1);
                printf("%s %f\n", "Корень уравнения x2 =", x2);
            }
        }
        

    } else if ((strcmp(argv[1], "-m") == 0) || (strcmp(argv[1], "/m") == 0)) {
        if (argc != 4) {
            printf("%s\n", "Некорректное число параметров для флага m");
            return 0;
        }

        int a = 0;
        int b = 0;
        int check1 = check_value(argv[2]);
        if (check1 == 0) {
            printf("%s\n", "Первое введенное вами число оказалось некорректным");
            return 0;
        } else if (check1 == 1) {
            a = convert_int(argv[2]);
        } else {
            printf("%s\n", "Произошло что-то страшное...");
            return 0;
        }

        int check2 = check_value(argv[3]);
        if (check2 == 0) {
            printf("%s\n", "Второе введенное вами число оказалось некорректным");
            return 0;
        } else if (check2 == 1) {
            b = convert_int(argv[3]);
        } else {
            printf("%s\n", "Произошло что-то страшное...");
            return 0;
        }

        if (a == 0 || b == 0) {
            printf("%s\n", "Вы указали неверное значение параметра");
            return 0;
        } 
        
        printf("Первое %sчисло кратно второму\n", a % b == 0 ? "" : "не ");
        
    } else if ((strcmp(argv[1], "-t") == 0) || (strcmp(argv[1], "/t") == 0)) {
        if (argc != 5) {
            printf("%s\n", "Некорректное число параметров для флага t");
            return 0;
        }
        double a = 0.0, b = 0.0, c = 0.0;

        int check1 = check_value_double(argv[2]);
        if (check1 == 0) {
            printf("%s\n", "Первое введенная вами длина треугольника оказалась некорректной");
            return 0;
        } else {
            a = convert_double(argv[2]);
        }
        if (a - 0.000000001 <= 0.0) {
            printf("%s\n", "Первое введенная вами длина треугольника оказалась некорректной");
            return 0;
        }

        int check2 = check_value_double(argv[3]);
        if (check2 == 0) {
            printf("%s\n", "Вторая введенная вами длина треугольника оказалась некорректной");
            return 0;
        } else {
            b = convert_double(argv[3]);
        }
        if (b - 0.000000001 <= 0.0) {
            printf("%s\n", "Вторая введенная вами длина треугольника оказалась некорректной");
            return 0;
        }

        int check3 = check_value_double(argv[4]);
        if (check3 == 0) {
            printf("%s\n", "Третья введенная вами длина треугольника оказалась некорректной");
            return 0;
        } else {
            c = convert_double(argv[4]);
        }
        if (c - 0.000000001 <= 0.0) {
            printf("%s\n", "Третья введенная вами длина треугольника оказалась некорректной");
            return 0;
        }
        double a1 = a * a;
        double b1 = b * b;
        double c1 = c * c;

        if (fabs(a1 + b1 - c1) < 0.000000001 || fabs(a1 + c1 - b1) < 0.000000001 || fabs(b1 + c1 - a1) < 0.000000001) {
            printf("%s\n", "Введенные значения могут быть сторонами прямоугольного треугольника");
        } else {
            printf("%s\n", "Введенные значения не могут быть сторонами прямоугольного треугольника");
        }


    } else {
        printf("%s\n", "Такого флага не существует");
        return 0;
    }
    return 0;
}
