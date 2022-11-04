#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Node Node;

enum error{
    its_ok = 1,
    not_allocated = -1,
    incor_word = -2,
    no_memmory = -3,
    end_of_file = -4
};

enum sex{
    M = 1,
    F = 2
};

typedef struct {
    char* surname;
    char* name;
    char* patronymic;
    char* birth_date;
    enum sex gender;
    double salary;
} Person;

typedef struct Node {
    Person human;
    Node *next;
} Node;

typedef struct {
    Node *head;
} list;


int compare_dates(char* first, char* second) {
    int a;
    char year1[5], month1[3], day1[3]; // 1 2 . 1 1 . 2 0 0 3 \0
    char year2[5], month2[3], day2[3]; // 0 1 2 3 4 5 6 7 8 9 10
    year1[0] = first[6];
    year1[1] = first[7];
    year1[2] = first[8];
    year1[3] = first[9];
    year1[4] = '\0';

    year2[0] = second[6];
    year2[1] = second[7];
    year2[2] = second[8];
    year2[3] = second[9];
    year2[4] = '\0';
    a = strcmp(year1, year2);
    if (a > 0) {
        return 1;
    } else if (a < 0) {
        return -1;
    }
    month1[0] = first[3];
    month1[1] = first[4];
    month1[2] = '\0';

    month2[0] = second[3];
    month2[1] = second[4];
    month2[2] = '\0';

    a = strcmp(month1, month2);
    if (a > 0) {
        return 1;
    } else if (a < 0) {
        return -1;
    }

    day1[0] = first[0];
    day1[1] = first[1];
    day1[2] = '\0';

    day2[0] = second[0];
    day2[1] = second[1];
    day2[2] = '\0';

    a = strcmp(day1, day2);
    if (a < 0) {
        return -1;
    } else {
        return 1;
    }

    // strcmp("2003", "2004") = -1;
    // strcmp("2003", "2002") = 1;
}

void person_free(Person one) {
    free(one.surname);
    free(one.name);
    free(one.patronymic);
    free(one.birth_date);
}

int create_node(list** ls, Person man) {
    *ls = (list*)malloc(sizeof(list));
    if (*ls == NULL) {
        return no_memmory;
    }

    (*ls)->head = (Node*)malloc(sizeof(Node));
    if ((*ls)->head == NULL) {
        free(*ls);
        return no_memmory;
    }


    (*ls)->head->human = man;
    (*ls)->head->next = NULL;
    return its_ok;
}

int add_node(list** ls, Person man) {
    int ccc;

    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL) {
        return no_memmory;
    }

    temp->human = man;
    temp->next = NULL;

    
    Node *cur = (*ls)->head;
    ccc = compare_dates(cur->human.birth_date, man.birth_date);
    if (ccc > 0) {
        temp->next = (*ls)->head;
        (*ls)->head = temp;
    } else {
        while (cur->next != NULL) {
            ccc = compare_dates(cur->next->human.birth_date, man.birth_date);
            if (ccc > 0) {
                temp->next = cur->next;
                cur->next = temp;
                return 1;
            }
            cur = cur->next;
        }
        cur->next = temp;
        temp->next = NULL;
    }
    return its_ok;

}

int find_node(list** ls, char* word, Person* one) {
    int a;
    a = strcmp(word, (*ls)->head->human.surname);
    if (a == 0) {
        return 1;
    } else {
        Node *cur = (*ls)->head;
        while (cur->next != NULL) {
            a = strcmp(word, cur->next->human.surname);
            if (a == 0) {
                *one = cur->next->human;
                return 1;
            }
            cur = cur->next;
        }
        return -1;
    }
}

int delete_node(list** ls, char* word) {
    Node* temp = NULL;
    int a;
    a = strcmp(word, (*ls)->head->human.surname);
    if (a == 0) {
        if ((*ls)->head->next != NULL) {
            temp = (*ls)->head;
            (*ls)->head = (*ls)->head->next;
            person_free(temp->human);
            free(temp);
        } else {
            person_free((*ls)->head->human);
            free((*ls)->head);
        }
    } else {
        Node *cur = (*ls)->head;
        while (cur->next != NULL) {
            a = strcmp(word, cur->next->human.surname);
            if (a == 0) {
                temp = cur->next;
                if (cur->next->next != NULL) {
                    cur->next = cur->next->next;
                } else {
                    cur->next = NULL;
                }
                person_free(temp->human);
                free(temp);
                return 1;
            }
            cur = cur->next;
        }
        return -1;
    }
}
 
void ls_print(list* my_list) {
    Node* cur = my_list->head;
    while (cur->next != NULL) {
        // printf("%s ", cur->human.surname);
        // printf("%s ", cur->human.name);
        // printf("%s ", cur->human.patronymic);
        // printf("%s ", cur->human.birth_date);
        // printf("%d ", cur->human.gender);
        // printf("%lf\n", cur->human.salary);
        printf("Surname : %7s | Name : %8s | Patronymic : %17s | Birth date : %11s ", cur->human.surname, 
        cur->human.name, cur->human.patronymic, cur->human.birth_date);
        if (cur->human.gender == 1) {
            printf("| Gender : M | Salary : %.2lf\n", cur->human.salary);
        } else {
            printf("| Gender : F | Salary : %.2lf\n", cur->human.salary);
        }
        cur = cur->next;
    }
    // printf("%s ", cur->human.surname);
    // printf("%s ", cur->human.name);
    // printf("%s ", cur->human.patronymic);
    // printf("%s ", cur->human.birth_date);
    // printf("%d ", cur->human.gender);
    // printf("%lf\n", cur->human.salary);
    printf("Surname : %7s | Name : %8s | Patronymic : %17s | Birth date : %11s ", cur->human.surname, 
        cur->human.name, cur->human.patronymic, cur->human.birth_date);
        if (cur->human.gender == 1) {
            printf("| Gender : M | Salary : %.2lf\n", cur->human.salary);
        } else {
            printf("| Gender : F | Salary : %.2lf\n", cur->human.salary);
        }
}



void ls_free(list* my_list) {
    Node* cur = my_list->head;
    Node* tmp;

    while (cur->next != NULL) {
        tmp = cur;
        cur = cur->next;
        person_free(tmp->human);
        free(tmp);
    }
    person_free(cur->human);
    free(cur);
    
    free(my_list);
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

void skip(char **ptr) {
    while (1) {
        if (**ptr == ' ') {
            (*ptr)++;
        } else {
            break;
        }
    }
}

int check_name(char* name, int len) {
    for (int i = 0; i < len - 1; i++) {
        if (!isalpha(name[i])) {
            return incor_word;
        }
    }
    return its_ok;
}

int check_date(char* date, int len) {
    if (len != 11) {
        return incor_word;
    }
    for (int i = 0; i < len - 1; i++) {
        if (!isdigit(date[i])) {
            if (date[i] != '.') {
                return incor_word;
            }
        }
    }
    char d[3], m[3], y[5];
    int day, month, year;
    d[0] = date[0];
    d[1] = date[1];
    d[2] = '\0';
    day = atoi(d);
    if (day > 31) {
        return incor_word;
    }

    m[0] = date[3];
    m[1] = date[4];
    m[2] = '\0';
    month = atoi(m);
    if (month > 12) {
        return incor_word;
    }

    y[0] = date[6];
    y[1] = date[7];
    y[2] = date[8];
    y[3] = date[9];
    y[4] = '\0';
    
    year = atoi(y);
    if (year < 2000 || year > 2022) {
        return incor_word;
    }

    return its_ok;
}

int check_gend(char* gend, int len) {
    if (len != 2) {
        return incor_word;
    }
    if (gend[0] != 'M' && gend[0] != 'F') {
        return incor_word;
    }

    if (gend[0] == 'M') {
        return 1;
    } else {
        return 2;
    }
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

int try_to_fill_pers(Person *one, char* my_string, int *true_len) {
    char *surname = NULL, *name = NULL, *patronymic = NULL, *birth_date = NULL, *gend = NULL, *salary = NULL;
    int size_surname = 0, size_name = 0, size_patronymic= 0, size_date = 0, size_gend = 0, size_salary = 0;
    char *ptr = my_string;
    int where = 0, ex = 0;
    skip(&ptr);


    where = fill_word(&surname, &ptr, &size_surname);
    ex = check_name(surname, where);
    if (ex == incor_word) {
        free(surname);
        return incor_word;
    }
    one->surname = (char*)malloc(sizeof(char) * where);
    strcpy(one->surname, surname);
    free(surname);
    skip(&ptr);


    where = fill_word(&name, &ptr, &size_name);
    ex = check_name(name, where);
    if (ex == incor_word) {
        free(name);
        free(one->surname);
        return incor_word;
    }
    one->name = (char*)malloc(sizeof(char) * where);
    strcpy(one->name, name);
    free(name);
    skip(&ptr);


    where = fill_word(&patronymic, &ptr, &size_patronymic);
    ex = check_name(patronymic, where);
    if (ex == incor_word) {
        free(patronymic);
        free(one->surname);
        free(one->name);
        return incor_word;
    }
    one->patronymic = (char*)malloc(sizeof(char) * where);
    strcpy(one->patronymic, patronymic);
    free(patronymic);
    skip(&ptr);


    where = fill_word(&birth_date, &ptr, &size_date);
    ex = check_date(birth_date, where);
    if (ex == incor_word) {
        free(birth_date);
        free(one->surname);
        free(one->name);
        free(one->patronymic);
        return incor_word;
    }
    one->birth_date = (char*)malloc(sizeof(char) * where);
    strcpy(one->birth_date, birth_date);
    free(birth_date);
    skip(&ptr);
    

    where = fill_word(&gend, &ptr, &size_gend);
    ex = check_gend(gend, where);
    if (ex == incor_word) {
        free(gend);
        person_free(*one);
        return incor_word;
    }
    one->gender = M ? ex == 1 : F;
    free(gend);
    skip(&ptr);
    

    where = fill_word(&salary, &ptr, &size_salary);
    ex = check_salary(salary, where);
    if (ex == incor_word) {
        free(salary);
        person_free(*one);
        return incor_word;
    }
    one->salary = atof(salary);
    free(salary);

    (*true_len)++;
    return its_ok;

}


int read_from_file(list** my_list, Node** first, FILE *f1, int* num) {
    int x = 0, length_str = 0, count = 0, flag = 0, sz = 0, true_len = 0, ch = 0;
    char* my_string = NULL;
    list* temp = NULL;
    Person one;
    while (x != end_of_file) {
        x = takestr(f1, &my_string, &length_str);
        if (x != end_of_file) {
            count = count_words(my_string);
            if (count != 6) {
                free(my_string);
                length_str = 0;
                continue;
            }
            // printf("wtf\n");
            
            flag = try_to_fill_pers(&one, my_string, &true_len);
            if (flag == its_ok) {
                if (true_len == 1) {
                    ch = create_node(&temp, one);
                    if (ch == no_memmory) {
                        free(my_string);
                        person_free(one);
                        return no_memmory;
                    }
                    *first = temp->head;
                } else {
                    ch = add_node(&temp, one);
                    if (ch == no_memmory) {
                        free(*first);
                        ls_free(temp);
                        free(my_string);
                        person_free(one);
                        return no_memmory;
                    }
                }
                (*num)++;
            }
            
            free(my_string);
            length_str = 0;
        }
    }
    *my_list = temp;
    return its_ok;  
}


int main() {
    int code, num = 0, choice = 0, x = 0, len = 0, count = 0;
    int flag = 0, garbage = 0, ch = 0;
    Person in_main;
    FILE *f1;
    list* my_list;
    Node* first;
    // if (argc != 2) {
    //     printf("Incorrect input\n");
    //     return -1;
    // }
    f1 = fopen("people.txt", "r");
    if (!f1) {
        printf("No such file\n");
        return -1;
    }
    code = read_from_file(&my_list, &first, f1, &num);
    printf("Hello!");
    while (choice != 5) {
        printf("\n1 - Print linked list\n2 - Add user\n3 - Delete user\n4 - Find user by surname\n5 - Save list to a file and stop the program\nEnter: ");
        scanf("%d", &choice);
        if (choice == 1) {
            if (num != 0) {
                ls_print(my_list);
            } else {
                printf("Linked list is empty!\n");
            }
        } else if (choice == 2) {
            char* my_string;
            x = takestr(stdin, &my_string, &len);
            if (x == no_memmory) {
                printf("Memory was not allocatted\n");
                ls_free(my_list);
                fclose(f1);
                return -1;
            }
            count = count_words(my_string);
            if (count != 6) { 
                printf("Incorrect input!\n");
                free(my_string);
                len = 0;
                continue;
            }
            flag = try_to_fill_pers(&in_main, my_string, &garbage);
            if (flag == its_ok) {
                if (num == 0) {
                    ch = create_node(&my_list, in_main);
                    if (ch == no_memmory) {
                        free(my_string);
                        person_free(in_main);
                        ls_free(my_list);
                        printf("Memory was not allocatted\n");
                        fclose(f1);
                        return -1;
                    }
                    // first->next = my_list->head;
                    num++;
                } else {
                    ch = add_node(&my_list, in_main);
                    if (ch == no_memmory) {
                        free(my_string);
                        person_free(in_main);
                        ls_free(my_list);
                        printf("Memory was not allocatted\n");
                        fclose(f1);
                        return -1;
                    }
                    num++;
                }
            }
            len = 0;
            free(my_string);
        } else if (choice == 3) {
            char* surn;
            x = takestr(stdin, &surn, &len);
            if (x == no_memmory) {
                printf("Memory was not allocatted\n");
                ls_free(my_list);
                fclose(f1);
                return -1;
            }
            x = check_name(surn, len);
            printf("%s %d\n", surn, len);
            if (x == incor_word) {
                printf("Incorrect input!\n");
                free(surn);
                len = 0;
                continue;
            }
            x = delete_node(&my_list, surn);
            if (x == -1) {
                printf("There is no such man in list!\n");
                free(surn);
            } else {
                ls_print(my_list);
            }
            len = 0;
        } else if (choice == 4) {
            char* surn;
            x = takestr(stdin, &surn, &len);
            if (x == no_memmory) {
                printf("Memory was not allocatted\n");
                ls_free(my_list);
                fclose(f1);
                return -1;
            }
            // x = check_name(surn, len);
            // printf("%s\n", surn);
            // if (x == incor_word) {
            //     printf("Incorrect input!\n");
            //     free(surn);
            //     len = 0;
            //     continue;
            // }
            x = find_node(&my_list, surn, &in_main);
            if (x == -1) {
                printf("There is no such man in list!\n");
                free(surn);
            } else {
                printf("Found:\nSurname : %7s | Name : %8s | Patronymic : %17s | Birth date : %11s ", in_main.surname,
                in_main.name, in_main.patronymic, in_main.birth_date);
                if (in_main.gender == 1) {
                    printf("| Gender : M | Salary : %.2lf", in_main.salary);
                } else {
                    printf("| Gender : F | Salary : %.2lf", in_main.salary);
                }
                // ls_print(my_list);
            }
            person_free(in_main);
            free(surn);
            len = 0;
        } else if (choice == 5) {
            if (num != 0) {
                // ls_print(my_list);
                ls_free(my_list);
            } else {
                printf("Linked list is empty!\n");
            }
        }
    }
    // if (num != 0) {
    //     ls_print(my_list);
    //     ls_free(my_list);
    // } else {
    //     printf("Linked list is empty!\n");
    // }
    fclose(f1);
    return 0;
}
