#include "stdio.h"
#include <string.h>
#include <ctype.h>

#define size 30

int is_good_word(char *word, int len, int num_syst) {
    int temp;
    for (int i = 0; i < len; i++) {
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

long long convert_to_usual(char *word, int len, int num_syst) {
    long long result = 0;
    for (int i = 0; i < len; i++) {
        result = result * num_syst + (isdigit(word[i]) ? word[i] - '0' : word[i] - 'A' + 10);
    }
    return result;
}


int main() {
    int num_syst;
    char word[size], len;
    int fin1[size], count = 0, temp;
    char fin2[size];
    char total[size];
    long long num;
    long long max = 0;

    printf("Введите систему счисления:\n");
    scanf("%d", &num_syst);
    printf("Введите числа:\n");
    while (scanf("%s", word) == 1 && strcmp(word, "Stop") != 0)
    {
        len = strlen(word);
        if (is_good_word(word, len, num_syst)) {
            num = convert_to_usual(word, len, num_syst); // from num_syst -> base 10
            if (num > max) max = num;
        } else {
            continue;
        }
    }
    // printf("%lld\n", max);

    temp = max;
    while (temp > 0) {
        fin1[count++] = temp % 9;
        temp = (temp - (temp % 9)) / 9;
    }
    printf("В 9-ричной системе счисления - ");
    for (int i = count - 1; i > -1; i--)
    {
        printf("%d", fin1[i]);
    }
    count = 0;
    printf("\n");


    temp = max;
    while (temp > 0) {
        fin2[count++] = (temp % 18 > 9 ? (temp % 18) - 10 + 'A' : (temp % 18) + '0') ;
        temp = (temp - (temp % 18)) / 18;
    }
    printf("В 18-ричной системе счисления - ");
    for (int i = count - 1; i > -1; i--)
    {
        printf("%c", fin2[i]);
    }
    count = 0;
    printf("\n");


    temp = max;
    while (temp > 0) {
        fin2[count++] = (temp % 27 > 9 ? (temp % 27) - 10 + 'A' : (temp % 27) + '0') ;
        temp = (temp - (temp % 27)) / 27;
    }
    printf("В 27-ричной системе счисления - ");
    for (int i = count - 1; i > -1; i--)
    {
        printf("%c", fin2[i]);
    }
    count = 0;
    printf("\n");


    temp = max;
    while (temp > 0) {
        fin2[count++] = (temp % 36 > 9 ? (temp % 36) - 10 + 'A' : (temp % 36) + '0') ;
        temp = (temp - (temp % 36)) / 36;
    }
    printf("В 36-ричной системе счисления - ");
    for (int i = count - 1; i > -1; i--)
    {
        printf("%c", fin2[i]);
    }
    printf("\n");
    return 0;
}
