#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* convert_to_usual(char *word, int base) {
    char *ptr = word;
    int temp;
    int count = 0;
    while (*ptr == '0') {
        count++;
        ptr++;
    }
    char* new = (char*)malloc(sizeof(char) * (strlen(word) - count + 1));
    if (new == NULL) {
        return NULL;
    }
    char *ptr_2 = new;
    while(*ptr) {
        if (isdigit(*ptr)) {
            temp = *ptr - '0';
        } else if (isalpha(*ptr)) {
            temp = toupper(*ptr) - 'A' + 10;
        } else {
            //free(word);
            free(new);
            return NULL; // или другую ошибку
        }
        if (temp >= base) {
            free(new);
            return 0;
        }
        *ptr_2 = *ptr;
        ptr++;
        ptr_2++;
    }
    *ptr_2 = '\0';
    return new;
}

char* smart_sum(char* result, char* word, int base) {
    int diff, ost = 0, sic, co = 0, temp;
    char *first = NULL;
    char *second = NULL;
    char *output = NULL;
    char *go = NULL;
    char *ptr_1 = result;
    char *ptr_2 = word;
    char *ptr_3;
    int size_1 = strlen(result);
    int size_2 = strlen(word);
    diff = size_1 - size_2;
    if (diff > 0) {
        first = (char*)malloc(sizeof(char) * (size_1 + 2)); // 0 в начали и \0 в конце
        first[0] = '0';

        char *temp_1 = first + 1;
        ptr_1 = result;
        while (*ptr_1) {
            *temp_1 = *ptr_1;
            temp_1++;
            ptr_1++;
        }
        *ptr_1 = '\0';
        printf("first in smart_sum - %s\n", first);

        second = (char*)malloc(sizeof(char) * (size_1 + 2));
        char *temp_2 = second;
        for (int i = 0; i < diff + 1; i++) {
            *temp_2++ = '0';
            // temp_2++;
        }
        ptr_2 = word;
        while (*ptr_2) {
            *temp_2 = *ptr_2;
            temp_2++;
            ptr_2++;
        }
        *ptr_2 = '\0';


        printf("second in smart_sum -%s\n", second);

        output = (char*)malloc(sizeof(char) * (size_1 + 2));
        ptr_1 = first + (size_1 + 1);
        *ptr_1-- = '\0';
        ptr_2 = second + (size_1 + 1);
        *ptr_2-- = '\0';
        ptr_3 = output + (size_1 + 1);
        *ptr_3-- = '\0';

    } else {
        first = (char*)malloc(sizeof(char) * (size_2 + 2));
        first[0] = '0';

        char *temp_1 = first + 1;
        ptr_2 = word;
        while (*ptr_2) {
            *temp_1 = *ptr_2;
            temp_1++;
            ptr_2++;
        }
        *ptr_2 = '\0';
        printf("first in smart_sum - %s\n", first);
        //printf("%s\n", first);

        second = (char*)malloc(sizeof(char) * (size_2 + 2));
        char *temp_2 = second;
        for (int i = 0; i < abs(diff) + 1; i++) {
            *temp_2++ = '0';
        //     // temp_2++;
        }
        ptr_1 = result;
        while (*ptr_1) {
            *temp_2 = *ptr_1;
            temp_2++;
            ptr_1++;
        }
        *ptr_1 = '\0';
        printf("second in smart_sum -%s\n", second);
        //printf("%s\n", second);

        output = (char*)malloc(sizeof(char) * (size_2 + 2));
        ptr_1 = first + (size_2 + 1);
        *ptr_1-- = '\0';
        ptr_2 = second + (size_2 + 1);
        *ptr_2-- = '\0';
        ptr_3 = output + (size_2 + 1);
        *ptr_3-- = '\0';
    }
    free(result);
    free(word);
    while(*ptr_1) {
        sic = isdigit(*ptr_1) ? *ptr_1 - '0' : toupper(*ptr_1) - 'A' + 10;
        printf("sic - %d  ", sic);
        sic += isdigit(*ptr_2) ? *ptr_2 - '0' : toupper(*ptr_2) - 'A' + 10;
        sic += ost;
        printf("sic with ost- %d ", sic);
        ////// *ptr_3 = sic>base ? sic%base - 10 + 'A': sic%base + '0';

        ////// temp = sic%base;
        ////// *ptr_3 = sic%base > 9;
        temp = sic%base;
        if (temp < 10) {
            *ptr_3 = temp + '0';
        } else {
            *ptr_3 = temp - 10 + 'A';
        }
        printf("=> insert %c \n", *ptr_3);
        ost = sic>=base ? 1 : 0;
        ptr_1--;
        ptr_2--;
        ptr_3--;
        co++;
    }
    printf("\n");
    free(first);
    free(second);
    // printf("%c\n", output[0]);
    if (output[0] == '0') {
        printf("here?1\n");
        go = (char*)malloc(sizeof(char)*co);
        ptr_1 = output + 1;
        ptr_2 = go;
        while (*ptr_1){
            *ptr_2 = *ptr_1;
            ptr_1++;
            ptr_2++;
        }
        *ptr_2 = '\0';
        // printf("here?\n");
        free(output);
        return go;
    } else {
        return output;
    }
    
    //go = convert_to_usual(output, base);
    //free(output);
    // printf("%s\n", go);
    return go;
}

char* find_sum(int count, int base, ...) {
    int size = 0;
    int cont;
    if (base < 2) {
        return NULL;
    }
    va_list(runner);
    va_start(runner, base);
    char* act = NULL;
    char* result = convert_to_usual(va_arg(runner, char*), base);
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < count - 1; i++) {
        char* a = convert_to_usual(va_arg(runner, char*), base);
        if (a == NULL) {
            free(result);
            return NULL;
        }
        // printf("a in find_sum - %s\n", a);
        // printf("%d\n", size);
        printf("result = %s\n", result);
        printf("a = %s\n", a);
        act = smart_sum(result, a, base);
        // printf("%s\n", act);
        //// if (act == NULL) {
        ////     free(result);
        ////     free(a);
        ////     return NULL;
        //// }
        size = strlen(act);
        result = (char*)malloc(sizeof(char)*(size + 1));
        strcpy(result, act);
        printf("result_1 = %s\n", result);
        printf("\n");
        free(act);
    }
    va_end(runner);
    // free(act);
    return result;
}

int main() {
    int base = 2;
    // char* hey = find_sum(6, (int) base, (char*) "12345", (char*) "12", (char*) "123", (char*) "1234", (char*) "12345", (char*) "123456"); // 149515 base-10
    // char* hey = find_sum(2, (int) base, (char*) "FFFF", (char*) "A7681B37FF8ECC");
    // char* hey = find_sum(5, (int) base, (char*) "7939", (char*) "16B52", (char*) "57955", (char*) "D94D5", (char*) "61285");
    // char* hey = find_sum(2, (int) base, (char*) "7939FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", (char*) "16B52");
    char* hey = find_sum(2, (int) base, (char*) "01010101001", (char*) "111110101");
    // char* hey = find_sum(2, (int) base, (char*) "75DE0", (char*) "D94D5");
    if (hey == NULL) {
        printf("oh..\n");
    }else {
        // printf("%s\n", hey);
        free(hey);
    }
    return 0;
}