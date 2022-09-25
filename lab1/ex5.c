#include <stdio.h>
#include <string.h>

int if_files_available(int *if_open, int size) {
    for (int i = 0; i < size; i++) {
        if (if_open[i] == 1) {
            return 1;
        }
    }
    return 0;
}

int do_flag_fi(FILE *f1, char (*names)[100]) {
    FILE *check = NULL;
    int len = 0;
    while (fscanf(f1, "%s", names[len]) == 1) {
        check = fopen(names[len], "r");
        if (check) {
            fclose(check);
        } else {
            return -1;
        }
        len++;
    }
    fclose(f1);
    return len;
}

int do_flag_cin(char (*names)[100]) {
    char word[100];
    int len = 0;
    FILE *check = NULL;
    while (scanf("%s", names[len]) == 1 && strcmp(names[len], "end") != 0)
    {
        check = fopen(names[len], "r");
        if (check) {
            fclose(check);
        } else {
            return -1;
        }
        len++;
    }
    return len;
    
}

int do_flag_arg(char (*names)[100], int size, char *argv[]) {
    int len = 0;
    FILE *check = NULL;
    for (int i = 2; i < size; i++) {
        check = fopen(argv[i], "r");
        if (check) {
            fclose(check);
        } else {
            return -1;
        }
        strcpy(names[len], argv[i]);
        len++;
    }
    return len;
}

void make_fin_file(FILE *final, char (*names)[100], int length) {
    FILE *temp[length];
    char c;
    final = fopen("out_final_file.txt", "w");
    int if_open[length];
    for (int i = 0; i < length; i++) {
        if_open[i] = 1;
        temp[i] = NULL;
    }
    while(if_files_available(if_open, length)){
        for (int i = 0; i < length; i++) {
            if (temp[i] == NULL) {
                temp[i] = fopen(names[i], "r");
            }
            c = fgetc(temp[i]);
            if (c != EOF) {
                fputc(c, final);
            } else {
                if_open[i] = 0;
                fclose(temp[i]);
            }
        }
    }
    fclose(final);

}

int main(int argc, char *argv[]) {
    FILE *f1 = NULL, *final = NULL;
    char names[100][100];
    int length = 0;
    if (argc < 2) {
        printf("Incorrect input format\n");
        return 0;
    }
    if (strcmp(argv[1], "-fi") == 0) {
        if (argc != 3) {
            printf("Incorrect input format\n");
            return 0;
        }
        f1 = fopen(argv[2], "r");
        if (!f1) {
            printf("The file does not exist\n");
            return 0;
        }

        length = do_flag_fi(f1, names);
        if (length != -1) {
            make_fin_file(final, names, length);
        } else {
            printf("There is a file that cannot be opened\n");
            return 0;
        }

    } else if (strcmp(argv[1], "-cin") == 0) {
        if (argc != 2) {
            printf("Incorrect input format\n");
            return 0;
        }
        length = do_flag_cin(names);
        if (length != -1) {
            make_fin_file(final, names, length);
        } else {
            printf("There is a file that cannot be opened\n");
            return 0;
        }
    } else if (strcmp(argv[1], "-arg") == 0) {
        if (argc < 3) {
            printf("Incorrect input format\n");
            return 0;
        }
        length = do_flag_arg(names, argc, argv);
        if (length != -1) {
            make_fin_file(final, names, length);
        } else {
            printf("There is a file that cannot be opened\n");
            return 0;
        }
    }
    else {
        printf("There is no such flag");
        return 0;
    }
    return 0;
}
