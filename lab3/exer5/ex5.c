#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    char* name;
    char* surname;
    int course;
    char* group;
    int* marks;
} Student;

enum error{
    its_ok = 1,
    not_allocated = -1,
    incor_word = -2,
    no_memmory = -3,
    end_of_file = -4
};

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
        if (isspace(**ptr)) {
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

int try_to_fill_stud(Student** all, char* my_string, int length_str) {
    Student one_man;

    int full_id = 0, full_name = 0, full_surname = 0, full_course = 0;
    int full_group = 0, full_marks = 0;

    int size_id = 0, size_name = 0, size_surname = 0, size_course = 0;
    int size_group = 0, size_piece = 0;

    char *id = NULL, *name = NULL, *surname = NULL, *course = NULL, *group = NULL, *piece = NULL;
    int* marks = NULL;

    int a, i = 0, j = 0, size_marks = 5;
    marks = (int*)malloc(sizeof(int) * size_marks);
    int* ptr = marks;
    char block = 0;

    int where = 0;
    char *best_ptr = my_string;

    skip(&best_ptr);

    where = fill_word(&id, &best_ptr, &size_id);
    one_man.id = atoi(id);
    free(id);
    skip(&best_ptr);

    where = fill_word(&name, &best_ptr, &size_name);
    one_man.name = (char*)malloc(sizeof(char) * where);
    strcpy(one_man.name, name);
    free(name);
    skip(&best_ptr);

    where = fill_word(&surname, &best_ptr, &size_surname);
    one_man.surname = (char*)malloc(sizeof(char) * where);
    strcpy(one_man.surname, surname);
    free(surname);
    skip(&best_ptr);

    where = fill_word(&course, &best_ptr, &size_course);
    one_man.course = atoi(course);
    free(course);
    skip(&best_ptr);

    where = fill_word(&group, &best_ptr, &size_group);
    one_man.group = (char*)malloc(sizeof(char) * where);
    strcpy(one_man.group, group);
    free(group);
    skip(&best_ptr);
    
    printf("id: %d | name: %s | surname: %s | course: %d | group: %s | marks: ", one_man.id, one_man.name, one_man.surname, one_man.course, one_man.group);
    
    one_man.marks = (int*)malloc(sizeof(int) * 5);
    for (int i = 0; i < 5; i++) {
        if (!isspace(*best_ptr)) {
            one_man.marks[i] = *best_ptr - '0';
            best_ptr++;
        }
        skip(&best_ptr);
    }

    for (int i = 0; i < 5; i++) {
        printf("%d ", one_man.marks[i]);
    }

    printf("\n");
    free(one_man.name);
    free(one_man.surname);
    free(one_man.group);
    free(one_man.marks);
    free(marks);
    return its_ok;
}

int read_from_file(Student** studs, int* num_stud, int* size, FILE *f1) {

    int count = 1, flag = 1, x = 0, length_str = 0, size_all = 0;
    char* my_string = NULL;
    Student* all = NULL;

    while (x != end_of_file) {
        x = takestr(f1, &my_string, &length_str);
        if (x != end_of_file) {
            count = count_words(my_string);
            if (count != 10) {
                free(my_string);
                length_str = 0;
                continue;
            }
            flag = try_to_fill_stud(&all, my_string, length_str);
            free(my_string);
            length_str = 0;
        }
    }
}



int main(int argc, char* argv[]) {
    int num_stud = 0, size = 0;
    int code;
    Student* studs = NULL;
    FILE *f1;
    // if (argc != 2) {
    //     printf("No file path\n");
    //     return -1;
    // }
    f1 = fopen("jopa.txt", "r");
    if (!f1) {
        printf("File does not exist\n");
        return -1;
    }
    code = read_from_file(&studs, &num_stud, &size, f1);
    fclose(f1);
    return 0;
}
