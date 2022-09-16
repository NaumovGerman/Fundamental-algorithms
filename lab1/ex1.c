#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

double power(double b, double n) {
    if (n == 0) {
        return 1;
    }
    return b * power(b, n - 1);
}

long long fact(long long n){
    long long res = 1;
    if (n > 1) {
        for (int i = 2; i <= n; i++) {
            if (LLONG_MAX / res > i) {
                res *= i;
            } else {
                return -1;
            }
        }
        return res;
    }
    else {
        return 1;
    }
}   

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("%s\n", "Неправильный формат ввода");
        return 0;
    }

    // проверка на то, сначала введен флаг или число
    int index1 = 0, index2 = 0;
    if (argv[1][0] == 45 || argv[1][0] == 47) {
        index1 = 1;
    }
    if (argv[2][0] == 45 || argv[2][0] == 47) {
        index2 = 1;
    }
    if (index1 == index2) {
        printf("%s\n", "Неправильный формат ввода");
        return 0;
    }

    // в зависимости от индекс определяю индекс_числа и индекс_флага
    int index_of_flag = 0;
    int index_of_int = 0;

    if (index1 == 1) {
        printf("%s\n", "В первую очередь необходимо указать значение, затем флаг");
        return 0;
    }
    if (index2 == 1) {
        index_of_flag = 2;
        index_of_int = 1;
        // это если нам не важен порядок
        // index_of_flag = 2;
        // index_of_int = 1;
    }


    // проверка на то, точно ли инт - инт
    int len_of_int = strlen(argv[index_of_int]);
    int checker = 0;
    for (int i = 0; i < len_of_int; i++) {
        if ((argv[index_of_int][i] >= 48) && (argv[index_of_int][i] <= 57)) {
            checker += 1;
        }
    }
    if (checker != len_of_int) {
        printf("%s\n", "Неправильный формат ввода");
        return 0;
    }
    // string -> int
    int a = 0;
    for (int i = 0; i < len_of_int; i++) {
        int d = argv[index_of_int][i] - '0';
        a = a * 10 + d;
    }


    if ((strcmp(argv[index_of_flag], "-h") == 0) || (strcmp(argv[index_of_flag], "/h") == 0)) {
        if (a == 0) {
            printf("%s\n", "Вы ввели 0, поэтому здесь ничего нет");
            return 0;
        }
        if (a > 50 && a <= 100) {
            printf("%d\n", a);
        } else if (a > 100) {
            printf("%s\n", "Таких чисел нет");
        } else {
            for (int i = 1; i <= 100; i++) {
                if (i % a == 0) {
                    printf("%d ", i);
                }
            }
            printf("\n");
        }
    } else if ((strcmp(argv[index_of_flag], "-p") == 0) || (strcmp(argv[index_of_flag], "/p") == 0)) {
        if (a == 0) {
            printf("%s\n", "Вы ввели 0, поэтому здесь ничего нет");
            return 0;
        }
        int count = 0;
        double temp = a;
        double q = sqrt(temp);
        int q_1 = q + 1;
        for (int i = 2; i < q_1; i++) {
            if (a % i == 0) {
                count += 1;
            }
        }
        if (count == 0) {
            printf("%s %d %s\n", "Число", a, "простое");
        } else {
            printf("%s %d %s\n", "Число", a, "составное");
        }
        
    } else if ((strcmp(argv[index_of_flag], "-s") == 0) || (strcmp(argv[index_of_flag], "/s") == 0)) {
        int b = strlen(argv[index_of_int]);
        for (int i = 0; i < b; i++) {
            char c = argv[index_of_int][i];
            printf("%c ", c);
        }
        printf("\n");

    } else if ((strcmp(argv[index_of_flag], "-e") == 0) || (strcmp(argv[index_of_flag], "/e") == 0)) {
        if (a == 0) {
            printf("%s\n", "Вы ввели 0, поэтому здесь ничего нет");
            return 0;
        }
        if (a > 10) {
            printf("%s\n", "Вы ввели слишком большое число");
        } else {
            long long result = 0;
            for (int i = 1; i <= 10; i++) {
                for (int j = 1; j <= a; j++) {
                    double i_1 = i;
                    double j_1 = j;
                    result = power(i_1, j_1);
                    printf("%-10lld ", result);
                }
                printf("\n");
            }
        }
        
    } else if ((strcmp(argv[index_of_flag], "-a") == 0) || (strcmp(argv[index_of_flag], "/a") == 0)) {
        if (a == 0) {
            printf("%s\n", "Вы ввели 0, поэтому здесь ничего нет");
            return 0;
        }
        int temp = 0;
        for (int i = 1; i <= a; i++) {
            temp += i;
        }
        printf("%s %d %s %d\n", "Сумма чисел от 1 до", a, " = ", temp);
    } else if ((strcmp(argv[index_of_flag], "-f") == 0) || (strcmp(argv[index_of_flag], "/f") == 0)) {
        long long n = a;
        long long qw = fact(n);
        if (qw == -1) {
            printf("%s\n", "Вы ввели слишком большое число");
        } else {
            printf("%s %d %s %lld\n", "Факториал числа", a, "=", qw);
        }

    } else {
        printf("%s\n", "Такого флага не существует");
        return 0;
    }
    return 0;
}
