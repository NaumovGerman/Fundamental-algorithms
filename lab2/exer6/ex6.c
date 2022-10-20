#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct {
    char filename[50];
    int *arr;
    int *rows;
    int count;
    int status;
} Okey;


int skipper(FILE *f1, int amount, char *ptr) {
    int w = 0;
    for (int i = 0; i < amount; i++) {
        ptr++;
        if (*ptr != '\n') {
            w++;
        }
        if (*ptr == EOF) {
            return -1;
        } 
    }
    return w;
}


Okey do_things(char* word, char* file) {
    FILE *f1;
    int len, flag = 1, a, ll = 0, index = 0;
    int amount_n = 1, act_size = 0, pos = 0;
    char stroka[255];
    char *ptr;
    Okey piece;
    piece.arr = (int*)malloc(sizeof(int) * 2);
    if (piece.arr == NULL) {
        piece.status = -1;
        return piece;
    }
    piece.rows = (int*)malloc(sizeof(int) * 2);
    if (piece.rows == NULL) {
        piece.status = -1;
        free(piece.arr);
        return piece;
    }
    piece.count = 0;
    f1 = fopen(file, "r");
    len = strlen(word);
    if (!f1) {
        printf("No file\n");
    } else {
        while(fgets(stroka, 255, f1) != NULL) {
            ptr = stroka;
            if (ptr == NULL) {
                continue;
            }

            while (*ptr != '\n') {

                if (*ptr == word[0]) {
                    pos = index;
                    for (int i = 1; i < len; i++) {
                        index++;
                        ptr++;
                        if (*ptr != word[i]) {
                            flag = 0;
                            a = skipper(f1, len-i-1, ptr);
                            if (a == -1) {
                                printf("hey eof!");
                                fclose(f1);
                            }
                        }
                        

                    }
                    if (flag) {
                        ll++;
                        if (ll - piece.count == 1) {
                            piece.arr = (int*)realloc(piece.arr, ll * 2);

                            int* tmp = (int*)realloc(piece.arr, ll * 2);
                            if (!tmp) {
                                free(piece.arr);
                                piece.status = -2;
                                return piece;
                                // return NULL;
                            } else {
                                piece.arr = tmp;
                            }

                            piece.rows = (int*)realloc(piece.rows, ll * 2);
                            tmp = (int*)realloc(piece.rows, ll * 2);
                            if (!tmp) {
                                free(piece.arr);
                                free(piece.rows);
                                piece.status = -2;
                                return piece;
                            } else {
                                piece.rows = tmp;
                            }
                            //проверка
                        }
                        piece.arr[piece.count] = pos;
                        piece.rows[piece.count] = amount_n;
                        piece.count++;
                    } else {
                        flag = 1;
                    }
                    amount_n += a;
                }
                index++;
                ptr++;

            }
            amount_n++;
            index = 0;
        }
        fclose(f1);
        strcpy(piece.filename,  file);
    }
    piece.status = piece.count > 0 ? 1 : 0;
    return piece;

    // }    
        
}

Okey* find_all_strings(int count, ...) {
    va_list(runner);
    va_start(runner, count);
    char* my_string = (char*)malloc(sizeof(char) * 60);
    if (my_string == NULL) {
        va_end(runner);
        return NULL;
    }

    Okey* my_array = (Okey*)malloc(sizeof(Okey) * (count-1));
    if (my_array == NULL) {
        free(my_string);
        va_end(runner);
        return NULL;
    }

    strcpy(my_string, va_arg(runner, char*));
    char* file_path = (char*)malloc(sizeof(char) * 70);
    if (file_path == NULL) {
        free(my_string);
        free(my_array);
        va_end(runner);
        return NULL;
    }
    for (int i = 0; i < count - 1; i++) {
        strcpy(file_path, va_arg(runner, char*));
        my_array[i] = do_things(my_string, file_path);

        if (my_array[i].status == -1) {
            free(file_path);
            free(my_string);
            va_end(runner);
            return NULL;
        }

        if (my_array[i].status == -2) {
            free(file_path);
            free(my_string);
            free(my_array);
            va_end(runner);
            return NULL;
        }

        free(file_path);
        file_path = (char*)malloc(sizeof(char) * 60);
        if (file_path == NULL) {
            free(my_string);
            free(my_array);
            va_end(runner);
            return NULL;
        }
    }
    free(file_path);
    free(my_string);
    va_end(runner);
    return my_array;
}

int main() {
    Okey *final = NULL;
    final = find_all_strings(3, (char*) "shi", (char*) "/home/german/fundi/newfile.txt", (char*) "/home/german/fundi/omg.txt");
    if (final == NULL) {
        printf("Memory was not allocated\n");
        return 0;
    }
    for (int i = 0; i < 2; i++) {
        printf("%s\n", final[i].filename);
        if (final[i].status == 1) {
            for (int j = 0; j < final[i].count; j++) {
                printf("row %d - index %d\n", final[i].rows[j] ,final[i].arr[j]);
            }
        } else {
            printf("There was no substring in this file\n");
        }
    }
    for (int i = 0; i < 2; i++) {
        free(final[i].rows);
        free(final[i].arr);
        
    }
    free(final);
    return 0;
}
