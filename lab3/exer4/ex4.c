#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    char* mes;
    int lenght;
} Message;

enum error{
    its_ok = 1,
    not_allocated = -1,
    incor_word = -2,
    no_memmory = -3,
    find_stop = -4
};

char* create_name_csv() {
    int len, choice, ch1;
    char q;
    len = 1 + rand()%15;
    char* word = (char*)malloc(sizeof(char) * (len + 5));
    if (word == NULL) {
        return NULL;
    }
    if (word == NULL) {
        return NULL;
    }
    char* ptr = word;
    for (int i = 0; i < len; i++) {
        choice = rand()%2;
        if (choice == 1) {
            ch1 = rand()%26;
            q = 'a' + ch1;
        } else {
            ch1 = rand()%10;
            q = '0' + ch1;
        }
        *ptr++ = q;
    }
    *ptr = '\0';
    strcat(word, ".csv");
    return word;
}

int check_for_stop(char* sent, char* word) {
    int len = strlen(word);
    int j = 0;
    for (int i = 0; sent[i] != '\0'; i++) {
        if (sent[i] == word[j] && j == 0) {
            j++;
            continue;
        } else if (sent[i] == word[j] && j < len - 1) {
            j++;
            continue;
        } else if (sent[i] == word[j] && j == len - 1) {
            return 1;
        } else {
            j = 0;
        }
    }
    return 0;
    
}

int join_char(char **str, char c, int* size) {
    char* tmp;
	if (*size == 0) {
		*size = 2;
		*str = (char*)malloc(sizeof(char) * *size);
		if (!*str) {
			return no_memmory;
		}

		(*str)[0] = c;
		(*str)[1] = '\0';

		return its_ok;
	}

	if (strlen(*str) == *size - 1) {
		*size *= 2;
		tmp = (char*)realloc(*str, sizeof(char) * *size);
		if (!tmp) {
            free(*str);
            return not_allocated;
        } else {
            *str = tmp;
        }
	}

	(*str)[strlen(*str) + 1] = '\0';
	(*str)[strlen(*str)] = c;
    
	return its_ok;
}


void print_and_free_arr(Message* mes, int num_rows) {
    for (int i = 0; i < num_rows; i++) {
        printf("id: %d | message: %s | length: %d\n", mes[i].id, mes[i].mes, mes[i].lenght);
        free(mes[i].mes);
    }
    free(mes);
}



char* getstr(FILE *file) {
    int id = 0, size_sent = 0, flag = 0, ex;
    char c = fgetc(file);
    char* sentence = NULL;
    flag = join_char(&sentence, c, &size_sent);
    if (flag == no_memmory || flag == not_allocated) {
        return NULL;
    }
    // char* word = NULL;
    while ((c = fgetc(file)) != '\n') {
        flag = join_char(&sentence, c, &size_sent);
        if (flag == no_memmory || flag == not_allocated) {
            return NULL;
        }
    }
    return sentence;
}

int validation(char* string) {
    char* ptr = string;
    while (*ptr++) {
        if (*ptr == ',' || *ptr == ';' || *ptr == '"') {
            return incor_word;
        }
    }
    return its_ok;
}

int fill_csv(FILE *f1, char* stopword, int* num_rows) {
    int size = 0, num_word = 0, ex = 0, test, attempt, attempts_left = 3, id = 1;
    char c;
    char* sentence = NULL;
    while (ex != 1) {
        sentence = getstr(stdin);
        if (sentence == NULL) {
            return no_memmory;
        }
        attempt = validation(sentence);
        if (attempt == its_ok) {
            ex = check_for_stop(sentence, stopword);
            if (ex == 1) {
                free(sentence);
                *num_rows = id;
                break;
            }
            int g = strlen(sentence);
            fprintf(f1, "%d,%s,%d\n", id, sentence, g);
            id++;
            free(sentence);
        } else {
            attempts_left--;
            printf("Your last message was incorrect. There are %d attempts left:\n", attempts_left);
            if (attempts_left == 0) {
                free(sentence);
                *num_rows = id;
                break;
            }
            free(sentence);
        }
    }
    return its_ok;
}

int csv_to_arr(Message** mes, int num_rows, char* filename) {
    Message one;
    Message* all = (Message*)malloc(sizeof(Message) * num_rows);
    if (all == NULL) {
        return no_memmory;
    }
    int co1 = 0, co2 = 0, q = 0, llll, fl1, fl2, fl3;
    char* hey = NULL;
    FILE *csv = fopen(filename, "r");
    char* id_1 = NULL, *mes_1 = NULL, *len_1 = NULL;
    int id_1_size = 0, mes_1_size = 0, len_1_size = 0;
    char* str;
    for (int i = 0; i < num_rows - 1; i++) {
        str = getstr(csv);
        if (str == NULL && i != 0) {
            print_and_free_arr(all, i-1);
            fclose(csv);
            return no_memmory;
        } else if (str == NULL && i == 0) {
            free(all);
            fclose(csv);
            return no_memmory;
        }
        char *p1 = str;
        co1 = 0;
        co2 = 0;
        q = 0;
        while (*p1) {
            q++;
            if (co1 > 0 && co2 == 0 && *p1 != ',') {
                fl2 = join_char(&mes_1, *p1, &id_1_size);
                if (fl2 == not_allocated || fl2 == no_memmory) {
                    print_and_free_arr(all, i-1);
                    fclose(csv);
                    return no_memmory;
                }
            }

            if (*p1 == ',' && co1 == 0) {
                co1 = q;
            } else if (*p1 == ',' && co1 > 0 && co2 == 0) {
                co2 = q;
            }
            p1++;
        }
        for (int i = 0; i < co1 - 1; i++) {
            fl1 = join_char(&id_1, str[i], &mes_1_size);
            if (fl1 == not_allocated || fl2 == no_memmory) {
                print_and_free_arr(all, i-1);
                free(mes_1);
                fclose(csv);
                return no_memmory;
            }
        }
        for (int i = co2; i < q; i++) {
            fl3 = join_char(&len_1, str[i], &len_1_size);
            if (fl3 == not_allocated || fl2 == no_memmory) {
                print_and_free_arr(all, i-1);
                free(mes_1);
                free(id_1);
                fclose(csv);
                return no_memmory;
            }
        }
        // printf("%s\n%s\n%s\n\n", id_1, mes_1, len_1);
        one.id = atoi(id_1);
        one.lenght = atoi(len_1);
        one.mes = (char*)malloc(sizeof(char) * (one.lenght + 1));
        if (one.mes == NULL) {
            print_and_free_arr(all, i-1);
            free(id_1);
            free(mes_1);
            free(len_1);
            fclose(csv);
            return no_memmory;
        }
        strcpy(one.mes, mes_1);
        all[i] = one;

        free(id_1);
        free(mes_1);
        free(len_1);
        free(str);
        id_1_size = 0;
        mes_1_size = 0;
        len_1_size = 0;

    }
    fclose(csv);
    *mes = all;
    return its_ok;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int num_rows = 1, how = 0, ll = 0;
    Message* mes = NULL;
    if (argc != 2) {
        printf("No stopword!\n");
        return 1;
    }
    FILE *f1;

    char* file_name = create_name_csv();
    if (file_name == NULL) {
        printf("The file was not created because the memory was not allocated\n");
        return -1;
    }

    f1 = fopen(file_name, "a");
    ll = fill_csv(f1, argv[1], &num_rows);
    if (ll == no_memmory) {
        free(file_name);
        return -1;
    }
    fclose(f1);

    how = csv_to_arr(&mes, num_rows, file_name);
    if (how == no_memmory) {
        free(file_name);
        return -1;
    }
    print_and_free_arr(mes, num_rows-1);
    free(file_name);
    return 0;
}
