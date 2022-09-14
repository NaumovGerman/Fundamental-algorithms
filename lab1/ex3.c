#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define MAX_LINE_LENGTH 1000

int check_flag(char *arr) {
    // return -1 - флага не существует; 1 - флаг сущ, но в нем нет n; 2 - флаг сущ и в нем есть n
    int marker = 0;
    int len = strlen(arr);
    if (len == 3) {
        if (arr[1] == 'n' && (arr[2] == 'd' ||arr[2] == 'i' || arr[2] == 's' || arr[2] == 'a' || arr[2] == 'f')) {
            marker = 2;
        } else {
            return 0;
        }
    } else {
        if (arr[1] == 'd' ||arr[1] == 'i' || arr[1] == 's' || arr[1] == 'a' || arr[1] == 'f') marker = 1;
        else return 0;
    }

    if (marker == 1) {
        if (arr[1] == 'd') return 1;
        else if (arr[1] == 'i') return 2;
        else if (arr[1] == 's') return 3;
        else if (arr[1] == 'a') return 4;
        else return 5;
    } else {
        if (arr[2] == 'd') return 10;
        else if (arr[2] == 'i') return 20;
        else if (arr[2] == 's') return 30;
        else if (arr[2] == 'a') return 40;
        else return 50;
    }
}


int main(int argc, char *argv[]) {

    if (argc != 3 && argc != 4) {
        printf("%s\n", "Неправильный формат ввода");
        return 0;
    }

    if (argv[1][0] != 45 && argv[1][0] != 47) {
        printf("%s\n", "Вы не ввели флаг");
        return 0;
    }

    int marker = check_flag(argv[1]);
    if (marker == 0) {
        printf("%s\n", "Такого флага не существует");
        return 0;
    }
    // Проверка на существование файла
    FILE *fp;
    fp = fopen(argv[2], "r");
    if (!fp) {
        printf("%s\n", "Такого файла не существует");
        exit(1);
    }

    if (marker == 1 || marker == 10) {
        if (marker == 10 && argc == 3) {
            printf("%s\n", "Вы ввели недостаточно аргументов");
            fclose(fp);
            return 0;
        }
        if (marker == 1 && argc == 4) {
            printf("%s\n", "Вы ввели слишком много аргументов");
            fclose(fp);
            return 0;
        }
        if (marker == 10) {
            FILE *go;
            go = fopen(argv[3], "w");
            while (!feof(fp)) {
                char c = fgetc(fp);
                if ('0' <= c && c <= '9') {
                    continue;
                }
                if (c != EOF) fputc(c, go);
            }
            // нужное содержимое теперь у нас в вспомогательном файле, возвращаем все назад
            fclose(fp);
            fclose(go);
            fp = fopen(argv[2], "w");
            go = fopen(argv[3], "r");
            while (!feof(go)) {
                char c = fgetc(go);
                if (c != EOF) fputc(c, fp);
            }
            fclose(go);
            
        } else {
            char file_name[30];
            strcpy(file_name, "out_");
            strcat(file_name, argv[2]);
            FILE *go;
            go = fopen(file_name, "w");
            while (!feof(fp)) {
                char c = fgetc(fp);
                if ('0' <= c && c <= '9') {
                    continue;
                }
                if (c != EOF) fputc(c, go);
            }
            // нужное содержимое теперь у нас в вспомогательном файле, возвращаем все назад
            fclose(fp);
            fclose(go);
            fp = fopen(argv[2], "w");
            go = fopen(file_name, "r");
            while (!feof(go)) {
                char c = fgetc(go);
                if (c != EOF) fputc(c, fp);
            }
            fclose(go);
        }



    } else if (marker == 2 || marker == 20) {
        if (marker == 20 && argc == 3) {
            printf("%s\n", "Вы ввели недостаточно аргументов");
            fclose(fp);
            return 0;
        }
        if (marker == 2 && argc == 4) {
            printf("%s\n", "Вы ввели слишком много аргументов");
            fclose(fp);
            return 0;
        }
        
        if (marker == 20) {
            FILE *go;
            go = fopen(argv[3], "w");
            char line[MAX_LINE_LENGTH];
            while(fgets(line, MAX_LINE_LENGTH, fp)){
                int count = 0;
                for (int i = 0; line[i] != '\n'; i++) {
                    if ((65 <= line[i] && line[i] <= 90) || (97 <= line[i] && line[i] <= 122)) {
                        count++;
                    } else {
                        continue;
                    }
                }
                fprintf(go, "%d\n", count);
            }
            fclose(go);
        } else {
            char file_name[30];
            strcpy(file_name, "out_");
            strcat(file_name, argv[2]);
            FILE *go;
            go = fopen(file_name, "w");
            char line[MAX_LINE_LENGTH];
            while(fgets(line, MAX_LINE_LENGTH, fp)){
                int count = 0;
                for (int i = 0; line[i] != '\n'; i++) {
                    if ((65 <= line[i] && line[i] <= 90) || (97 <= line[i] && line[i] <= 122)) {
                        count++;
                    } else {
                        continue;
                    }
                }
                fprintf(go, "%d\n", count);
            }
            fclose(go);
        }


    } else if (marker == 3 || marker == 30) {
        if (marker == 30 && argc == 3) {
            printf("%s\n", "Вы ввели недостаточно аргументов");
            fclose(fp);
            return 0;
        }
        if (marker == 3 && argc == 4) {
            printf("%s\n", "Вы ввели слишком много аргументов");
            fclose(fp);
            return 0;
        }

        if (marker == 30) {
            FILE *go;
            go = fopen(argv[3], "w");
            char line[MAX_LINE_LENGTH];
            while(fgets(line, MAX_LINE_LENGTH, fp)){
                int count = 0;
                for (int i = 0; line[i] != '\n'; i++) {
                    if ((65 <= line[i] && line[i] <= 90) || (97 <= line[i] && line[i] <= 122) || (48 <= line[i] && line[i] <= 57) || line[i] == 32) {
                        continue;

                    } else {
                        count++;
                    }
                }
                fprintf(go, "%d\n", count);
            }
            fclose(go);
        } else {
            char file_name[30];
            strcpy(file_name, "out_");
            strcat(file_name, argv[2]);
            FILE *go;
            go = fopen(file_name, "w");
            char line[MAX_LINE_LENGTH];
            while(fgets(line, MAX_LINE_LENGTH, fp)){
                int count = 0;
                for (int i = 0; line[i] != '\n'; i++) {
                    if ((65 <= line[i] && line[i] <= 90) || (97 <= line[i] && line[i] <= 122) || (48 <= line[i] && line[i] <= 57) || line[i] == 32) {
                        continue;

                    } else {
                        count++;
                    }
                }
                fprintf(go, "%d\n", count);
            }
            fclose(go);
        }
        
    } else if (marker == 4 || marker == 40) {
        if (marker == 40 && argc == 3) {
            printf("%s\n", "Вы ввели недостаточно аргументов");
            fclose(fp);
            return 0;
        }
        if (marker == 4 && argc == 4) {
            printf("%s\n", "Вы ввели слишком много аргументов");
            fclose(fp);
            return 0;
        }

        if (marker == 40) {
            FILE *go;
            go = fopen(argv[3], "w");
            while (!feof(fp)) {
                char c = fgetc(fp);
                if (c == '\n') {
                    int a = c;
                    fprintf(go, "%d\n", a);
                } else {
                    if ('0' <= c && c <= '9') {
                        fputc(c, go);
                    } else  {
                        if (c != EOF) {
                            int a = c;
                            fprintf(go, "%d", a);
                        }
                    }
                }
            }
            fclose(fp);
            fclose(go);
            fp = fopen(argv[2], "w");
            go = fopen(argv[3], "r");
            while (!feof(go)) {
                char c = fgetc(go);
                if (c != EOF) fputc(c, fp);
            }
            fclose(go);

        } else {
            char file_name[30];
            strcpy(file_name, "out_");
            strcat(file_name, argv[2]);
            FILE *go;
            go = fopen(file_name, "w");
            while (!feof(fp)) {
                char c = fgetc(fp);
                if (c == '\n') {
                    int a = c;
                    fprintf(go, "%d\n", a);
                } else {
                    if ('0' <= c && c <= '9') {
                        fputc(c, go);
                    } else  {
                        if (c != EOF) {
                            int a = c;
                            fprintf(go, "%d", a);
                        }
                        
                    }
                }
            }
            fclose(fp);
            fclose(go);
            fp = fopen(argv[2], "w");
            go = fopen(file_name, "r");
            while (!feof(go)) {
                char c = fgetc(go);
                if (c != EOF) fputc(c, fp);
            }
            fclose(go);
        }


    } else if (marker == 5 || marker == 50) {
        if (marker == 50 && argc == 3) {
            printf("%s\n", "Вы ввели недостаточно аргументов");
            fclose(fp);
            return 0;
        }
        if (marker == 5 && argc == 4) {
            printf("%s\n", "Вы ввели слишком много аргументов");
            fclose(fp);
            return 0;
        }

        if (marker == 50) {
            FILE *go;
            go = fopen(argv[3], "w");
            char word[MAX_LINE_LENGTH];
            int count = 0;
            while (fscanf(fp, " %s", word) == 1) {
                count++;
                if (count % 5 == 0 && count % 2 != 0) {
                    for (int i = 0; word[i] != '\0'; i++) {
                        fprintf(go, "%d", word[i]);
                    }
                } else if (count % 5 != 0 && count % 2 == 0) {
                    for (int i = 0; word[i] != '\0'; i++) {
                        if (65 <= word[i] && word[i] <= 90) {
                            int new_code = word[i] + 32;
                            fprintf(go, "%c", new_code);
                        } else {
                            fputc(word[i], go);
                        }
                    }
                } else if (count % 5 == 0 && count % 2 == 0) {
                    for (int i = 0; word[i] != '\0'; i++) {
                        if (65 <= word[i] && word[i] <= 90) {
                            fprintf(go, "%d", word[i] + 32);
                        } else {
                            fprintf(go, "%d", word[i]);
                        }
                    }
                } else {
                    for (int i = 0; word[i] != '\0'; i++) {
                        fputc(word[i], go);
                    }
                }
                fputc(' ', go);

            }
            fclose(go);
        } else {
            char file_name[30];
            strcpy(file_name, "out_");
            strcat(file_name, argv[2]);
            FILE *go;
            go = fopen(file_name, "w");
            char word[MAX_LINE_LENGTH];
            int count = 0;
            while (fscanf(fp, " %s", word) == 1) {
                count++;
                if (count % 5 == 0 && count % 2 != 0) {
                    for (int i = 0; word[i] != '\0'; i++) {
                        fprintf(go, "%d", word[i]);
                    }
                } else if (count % 5 != 0 && count % 2 == 0) {
                    for (int i = 0; word[i] != '\0'; i++) {
                        if (65 <= word[i] && word[i] <= 90) {
                            int new_code = word[i] + 32;
                            fprintf(go, "%c", new_code);
                        } else {
                            fputc(word[i], go);
                        }
                    }
                } else if (count % 5 == 0 && count % 2 == 0) {
                    for (int i = 0; word[i] != '\0'; i++) {
                        if (65 <= word[i] && word[i] <= 90) {
                            fprintf(go, "%d", word[i] + 32);
                        } else {
                            fprintf(go, "%d", word[i]);
                        }
                    }
                } else {
                    for (int i = 0; word[i] != '\0'; i++) {
                        fputc(word[i], go);
                    }
                }
                fputc(' ', go);

            }
            fclose(go);
        }


    } else {
        printf("%s\n", "Такого флага не существует");
        return 0;
    }
    fclose(fp);
    return 0;
}
