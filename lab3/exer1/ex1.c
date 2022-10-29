#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

enum error{
    its_ok = -1,
    incor_int = -2,
    no_memmory = -3
};

int add(int num1, int num2) {
    int res = 0, carry = 0;
    res = num1^num2;
    carry = (num1&num2) << 1;
    while (carry) {
        int tmp = res;
        res = res^carry;
        carry = (tmp&carry) << 1;
    }
    return res;
}


int negtive(int n) {
    return add(~n, 1);
}

int subtraction(int a, int b) {
    return add(a, negtive(b));
}

int divide(int a, int b) {
    int res = 0;
    while (a >= b) {
        res = add(res, 1);
        a = subtraction(a, b);
    }
    return res;
}

int check(int *n) {
    char c = 0;
    if (scanf("%d%c", n, &c) == 2 && c == '\n') {
        return its_ok;
    }
    return incor_int;
}

char* convert(int number, int degree, int flag) {
    char* res = (char*)malloc(sizeof(char)*2);
    if (res == NULL) {
        return NULL;
    }
    char* out = NULL;
    int size = 0, len = 1;
    char *ptr = res;
    char *p = NULL;
    int temp = 0, k = degree;
    degree = 1 << degree;
    while (number > 0) {
        if (len - size == 1) {
            char* tmp = (char*)realloc(res, sizeof(char) * len*2);
            if (!tmp) {
                free(res);
                return NULL;
            } else {
                res = tmp;
            }
            len *= 2;
        }
        
        temp = number & (degree - 1);
        *ptr++ = temp > 9 ? add(subtraction(temp, 10), 'A'): add(temp, '0');
        number >>= k;
        size++; 
    }
    *ptr = 0;
    ptr--;
    if (flag == 1) {
        out = (char*)malloc(sizeof(char) * (size + 1));
        if (out == NULL) {
            free(res);
            return NULL;
        }
        p = out;
    } else {
        out = (char*)malloc(sizeof(char) * (size + 2));
        if (out == NULL) {
            free(res);
            return NULL;
        }
        p = out;
        *p++ = '-'; 
    }

    while (size > 0) {
        *p++ = *ptr--;
        size--;
    }
    *p = 0;
    free(res);
    return out;
}


int main() {
    int number = 0, degr = 0, test, flag = 1;
    char *result = NULL;
    printf("Please enter the number\n");
    if (check(&number) != its_ok) {
        printf("You didn't enter a number\n");
        return 0;
    }
    printf("Please enter the degree of 2 from 1 to 5\n");
    if ((check(&degr) != its_ok)) {
        printf("You didn't enter a degree\n");
        return 0;
    }
    if ((degr < 1) || (degr > 5)) {
        printf("The degree is not in the range from 1 to 5\n");
        return 0;
    }
    if (number == 0) {
        printf("0\n");
        return 0;
    }
    flag = number > 0 ? 1 : -1;
    number = flag == 1 ? number : negtive(number);
    // printf("%d %d\n", number, flag);
    result = convert(number, degr, flag);
    if (result == NULL) {
        printf("Memory was not allocated\n");
        return 0;
    }
    printf("%s\n", result);
    free(result);
    return 0;
}
