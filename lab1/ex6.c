#include "stdio.h"
#include <string.h>
#include <ctype.h>

int is_good_word(char *word, int len) {
    for (int i = 0; i < len; i++) {
        if (!isdigit(word[i]) && !isalpha(word[i])) {
            return 0;
        }
    }
    return 1;
}

int syst_define(char *word, int len) {
    int syst = 0, temp = 0;
    for (int i = 0; i < len; i++) {
        if (isdigit(word[i])) {
            temp = word[i] - '0';
        } else {
            temp = word[i] - 'A' + 10;
        }
        if (temp > syst) syst = temp;
    }
    return syst + 1;
}

long long convert_to_usual(char *word, int len, int num_syst) {
    long long result = 0;
    for (int i = 0; i < len; i++) {
        result = result * num_syst + (isdigit(word[i]) ? word[i] - '0' : word[i] - 'A' + 10);
    }
    return result;
}


int main(int argc, char *argv) {
    char word[30];
    int num_syst, len;
    long long num;

    FILE *fi;
    fi = fopen("file.txt", "r");
    if (!fi) {
        printf("Файл не существует\n");
        return 0;
    }
    while(fscanf(fi, "%s", word) == 1) {
        len = strlen(word);
        if (is_good_word(word, len)) {
            num_syst = syst_define(word, len);
            num = convert_to_usual(word, len, num_syst);
        } else {
            continue;
        }
        printf("num_syst = %d, num = %lld\n", num_syst, num);
    }


    fclose(fi);
    return 0;
}
