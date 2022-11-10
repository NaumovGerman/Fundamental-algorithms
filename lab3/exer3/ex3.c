#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct Node Node;

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


typedef struct Node {
	employee* key;
	Node* parent;
	Node* child;
	Node* left;
	Node* right;
	int degree;
} Node;

typedef struct {
	int size;
	Node* min;
} fibonacci_heap;

/////////////////////////////////////////////////
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
        if (**ptr == '\0' || **ptr == ' ') {
            break;
        }
        a = join_char(&(*word), **ptr, &(*size));
        true_len++;
        (*ptr)++;
    }
    return true_len;
}

int try_to_fill_stud(employee** all, char* my_string, int length_str, int* sz, int* true_len) {
    employee one_man;
    employee* temp = NULL;
    int ex = 0;
    int size_id = 0, size_name = 0, size_surname = 0, size_salary = 0;

    char *id = NULL, *name = NULL, *surname = NULL, *salary = NULL;

    int a, i = 0, j = 0, size_marks = 5, one_mark = 0, ww = 0;

    int where = 0;
    char *best_ptr = my_string;

    if (*sz == 0) {
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

    where = fill_word(&salary, &best_ptr, &size_salary);
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
            my_string = NULL;
            len_str = 0;
        }
    }
    *number_of_man = cur_size;
    *mankind = all;
    return 0;
}

//////////////////////////////////////////////////

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

//-------------------------------------------------------------------------
int fib_insert(fibonacci_heap* heap, employee* node, int a) {
    if (!heap) {
		// return fibonacci_insert_heap_incorrect_heap_ptr;
	}
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL) {
        return no_memmory;
    }
    temp->key = node;
    temp->child = NULL;
    temp->parent = NULL;
    temp->degree = 0;
    if (heap->size == 0) {
        heap->min = temp;
        heap->min->left = temp;
        heap->min->right = temp;
    } else {
        Node* prev_right = heap->min->right;
        heap->min->right = temp;
        temp->left = heap->min;
        temp->right = prev_right;
        prev_right->left = temp;
    }
    // if (operation == '<' && (new_node->key->wage < heap->root->key->wage) || operation == '>' && (new_node->key->wage > heap->root->key->wage)) {
	// 	heap->root = new_node;
	// }
    if (a == 1 && (temp->key->salary < heap->min->key->salary)) {
        heap->min = temp;
    }
    (heap->size)++;
    return its_ok;
}


void union_lists(Node* first, Node* second) {
    Node* l = first->left;
    Node* r = second->right;
    second->right = first;
    first->left = second;
    l->right = r;
    r->left = l;
}
void fib_link(fibonacci_heap* heap, Node* x, Node* y) {
    y->left->right = y->right;
    y->right->left = y->left;
    y->left = NULL;
    y->right = NULL;
    if (x->child != NULL) {
        y->parent = x;
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    } else {
        x->child = y;
        y->parent = x;
        y->left = y;
        y->right = y;
    }
    (x->degree)++;
}

int fib_consolid(fibonacci_heap* heap, int a) {
    Node* helper = NULL;
    int num = log2(heap->size) + 1;
    Node** arr = (Node**)calloc(num, sizeof(Node*));

    if (arr == NULL) {
        return no_memmory;
    }

    for (int i = 0; i < num; i++) {
        arr[i] == NULL;
    }
    int degree = heap->min->degree;
    arr[degree] = heap->min;
    Node* current = heap->min;
    if (current->right != current) {
        current = current->right;
        for (int i = 0; i < num - 1; i++) {
            degree = current->degree;
            while (arr[degree] != NULL) {
                helper = arr[degree];
                if (helper == current) {
                    break;
                }
                if (a == 1 && current->key->salary > helper->key->salary) { // 1 = <
                    Node* temp = current;
                    current = helper;
                    helper = temp;
                }
                fib_link(heap, current, helper);
                arr[degree] = NULL;
                degree++;
            }
             if ((a == 1 && current->key->salary < helper->key->salary) && (current != heap->min)) { // 1 = <
                    heap->min = current;
            }
            if (helper != current) { // минус час жизни
                arr[degree] = current;
            }
            current = current->right;
        }
    }
    
    heap->min = NULL;
    for (int i = 0; i < num; i++) {
        if (arr[i] != NULL) {
            if (heap->min == NULL) {
                heap->min = arr[i];
                heap->min->left = arr[i];
                heap->min->right = arr[i];
            } else {
                arr[i]->left = heap->min;
                arr[i]->right = heap->min->right;
                heap->min->right->left = arr[i];
                heap->min->right = arr[i];
                if (a == 1 && (arr[i]->key->salary < heap->min->key->salary)) {
                    heap->min = arr[i];
                }
            }
        }
    }

    // здесь утечка
    // for (int i = 0; i < num; i++) {
    //     if (arr[i] != NULL) {
    //         free(arr[i]);
    //     }
    // }
    free(arr); 
    return its_ok;
    
}
int extract(fibonacci_heap* heap, Node** to_file, int a) {
    int flag = its_ok;
    Node* temp = heap->min;
    if (temp != NULL) {
        if (temp->child != NULL) {
            Node* current = temp->child;
            Node *helper = NULL;
            helper = current->right;
            current->parent = NULL;
            current->left = temp;
            current->right = temp->right;
            temp->right->left = current;
            temp->right = current;
            current = helper;
            while(current != temp->child) {
                helper = current->right;
                current->parent = NULL;
                current->left = temp;
                current->right = temp->right;
                temp->right->left = current;
                temp->right = current;
                current = helper;
            }
        }
        temp->left->right = temp->right;
        temp->right->left = temp->left;

        if (temp == temp->right) {
            heap->min = NULL;
        } else {
            heap->min = temp->right;
            flag = fib_consolid(heap, a);
            if (flag == no_memmory) {
                return no_memmory;
            }
        }
        heap->size--;
    }
    (*to_file) = temp;
    return its_ok;
}

int sort(employee* mankind, int number_of_man, FILE* f1, int a) {
    int flag = its_ok;
    fibonacci_heap heap;
    heap.min = NULL;
    heap.size = 0;
    for (int i = 0; i < number_of_man; i++) {
        flag = fib_insert(&heap, &(mankind[i]), a);
        if (flag == no_memmory) {
            return no_memmory;
        }
    }
    Node* to_file = NULL;
    for (int i = 0; i < number_of_man; i++) {
        flag = extract(&heap, &to_file, a);
        if (flag == no_memmory) {
            return no_memmory;
        }
        fprintf(f1, "%3d | %8s | %8s | %.2lf\n", to_file->key->id, to_file->key->name,
        to_file->key->surname, to_file->key->salary);
        free(to_file->key->name);
        free(to_file->key->surname);
        free(to_file);
        to_file = NULL;
    }
    return its_ok;
}   
//-------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    int ex = 0, number_of_man = 0;
    // if (argc != 3) {
    //     printf("Incorrect arguments\n");
    //     return -1;
    // }
    employee *mankind;
    FILE *f1;
    FILE *out;
    f1 = fopen(argv[1], "r");
    if (f1 == NULL) {
        printf("There is no such file\n");
        return -1;
    }

    ex = file_to_arr(&mankind, &number_of_man, f1);
    // print_arr(mankind, number_of_man);
    
    out = fopen("out.txt", "a");
    if (out == NULL) {
        printf("Smth goes wrong..\n");
        free_arr(mankind, number_of_man);
        fclose(f1);
        return -1;
    }
    
    ex = sort(mankind, number_of_man, out, 1);
    free(mankind);
    fclose(f1);
    fclose(out);
    // 
    

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
