#include "stdio.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {


    // если первое введеное значение - флаг
    if (argv[1][0] != 45) {
        printf("%s\n", "Вы не ввели флаг");
        return 0;
    }

    // файл в который записываем
    char file_name[30];
    strcpy(file_name, "out_finalfile.txt");
    FILE *final;
    final = fopen(file_name, "a");
        

    if (strcmp(argv[1], "-fi") == 0) {
        if (argc != 3) {
            printf("%s\n", "Некорректное число параметров для флага fi");
            return 0;
        }
        FILE *f1;
        f1 = fopen(argv[2], "r");
        if (!f1) {
            printf("%s\n", "Такого файла не существует");
            fclose(final);
            exit(1);
        }

        char word[30];
        while (fscanf(f1, "%s", word) == 1) {
            FILE *another;
            another = fopen(word, "r");
            if (!another) {
                printf("%s\n", "Такого файла не существует");
                fclose(f1);
                fclose(final);
                exit(1);
            }
            while (!feof(another)) {
                char c = fgetc(another);
                if (c != EOF) {
                    fputc(c, final);
                }
            }
            fclose(another);
        }
        fclose(f1);
    } else if (strcmp(argv[1], "-cin") == 0) {
        if (argc != 2) {
            printf("%s\n", "Некорректное число параметров для флага m");
            return 0;
        }
        char word[30];
        while (scanf("%s", word) == 1) {
            FILE *another;
            another = fopen(word, "r");
            if (!another) {
                printf("%s\n", "Такого файла не существует");
                fclose(final);
                exit(1);
            }
            while (!feof(another)) {
                char c = fgetc(another);
                if (c != EOF) {
                    fputc(c, final);
                }
            }
            fclose(another);
        }

    } else if (strcmp(argv[1], "-arg") == 0) {
        if (argc <= 2) {
            printf("%s\n", "Некорректное число параметров для флага m");
            return 0;
        }
        for (int i = 2; i < argc; i++) {
            FILE *another;
            another = fopen(argv[i], "r");
            if (!another) {
                printf("%s\n", "Такого файла не существует");
                fclose(final);
                exit(1);
            }
            while (!feof(another)) {
                char c = fgetc(another);
                if (c != EOF) {
                    fputc(c, final);
                }
            }
            fclose(another);
        }

    } else {
        printf("%s\n", "Такого флага не существует");
        return 0;
    }
    fclose(final);
    return 0;
}