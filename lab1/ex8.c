#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_value(char *arr) {
    // возратит 0 если число некорректное, 1 если корректное
    if (arr[0] != '-' && !isdigit(arr[0])) {
        return 0;
    }

    int len = strlen(arr);
    for (int i = 1; i < len; i++) {
        if (isdigit(arr[i])) {
            continue;
        } else {
            return 0;
        }
    }

    return 1;
}

int conver_int(char *arr) {
    int znak = 1;
    int res = 0;
    int len = strlen(arr);
    if (arr[0] == '-') znak = -1;
    else {
        res = arr[0] - '0';
    }
    for (int i = 1; i < len; i++) {
        res = res * 10 + (arr[i] - '0');
    }
    return znak == -1 ? -res : res;
}

int main(int argc, char *argv[]) {
    int temp;
    char word[5];
    int arr[128], arr2[128], size = 0, size2 = 0;
    int index, difference, sample, max_dif = 0, value;
    int total = 0;

    if (argc != 2 && argc != 3) {
        printf("Неправильный формат ввода\n");
        return 0;
    }

    FILE *f1;
    f1 = fopen("file.txt", "r");
    if (!f1) {
        printf("Такого файла не существует.\n");
        return 0;
    }
    while (fscanf(f1, "%s", word) == 1)
    {
        temp = check_value(word);
        if (temp == 0) continue;
        else {
            arr[size] = conver_int(word);
            size++;
        }
    }
    fclose(f1);

    if (strcmp(argv[1], "a") == 0) {
        if (argc != 2) {
            printf("Введено слишком много аргументов для флана a\n");
            return 0;
        }

        for (int i = 0; i < size; i += 2) {
            arr2[size2] = arr[i];
            size2++;
        }

        for (int i = 0; i < size2; i++) {
            printf("%d ", arr2[i]);
        }

    } else if (strcmp(argv[1], "b") == 0) {
        if (argc != 2) {
            printf("Введено слишком много аргументов для флана a\n");
            return 0;
        }

        for (int i = 0; i < size; i++) {
            if (arr[i] % 2 == 0) {
                arr2[size2] = arr[i];
                size2++;
            }
        }

        for (int i = 0; i < size2; i++) {
            printf("%d ", arr2[i]);
        }

    } else if (strcmp(argv[1], "c") == 0) {
        if (argc != 3) {
            printf("Введено слишком мало аргументов для флана c\n");
            return 0;
        }
        temp = check_value(argv[2]);
        if (temp == 0) {
            printf("Вы ввели некорректное число\n");
            return 0;
        }

        index = conver_int(argv[2]);
        if (0 <= index && index <= size) {
            sample = arr[index];
        } else {
            printf("Вы ввели некорректное число\n");
            return 0;
        }
        

        for (int i = 0; i < size; i++) {
            difference = abs(sample - arr[i]);
            if (difference > max_dif) {
                max_dif = difference;
                value = arr[i];
            }
        }
        arr2[0] = value;
        printf("%d", arr2[0]);
    } else if (strcmp(argv[1], "d") == 0) {
        if (argc != 3) {
            printf("Введено слишком мало аргументов для флана d\n");
            return 0;
        }
        temp = check_value(argv[2]);
        if (temp == 0) {
            printf("Вы ввели некорректное число\n");
            return 0;
        }

        index = conver_int(argv[2]);
        if (0 <= index && index <= size) {
            sample = arr[index];
        } else {
            printf("Вы ввели некорректное число\n");
            return 0;
        }

        for (int i = 0; i < index; i++) {
            total += arr[i];
        } 
        arr2[0] = total;
        printf("%d", arr2[0]);

    } else if (strcmp(argv[1], "e") == 0) {
        if (argc != 3) {
            printf("Введено слишком мало аргументов для флана e\n");
            return 0;
        }
        temp = check_value(argv[2]);
        if (temp == 0) {
            printf("Вы ввели некорректное число\n");
            return 0;
        }

        index = conver_int(argv[2]);
        if (0 <= index && index <= size) {
            sample = arr[index];
        } else {
            printf("Вы ввели некорректное число\n");
            return 0;
        }

        for (int i = 0; i < size; i++) {
            if (sample > arr[i]) {
                total += arr[i];
            }
        }
        arr2[0] = total;
        printf("%d", arr2[0]);

    } else {
        printf("%s\n", "Такого флага не существует");
        return 0;
    }
    printf("\n");
    return 0;
}
