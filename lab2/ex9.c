#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_good_word(char *word, int num_syst) {
    int temp;
    if (word[0] == '-') return 0;
    for (int i = 1; word[i] != '\0'; i++) {
        if (isdigit(word[i])) {
            temp = word[i] - '0';
        } else if (isalpha(word[i])) {
            temp = word[i] - 'A' + 10;
        } else {
            return 0;
        }
        if (temp >= num_syst) {
            return 0;
        }
    }            
    for (int i = 0; word[i] != '\0'; i++) {
        if (isdigit(word[i])) {
            temp = word[i] - '0';
        } else if (isalpha(word[i])) {
            temp = word[i] - 'A' + 10;
        } else {
            return 0;
        }
        if (temp >= num_syst) {
            return 0;
        }
    }       
    

    return 1;
}

char* convert_to_usual(char *word, int num_syst) {
    unsigned long long int result = 0, temp;
    int a, count = 0, size = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        result = result * num_syst + (isdigit(word[i]) ? word[i] - '0' : word[i] - 'A' + 10);
    }
    temp = result;
    while (temp > 0) {
        count++;
        temp /= 10;
    }
    char* arr = (char*)malloc(sizeof(char) * count);
    for (int i = 0; i < count; i++) {
        arr[i] = result%10 + '0';
        result /= 10;
    }
    return arr;
}


char* smart_sum(char* result, char* word) {
    int len_res = strlen(result);
    int len_word = strlen(word);
    int size, ost = 0, temp;
    char* act_res = NULL;
    if (len_res >= len_word) {
        size = len_res + 1;
        act_res = (char*)malloc(sizeof(char) * size);
        for (int i = 0; i < len_word; i++) {
            temp = (result[i] - '0') + (word[i] - '0') + ost;
            act_res[i] = temp%10 + '0';
            ost = temp / 10;
        }
        for (int i = len_word; i < len_res; i++) {
            temp = (result[i] - '0') + ost;
            act_res[i] = temp%10 + '0';
            ost = temp / 10;
        }
    } else {
        size = len_word + 1;
        act_res = (char*)malloc(sizeof(char) * size);
        for (int i = 0; i < len_res; i++) {
            temp = (result[i] - '0') + (word[i] - '0') + ost;
            act_res[i] = temp%10 + '0';
            ost = temp / 10;
        }
        for (int i = len_res; i < len_word; i++) {
            temp = (word[i] - '0') + ost;
            act_res[i] = temp%10 + '0';
            ost = temp / 10;
        }
    }
    // char* ptr = result;
    // while (*ptr) {
    //     printf("%c", *ptr);
    //     ptr++;
    // }
    // printf("\n");
    // ptr = word;
    // while (*ptr) {
    //     printf("%c", *ptr);
    //     ptr++;
    // }
    // printf("\n");
    // char *ptr = act_res;
    // while (*ptr) {
    //     printf("%c", *ptr);
    //     ptr++;
    // }

    // printf("\n");
    return act_res;
}

char* find_sum(int count, ...) {
    // char* result = (char*)malloc(sizeof(char) * 50);
    int size = 0;
    va_list(runner);
    va_start(runner, count);
    char* act = NULL;
    int base = va_arg(runner, int);
    char* result = convert_to_usual(va_arg(runner, char*), base);
    for (int i = 0; i < count - 2; i++) {
        char* a = va_arg(runner, char*);
        if (!is_good_word(a, base)) {
            free(result);
            return NULL;
        }
        char* conv = convert_to_usual(a, base);
        char* act = smart_sum(result, conv);
        result = act;
        // char* ptr = total;
        // while (*ptr) {
        //     printf("%c ", *ptr);
        //     ptr++;
        // }
        // printf("\n");
        
        free(conv);
    }
    va_end(runner);

    char* ptr = result;
    while (*ptr) {
        size++;
        ptr++;
    }
    char* output = (char*)malloc(sizeof(char) * (size+1));
    ptr = output;
    for (int i = size - 1; i >= 0; i--) {
        *ptr++ = result[i];
    }
    *ptr = 0;
    free(result);
    return output;
}

int main() {
    int base = 16;
    char* hey = find_sum(7, (int) base, (char*) "1A4C84FC", (char*) "86F27B", (char*) "A6238F", (char*) "FFA8367C", (char*) "FFFF", (char*) "FBABCDEF");
    if (hey == NULL) {
        printf("oh..\n");
    }else {
        printf("%s\n", hey);
        free(hey);
    }

    return 0;
}
