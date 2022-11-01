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

int check_course(char* course, int len) {
    if (len != 2) {
        return incor_word;
    }
    if (!isdigit(course[0])) {
        return incor_word;
    }
    int q = course[0] - '0';
    if (q >= 1 && q <= 4) {
        return its_ok;
    }
    return incor_word;
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

int try_to_fill_stud(Student** all, char* my_string, int length_str, int* sz, int* true_len) {
    // printf("###%d", **true_len);
    Student one_man;
    Student* temp = NULL;
    int ex = 0;
    int size_id = 0, size_name = 0, size_surname = 0, size_course = 0;
    int size_group = 0, size_piece = 0, size_mark = 0;

    char *id = NULL, *name = NULL, *surname = NULL, *course = NULL, *group = NULL, *piece = NULL, *mark = NULL;
    int* marks = NULL;

    int a, i = 0, j = 0, size_marks = 5, one_mark = 0, ww = 0;

    int where = 0;
    char *best_ptr = my_string;

    if (*sz == 0) {
        // printf("wtfffffffff\n");
        *sz = 1;
        temp = (Student*)realloc(*all, sizeof(Student) * (*sz));
        if (!temp) {
            printf("nop\n");
        } 
        *all = temp;
    }
    if (*sz == *true_len) {
        (*sz) *= 2;
        temp = (Student*)realloc(*all, sizeof(Student) * (*sz));
        if (!temp) {
            free(*all);
        } else {
            *all = temp;
        }
    
    }
    // printf("1111\n");
    skip(&best_ptr);
    // printf("%d\n", *true_len);
    where = fill_word(&id, &best_ptr, &size_id);
    // one_man.id = atoi(id);
    ex = check_id(id, where);
    if (ex == incor_word) {
        free(id);
        return incor_word;
    }
    (*all)[*true_len].id = atoi(id);
    free(id);
    skip(&best_ptr);
    // printf("%d", (*all)[**true_len].id);
    

    where = fill_word(&name, &best_ptr, &size_name);
    // one_man.name = (char*)malloc(sizeof(char) * where);
    ex = check_name(name, where);
    if (ex == incor_word) {
        // free(id);
        free(name);
        return incor_word;
    }
    (*all)[*true_len].name = (char*)malloc(sizeof(char) * where);
    strcpy((*all)[*true_len].name, name);
    free(name);
    skip(&best_ptr);

    where = fill_word(&surname, &best_ptr, &size_surname);
    // one_man.surname = (char*)malloc(sizeof(char) * where);
    ex = check_name(surname, where);
    if (ex == incor_word) {
        // free(id);
        // free(name);
        free((*all)[*true_len].name);
        free(surname);
        return incor_word;
    }
    (*all)[*true_len].surname = (char*)malloc(sizeof(char) * where);
    strcpy((*all)[*true_len].surname, surname);
    free(surname);
    skip(&best_ptr);

    where = fill_word(&course, &best_ptr, &size_course);
    // one_man.course = atoi(course);
    ex = check_course(course, where);
    if (ex == incor_word) {
        // free(id);
        // free(name);
        free((*all)[*true_len].name);
        // free(surname);
        free((*all)[*true_len].surname);
        free(course);
        return incor_word;
    }
    (*all)[*true_len].course = atoi(course);
    free(course);
    skip(&best_ptr);

    where = fill_word(&group, &best_ptr, &size_group);
    // one_man.group = (char*)malloc(sizeof(char) * where);
    
    // ex = check_course(group, where);
    // if (ex == incor_word) {
    //     free(id);
    //     free(name);
    //     free((*all)[*true_len].name);
    //     free(surname);
    //     free((*all)[*true_len].surname);
    //     free(course);
    //     return incor_word;
    // }

    (*all)[*true_len].group = (char*)malloc(sizeof(char) * where);
    strcpy((*all)[*true_len].group, group);
    free(group);
    skip(&best_ptr);
    
    // printf("id: %d | name: %s | surname: %s | course: %d | group: %s | marks: ", (*all)[*true_len].id, (*all)[*true_len].name, (*all)[*true_len].surname, (*all)[*true_len].course, (*all)[*true_len].group);
    
    (*all)[*true_len].marks = (int*)malloc(sizeof(int) * 5);
    for (int i = 0; i < 5; i++) {
        if (!isspace(*best_ptr)) {
            one_mark = *best_ptr - '0';
            if (one_mark >= 2 && one_mark <= 5) {
                (*all)[*true_len].marks[i] = *best_ptr - '0';
            }
            best_ptr++;
        }
       
        // where = fill_word(&mark, &best_ptr, &size_mark);
        // ex = check_id(mark, where);
        // if (ex == incor_word) {
        //     free(id);
        //     free(name);
        //     free((*all)[*true_len].name);
        //     free(surname);
        //     free((*all)[*true_len].surname);
        //     free(course);
        //     free(group);
        //     free((*all)[*true_len].group);
        //     free(mark);
        //     return incor_word;
        // }
        // ww = atoi(mark);
        // printf("%s\n", mark);
        // printf("-%d", ww);
        // if (ww < 2 | ww > 5) {
        //     free(id);
        //     free(name);
        //     free((*all)[*true_len].name);
        //     free(surname);
        //     free((*all)[*true_len].surname);
        //     free(course);
        //     free(group);
        //     free((*all)[*true_len].group);
        //     free(mark);
        //     return incor_word;
        // }
        // (*all)[*true_len].marks[i] = ww;
        // free(mark);
        // size_mark = 0;
        skip(&best_ptr);
    }
    // printf("here\n");
    (*true_len)++;
    // for (int i = 0; i < 5; i++) {
    //     printf("%d ", one_man.marks[i]);
    // }
    return its_ok;
}

int read_from_file(Student** studs, int* num_stud, int* size, FILE *f1, int* true_len) {

    int count = 1, flag = 1, x = 0, length_str = 0, size_all = 0, sz = 0, okk = *true_len;
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
            // printf("wtf\n");
            flag = try_to_fill_stud(&all, my_string, length_str, &sz, &okk);
            // if (flag == incor_word) {

            // }
            // printf("--wtf\n");
            free(my_string);
            length_str = 0;
        }
    }
    *true_len = okk;
    *studs = all;
    return 0;
}

double find_avg(int* mass) {
    double total = 0.0;
    for (int i = 0; i < 5; i++) {
        total += mass[i];
    }
    total /= 5;
    return total;
}

Student* find_by_id(Student* arr, int size, int id, int* s) {
    int count = 0, j = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].id == id) {
            count++;
        }
    }
    if (count == 0) {
        return NULL;
    }
    Student* itog = (Student*)malloc(sizeof(Student) * count);
    for (int i = 0; i < size; i++) {
        if (arr[i].id == id) {
            itog[j].id = arr[i].id;
            itog[j].name = arr[i].name;
            itog[j].surname = arr[i].surname;
            itog[j].course = arr[i].course;
            itog[j].group = arr[i].group;
            itog[j].marks = arr[i].marks;
            j++;
        }
    }
    *s = count;
    return itog;
}

Student* find_by_name(Student* arr, int size, char* word, int* s) {
    int count = 0, j = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].name, word) == 0) {
            count++;
        }
    }
    if (count == 0) {
        return NULL;
    }
    Student* itog = (Student*)malloc(sizeof(Student) * count);
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].name, word) == 0) {
            itog[j].id = arr[i].id;
            itog[j].name = arr[i].name;
            itog[j].surname = arr[i].surname;
            itog[j].course = arr[i].course;
            itog[j].group = arr[i].group;
            itog[j].marks = arr[i].marks;
            j++;
        }
    }
    *s = count;
    return itog;
}

Student* find_by_surname(Student* arr, int size, char* word, int* s) {
    int count = 0, j = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].surname, word) == 0) {
            count++;
        }
    }
    if (count == 0) {
        return NULL;
    }
    Student* itog = (Student*)malloc(sizeof(Student) * count);
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].surname, word) == 0) {
            itog[j].id = arr[i].id;
            itog[j].name = arr[i].name;
            itog[j].surname = arr[i].surname;
            itog[j].course = arr[i].course;
            itog[j].group = arr[i].group;
            itog[j].marks = arr[i].marks;
            j++;
        }
    }
    *s = count;
    return itog;
}

int cmp_id(const void *a, const void *b)
{
    const Student *p1 = a;
    const Student *p2 = b;
    return p1->id - p2->id;
}

int cmp_name(const void *a, const void *b)
{
    const Student *p1 = a;
    const Student *p2 = b;
    return strcmp(p1->name, p2->name);
}

int cmp_sur(const void *a, const void *b)
{
    const Student *p1 = a;
    const Student *p2 = b;
    return strcmp(p1->surname, p2->surname);
}

int cmp_gr(const void *a, const void *b)
{
    const Student *p1 = a;
    const Student *p2 = b;
    return strcmp(p1->group, p2->group);
}

void group(Student* arr, int size, char* path) {
    char *name = NULL, c[2], sl[2];
    FILE *file;
    double tot = 0;
    sl[0] = '/';
    sl[1] = '\0';
    for (int i = 0; i < size; i++) {
        tot += find_avg(arr[i].marks);
    }
    tot /= size;
    // printf("%lf\n", tot);
    for (int i = 0; i < size; i++) {
        if (find_avg(arr[i].marks) > tot) {
            c[0] = arr[i].course + '0';
            c[1] = '\0';
            name = (char*)calloc(70, sizeof(char));
            strcat(name, path);
            strcat(name, sl);
            strcat(name, c);
            strcat(name,".txt");
            // printf("%s\n", name);
            file = fopen(name, "a");
            fprintf(file, "id: %3d | name: %12s | surname: %12s | course: %2d | group: %12s | avg_mark: %lf\n", arr[i].id, arr[i].name, arr[i].surname, arr[i].course, arr[i].group, find_avg(arr[i].marks));
            fclose(file);
            free(name);
            // printf("%s\n", arr[i].name);
        }
    }
}
 
void print_stud(Student* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("id: %3d | name: %12s | surname: %12s | course: %2d | group: %12s | avg_mark: %lf\n", arr[i].id, arr[i].name, arr[i].surname, arr[i].course, arr[i].group, find_avg(arr[i].marks));
    }
}

void free_stud(Student* arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i].name);
        free(arr[i].surname);
        free(arr[i].group);
        free(arr[i].marks);
    }
    free(arr);
}

int main(int argc, char* argv[]) {
    int num_stud = 0, size = 0, true_len = 0, yy, s = 0;
    int code, choice, sec_choice;
    char c;
    char* word;
    Student* studs = NULL;
    Student* found = NULL;
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
    code = read_from_file(&studs, &num_stud, &size, f1, &true_len);
    printf("1 - Find students\n");
    printf("2 - Sort students\n");
    printf("3 - Group students by their courses\n");
    scanf("%d", &choice);
    if (choice == 1) {
        printf("\n1 - Find by id:\n");
        printf("2 - Find by name:\n");
        printf("3 - Find by surname:\n");
        scanf("%d", &sec_choice);
        if (sec_choice == 1) {
            printf("Enter id:\n");
            if (scanf("%d%c", &yy, &c) == 2 && c == '\n') {
                found = find_by_id(studs, true_len, yy, &s);
                if (found == NULL) {
                    printf("There aren't students with entered id\n");
                    free_stud(studs, true_len);
                    fclose(f1);
                    return -1;
                }

            } else {
                printf("You didn't enter a number\n");
                free_stud(studs, true_len);
                fclose(f1);
                return -1;
            }
        } else if (sec_choice == 2) {
            printf("Enter name:\n");
            scanf("%s", word);
            found = find_by_name(studs, true_len, word, &s);
            if (found == NULL) {
                printf("There aren't students with entered name\n");
                free_stud(studs, true_len);
                fclose(f1);
                return -1;
            }
            
        } else if (sec_choice == 3) {
            printf("Enter surname:\n");
            scanf("%s", word);
            found = find_by_surname(studs, true_len, word, &s);
            if (found == NULL) {
                printf("There aren't students with entered surname\n");
                free_stud(studs, true_len);
                fclose(f1);
                return -1;
            }
        } else {
            printf("Incorrect choice\n");
            free_stud(studs, true_len);
            fclose(f1);
            return -1;
        }
        print_stud(found, s);
        free_stud(studs, true_len);
        free(found);
        fclose(f1);
        return 0;

    } else if (choice == 2) {
        printf("\n1 - Sort by id:\n");
        printf("2 - Sort by name:\n");
        printf("3 - Sort by surname:\n");
        printf("4 - Sort by group:\n");
        scanf("%d", &sec_choice);
        if (sec_choice == 1) {
            qsort(studs, true_len, sizeof(Student), cmp_id);
        } else if (sec_choice == 2) {
            qsort(studs, true_len, sizeof(Student), cmp_name);
        } else if (sec_choice == 3) {
            qsort(studs, true_len, sizeof(Student), cmp_sur);
        } else if (sec_choice == 4) {
            qsort(studs, true_len, sizeof(Student), cmp_gr);          
        } else {
            printf("Incorrect choice\n");
            free_stud(studs, true_len);
            fclose(f1);
            return -1;
        }
        print_stud(studs, true_len);
        free_stud(studs, true_len);
        fclose(f1);
        return 0;

    } else if (choice == 3) {
        group(studs, true_len, "/home/german/fundi/lab3/exer5");
        free_stud(studs, true_len);
        fclose(f1);
        return 0;
    } else {
        printf("wrong choice\n");
        free_stud(studs, true_len);
        fclose(f1);
        return -1;
    }
    print_stud(studs, true_len);
    free_stud(studs, true_len);
    fclose(f1);
    return 0;
}
