#include "stdio.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("%s\n", "Неправильный формат ввода");
        return 0;
    }
    // Проверка на существование файла
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (!fp) {
        printf("%s\n", "Такого файла не существует");
        return 0;
    }

    char file_name[30];
    strcpy(file_name, "out_");
    strcat(file_name, argv[1]);
    FILE *go;
    go = fopen(file_name, "w");
    char word1[30];
    char word2[30];
    char word3[30];
    while (fscanf(fp, "%s %s %s", word1, word2, word3) == 3)
    {
        fprintf(go, "%s %s %s\n", word3, word1, word2);
    }
    fclose(fp);
    fclose(go);

    fp = fopen(argv[1], "w");
    go = fopen(file_name, "r");
    while (!feof(go)) {
        char c = fgetc(go);
        if (c != EOF) fputc(c, fp);
    }
    fclose(fp);
    fclose(go);
    return 0;
}
