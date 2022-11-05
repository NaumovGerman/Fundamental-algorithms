#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum error{
    its_ok = 1,
    not_allocated = -1,
    incor_word = -2,
    no_memmory = -3,
    end_of_file = -4
};

typedef struct {
    int id;
    char* name;
    char* surname;
    double salary;
} employee;


int check_id(char* id, int len) {
    for (int i = 0; i < len - 1; i++) {
        if (!isdigit(id[i])) {
            return incor_word;
        }
    }
    return its_ok;
}

int check_name(char* name, int len) {
    for (int i = 0; i < len - 1; i++) {
        if (!isalpha(name[i])) {
            return incor_word;
        }
    }
    return its_ok;
}

int check_salary(char* sal, int len) {
    int count = 0;
    for (int i = 0; i < len - 1; i++) {
        if (!isdigit(sal[i])) {
            if (sal[i] == '.') {
                count++;
            } else {
                return incor_word;
            }
        }
    }
    if (count != 1) {
        return incor_word;
    }
    return its_ok;
}

int join_char(char **str, char c, int* size) {
    char* tmp;
    if (c == '\0') {
        return its_ok;
    }
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

int takestr(FILE *file, char** string, int* len) {
    char* temp = NULL;
    int id = 0, size_sent = 0, flag = 0, ex;
    char c = fgetc(file);
    if (c == EOF) {
        return end_of_file;
    }
    
    char* sentence = NULL;
    flag = join_char(&temp, c, &size_sent);
    if (flag == no_memmory || flag == not_allocated) {
        return no_memmory;
    }
    (*len)++;
    // char* word = NULL;
    while ((c = fgetc(file)) != '\n') {
        if (c == EOF) {
            *string = temp;
            return end_of_file;
        }
        flag = join_char(&temp, c, &size_sent);
        if (flag == no_memmory || flag == not_allocated) {
            return no_memmory;
        }
        (*len)++;
    }
    *string = temp;
    return its_ok;
}

int count_words(char* my_string) {
    int count = 0, flag = 0;
    for (int i = 0; my_string[i] != '\0'; i++) {
        if (isspace(my_string[i])) {
            flag = 0;
        } else {
            if (flag == 0) {
                count++;
                flag = 1;
            }
        }
        if (my_string[i] == '\0') {
            break;
        }
    }
    return count;
}

void skip(char **ptr) {
    while (1) {
        if (**ptr == ' ') {
            (*ptr)++;
        } else {
            break;
        }
    }
}

int fill_word(char** word, char **ptr, int *size) {
    int a, true_len = 1;
    while (1) {
        if (isspace(**ptr)) {
            break;
        }
        a = join_char(&(*word), **ptr, &(*size));
        true_len++;
        (*ptr)++;
    }
    return true_len;
}

int prfill_word(char** word, char **ptr, int *size) {
    int a, true_len = 1;
    while (1) {
        if (**ptr == '\n' || **ptr == ' ') {
            break;
        }
        a = join_char(&(*word), **ptr, &(*size));
        // printf("%c\n", **ptr);
        // if (**ptr = '\n') {
        //     true_len++;
        //     (*ptr)++;
        //     break;
        // }
        true_len++;
        (*ptr)++;
    }
    return true_len;
}

int try_to_fill_stud(employee** all, char* my_string, int length_str, int* sz, int* true_len) {
    // printf("###%d", **true_len);
    employee one_man;
    employee* temp = NULL;
    int ex = 0;
    int size_id = 0, size_name = 0, size_surname = 0, size_salary = 0;

    char *id = NULL, *name = NULL, *surname = NULL, *salary = NULL;

    int a, i = 0, j = 0, size_marks = 5, one_mark = 0, ww = 0;

    int where = 0;
    char *best_ptr = my_string;

    if (*sz == 0) {
        // printf("wtfffffffff\n");
        *sz = 1;
        temp = (employee*)realloc(*all, sizeof(employee) * (*sz));
        if (!temp) {
            printf("nop\n");
        } 
        *all = temp;
    }
    if (*sz == *true_len) {
        (*sz) *= 2;
        temp = (employee*)realloc(*all, sizeof(employee) * (*sz));
        if (!temp) {
            free(*all);
        } else {
            *all = temp;
        }
    
    }

    skip(&best_ptr);
    where = fill_word(&id, &best_ptr, &size_id);
    ex = check_id(id, where);
    if (ex == incor_word) {
        free(id);
        return incor_word;
    }
    (*all)[*true_len].id = atoi(id);
    free(id);
    skip(&best_ptr);
    

    where = fill_word(&name, &best_ptr, &size_name);
    ex = check_name(name, where);
    if (ex == incor_word) {
        free(name);
        return incor_word;
    }
    (*all)[*true_len].name = (char*)malloc(sizeof(char) * where);
    strcpy((*all)[*true_len].name, name);
    free(name);
    skip(&best_ptr);


    where = fill_word(&surname, &best_ptr, &size_surname);
    ex = check_name(surname, where);
    if (ex == incor_word) {
        free((*all)[*true_len].name);
        free(surname);
        return incor_word;
    }
    (*all)[*true_len].surname = (char*)malloc(sizeof(char) * where);
    strcpy((*all)[*true_len].surname, surname);
    free(surname);
    skip(&best_ptr);

    // where = fill_word(&salary, &best_ptr, &size_salary);
    printf("%c\n", *best_ptr);
    where = prfill_word(&salary, &best_ptr, &size_salary);
    printf("%s %d\n", salary, size_salary);
    ex = check_salary(salary, where);
    if (ex == incor_word) {
        free((*all)[*true_len].name);

        free((*all)[*true_len].surname);
        free(salary);
        return incor_word;
    }
    (*all)[*true_len].salary = atof(salary);
    free(salary);

    (*true_len)++;
    return its_ok;
}

int file_to_arr(employee** mankind, int *number_of_man, FILE *f1) {
    int size_for_mem = 0, cur_size = 0, x = 0, len_str = 0, count = 0, flag = 0;
    employee* all = NULL;
    char* my_string;

    while (x != end_of_file) {
        x = takestr(f1, &my_string, &len_str);
        if (x != end_of_file) {
            count = count_words(my_string);
            if (count != 4) {
                free(my_string);
                len_str = 0;
                continue;
            }
            // printf("wtf\n");
            flag = try_to_fill_stud(&all, my_string, len_str, &size_for_mem, &cur_size);
            // if (flag == incor_word) {

            // }
            // printf("--wtf\n");
            free(my_string);
            len_str = 0;
        }
    }
    *number_of_man = cur_size;
    *mankind = all;
    return 0;

}

void print_arr(employee* mankind, int len) {
    for (int i = 0; i < len; i++) {
        printf("id : %3d | name : %8s | surname : %7s | salary : %.2lf\n",
        mankind[i].id, mankind[i].name, mankind[i].surname, mankind[i].salary);
    }
}

void free_arr(employee* mankind, int len) {
    for (int i = 0; i < len; i++) {
        free(mankind[i].name);
        free(mankind[i].surname);
    }
    free(mankind);
}

int main(int argc, char* argv[]) {
    int ex = 0, number_of_man = 0;
    // if (argc != 3) {
    //     printf("Incorrect arguments\n");
    //     return -1;
    // }
    employee *mankind;
    FILE *f1;
    f1 = fopen(argv[1], "r");
    if (f1 == NULL) {
        printf("There is no such file\n");
        return -1;
    }

    ex = file_to_arr(&mankind, &number_of_man, f1);
    print_arr(mankind, number_of_man);
    free_arr(mankind, number_of_man);
    fclose(f1);

    // if (strcmp("-a", argv[2]) == 0 || strcmp("/a", argv[2]) == 0) {
    //     do some short;
    // } else if (strcmp("-d", argv[2]) == 0 || strcmp("/d", argv[2]) == 0) {
    //     do some sort;
    // } else {
    //     printf("Incorrect flag\n");
    //     free everything;
    //     return -1;
    // }
    return 0;
}
