#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

enum error {
    its_ok = -1,
    incor_notation = -2,
    incor_double = -3,
    no_memmory = -4,
    not_conv = 1,
    conv = 2
};


typedef struct {
    long long numerator;
    long long denominator;
    int status;
}Fraction;

int check_word(char* word) {
    char *ptr = word;
    if (*ptr != '0') {
        return incor_double;
    }
    ptr++;
    if (*ptr != '.') {
        return incor_double;
    }
    ptr++;
    while (*ptr) {
        if (!isdigit(*ptr)) {
            return incor_double;
        }
        ptr++;
    }
    return its_ok;
}

void fill_fract(Fraction *fract, char* word, int not) {
    char *ptr = word;
    int a = 0, b = 1;
    ptr++;
    ptr++;
    while (*ptr) {
        a = a * 10 + (*ptr - '0');
        b *= 10;
        ptr++;
    }
    fract->numerator = a;
    fract->denominator = b;
}

void try_to_slash(long long *a, long long *b) {
    int temp = 2;
    if (*b % *a == 0) {
        *b /= *a;
        *a /= *a;
    }

    for (temp; temp <= (int)(sqrt(*a) + 1); temp++) {
        if (*a % temp == 0 && *b % temp == 0) {
            *a /= temp;
            *b /= temp;
        }
    }
}

int is_covertable(long long a, int not) {
    while (a > 1) {
        if (a % not != 0) {
            return not_conv;
        }
        a /= not;
    }
    return conv;  
}

int* try_to_convert(int count, int notation, ...) {
    char* word = NULL;
    int ch = 1, identify = 0;
    Fraction *fract = (Fraction*)malloc(sizeof(Fraction));
    if (fract == NULL) {
        return NULL;
    }
    int* res = (int*)malloc(sizeof(int) * count);
    if (res == NULL) {
        free(fract);
        return NULL;
    }
    va_list(runner);
    va_start(runner, notation);
    for (int i = 0; i < count; i++) {
        word = va_arg(runner, char*);
        ch = check_word(word);
        if (ch == incor_double) {
            res[i] = incor_double;
            continue;
        }
        fill_fract(fract, word, notation);
        try_to_slash(&(fract->numerator), &(fract->denominator));
        identify = is_covertable(fract->denominator, notation);
        res[i] = identify;
    }
    free(fract);
    return res;
}

int main() {
    int *result = NULL;
    int count = 4, notation = 8;
    if (notation < 2 || notation > 36) {
        printf("Notation has to be in range from 2 to 36\n");
        return 0;
    }
    result = try_to_convert(count, notation, (char*) "0.125", (char*) "0.233335", (char*) "0.1666666", (char*) "0.256");
    if (result == NULL) {
        printf("Memory was not allocated for vital objects and data types\n");
        return 0;
    }
    for (int i = 0; i < count; i++) {
        if (result[i] == conv) {
            printf("Convertable\n");
        } else if (result[i] == incor_double) {
            printf("Incorrect double\n");
        } else {
            printf("Not conertable\n");
        }
    }
    free(result);
    return 0;
}
