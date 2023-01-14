#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include </home/german/fundi/lab4/exer4/header.h>

int command_load(char* name_arr, char* file_name, int** is_exist, int*** pointers_to_arrays) {
    FILE* f1;
    char a = name_arr[0];
    int my_number;
    int position = a - 65;
    int *temp = NULL;
    int *super_temp;
    int* ptr = temp;
    int temp_lenth = 0, temp_allocated = 0;
    f1 = fopen(file_name, "r");
    if (!f1) {
        return no_file;
    }
    
    if ((*is_exist)[position] == 0) { // shows len of arrays
        // printf("one\n");
        while (fscanf(f1, "%d", &my_number) == 1) {
            if (temp_allocated == 0) {
                temp = (int*)malloc(sizeof(int) * 2);
                if (temp == NULL) {
                    fclose(f1);
                    return no_memmory;
                }
                temp_allocated = 2;
                temp_lenth = 1;
            } else {
                if (temp_allocated = temp_lenth) {
                    temp_allocated *= 2;
                    super_temp = (int*)realloc(temp, sizeof(int) * temp_allocated);
                    if (!super_temp) {
                        free(temp);
                        fclose(f1);
                        return not_allocated;
                    } else {
                        temp = super_temp;
                    }
                }

            }
            *ptr = my_number;
            temp_lenth++;
            ptr++;
            
        }
        super_temp = (int*)realloc(temp, sizeof(int) * temp_lenth);
        if (!super_temp) {
            free(temp);
            fclose(f1);
            return not_allocated;
        } else {
            temp = super_temp;
        }
        (*is_exist)[position] = temp_lenth;
        (*pointers_to_arrays)[position] = temp;

    } else if ((*is_exist)[position] != 0) {
        // printf("two\n");
        temp = (*pointers_to_arrays)[position];
        temp_lenth = (*is_exist)[position];
        ptr = temp + (temp_lenth - 1);
        temp_allocated = temp_lenth;

        while (fscanf(f1, "%d", &my_number) == 1) {
            if (temp_allocated = temp_lenth) {
                    temp_allocated *= 2;
                    super_temp = (int*)realloc(temp, sizeof(int) * temp_allocated);
                    if (!super_temp) {
                        free(temp);
                        fclose(f1);
                        return not_allocated;
                    } else {
                        temp = super_temp;
                    }
            }
            temp[temp_lenth] = my_number;
            temp_lenth++;
        }

        super_temp = (int*)realloc(temp, sizeof(int) * (temp_lenth+1)); // или не + 1
        if (!super_temp) {
            free(temp);
            fclose(f1);
            return not_allocated;
        } else {
            temp = super_temp;
        }
        (*is_exist)[position] = temp_lenth+1;
        (*pointers_to_arrays)[position] = temp;
    }
    fclose(f1);
    return its_ok;
}

int command_save(char* name_arr, char* file_name, int** is_exist, int*** pointers_to_arrays) {
    char a = name_arr[0];
    // int my_number;
    int position = a - 65;

    if ((*is_exist)[position] == 0) {
        return impossible_action;
    }
    FILE *f1;
    f1 = fopen(file_name, "a");
    // if (!f1) ? а же создает файл в случае чего
    for (int i = 0; i < (*is_exist)[position]; i++) {
        fprintf(f1, "%d ", (*pointers_to_arrays)[position][i]);
    }
    fclose(f1);
    return its_ok;
}

int command_rand(char* name_arr, char* amount, char* left_bound, char* right_bound, int** is_exist, int*** pointers_to_arrays) {
    int count = atoi(amount), lb, rb;
    int* temp = NULL;
    if (count < 1) {
        return impossible_action;
    }
    lb = atoi(left_bound);
    rb = atoi(right_bound);

    if (lb < 0 || lb > rb) {
        return impossible_action;
    }
    char a = name_arr[0];
    int my_number;
    int position = a - 65;

    if ((*is_exist)[position] != 0) {
        return impossible_action;
    }
    temp = (int*)malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) {
        temp[i] = (rand()%(rb - lb + 1)) + lb;
    }
    (*pointers_to_arrays)[position] = temp;
    (*is_exist)[position] = count;
}

int command_remove(char* name_arr, char* f_pos, char* s_pos, int** is_exist, int*** pointers_to_arrays) {
    int from = atoi(f_pos), num = atoi(s_pos);
    char a = name_arr[0];
    // int my_number;
    int position = a - 65;
    if ((*is_exist)[position] < from + num || from < 0 || num < 0) {
        return impossible_action;
    }
    int temp_length = (*is_exist)[position] - num;
    int* temp = (int*)malloc(sizeof(int) * temp_length);
    int* ptr = temp;
    for (int i = 0; i < (*is_exist)[position]; i++) {
        if (i >= from && i <= from + num - 1){
            continue;
        }
        *ptr = (*pointers_to_arrays)[position][i];
        ptr++;
    }
    (*is_exist)[position] = temp_length;
    free((*pointers_to_arrays)[position]);
    (*pointers_to_arrays)[position] = temp;
    return its_ok;
}

int command_free(char* name_arr, int** is_exist, int*** pointers_to_arrays) {
    char a = name_arr[0];
    // int my_number;
    int position = a - 65;

    if ((*is_exist)[position] == 0) {
        return its_ok;
    }
    free((*pointers_to_arrays)[position]); 
    (*pointers_to_arrays)[position] = NULL; // сопоставить с 0 ???????????
    (*is_exist)[position] = 0;
    return its_ok;
}

int compare_ints_plus(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 >= arg2) return 1; // =?
    return 0;
}

int compare_ints_minus(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 > arg2) return -1;
    if (arg1 <= arg2) return 1; // =?
    return 0;
}


int command_sort(char* name_arr, int mark, int** is_exist, int*** pointers_to_arrays) {
    char a = name_arr[0];
    // int my_number;
    int position = a - 65;
    if ((*is_exist)[position] == 0) {
        return impossible_action;
    }
    if (mark == 1) {
        qsort((*pointers_to_arrays)[position], (*is_exist)[position], sizeof(int), compare_ints_plus);
    } else {
        qsort((*pointers_to_arrays)[position], (*is_exist)[position], sizeof(int), compare_ints_minus);
    }
    return its_ok;
}


int command_print_all(char* name_arr, int** is_exist, int*** pointers_to_arrays) {
    char a = name_arr[0];
    // int my_number;
    int position = a - 65;
    if ((*is_exist)[position] == 0) {
        return impossible_action;
    }
    for (int i = 0; i < (*is_exist)[position]; i++) {
        printf("%d ", (*pointers_to_arrays)[position][i]);
    }
    return its_ok;
}

int command_print_range(char* name_arr, char* lb, char* rb, int** is_exist, int*** pointers_to_arrays) {
    char a = name_arr[0];
    // int my_number;
    int position = a - 65;
    if ((*is_exist)[position] == 0) {
        return impossible_action;
    }
    int left = atoi(lb), right = atoi(rb);
    if (left < 1 || left > right || (*is_exist)[position] < right) {
        return impossible_action;
    }
    for (int i = left - 1; i < right; i++) {
        printf("%d ", (*pointers_to_arrays)[position][i]);
    }
    return its_ok;
}

int comand_concat(char* first, char* second, int** is_exist, int*** pointers_to_arrays) {
    char a = first[0];
    // int my_number;
    int position_first = a - 65;
    if ((*is_exist)[position_first] == 0) {
        return impossible_action;
    }
    
    char b = second[0];
    // int my_number;
    int position_second = b - 65;
    if ((*is_exist)[position_second] == 0) {
        return impossible_action;
    }
    int new_length = (*is_exist)[position_first] + (*is_exist)[position_second];
    int q = (*is_exist)[position_first];
    int* temp = (int*)realloc((*pointers_to_arrays)[position_first], sizeof(int) * (new_length+1)); // почему + 1
    if (!temp) {
        free((*pointers_to_arrays)[position_first]);
        return not_allocated;
    } else {
        (*pointers_to_arrays)[position_first] = temp;
    }
    int *ptr = (*pointers_to_arrays)[position_first];
    for (int i = 0; i < position_second; i++) {
        (*pointers_to_arrays)[position_first][q] = (*pointers_to_arrays)[position_first][i];
        q++;
    }
    return its_ok;
    
}

int command_shuffle(char* name_arr, int** is_exist, int*** pointers_to_arrays) {
    int temp, index;
    char a = name_arr[0];
    int position = a - 65;
    if ((*is_exist)[position] == 0) {
        return impossible_action;
    }
    for (int i = 0; i < (*is_exist)[position]; i++)  {
        index = rand() % (*is_exist)[position];
        temp = (*pointers_to_arrays)[position][i];
        (*pointers_to_arrays)[position][i] = (*pointers_to_arrays)[position][index];
        (*pointers_to_arrays)[position][index] = temp;
    }

    return its_ok;
}

int command_copy(char* name_arr, char* lb, char* rb, char* destination, int** is_exist, int*** pointers_to_arrays) {
    char a = name_arr[0];
    int position_first = a - 65;
    if ((*is_exist)[position_first] == 0) {
        return impossible_action;
    }
    int left = atoi(lb), right = atoi(rb);
    if (((*is_exist)[position_first] < right) || (left > right) || (left < 1)) {
        return impossible_action;
    }
    
    a = destination[0];
    int position_second = a - 65;
    if ((*is_exist)[position_second] != 0) {
        free((*pointers_to_arrays)[position_second]);
        (*pointers_to_arrays)[position_second] = NULL;
        (*is_exist)[position_second] = 0;
    }
    (*pointers_to_arrays)[position_second] = (int*)malloc(sizeof(int) * (right - left + 1));
    if (!(*pointers_to_arrays)[position_second]) {
        return no_memmory;
    }
    int q = 0;
    for (int i = left - 1; i < right; i++) {
        (*pointers_to_arrays)[position_second][q] = (*pointers_to_arrays)[position_first][i];
        q++;
    }
    return its_ok;
}

int command_stats(char* name_arr, int** is_exist, int*** pointers_to_arrays) {
    int max, max_index, min, min_index;
    char a = name_arr[0];
    int position = a - 65;
    if ((*is_exist)[position] == 0) {
        return impossible_action;
    }
    printf("Statistics for array '%s':\n", name_arr);
    printf("Size: %d\n", (*is_exist)[position]);

    max = (*pointers_to_arrays)[position][0];
    min = (*pointers_to_arrays)[position][0];
    max_index = 0;
    min_index = 0;

    for (int i = 1; i < (*is_exist)[position]; i++) {
        int value = (*pointers_to_arrays)[position][i];
        if (value > max) {
            max = value;
            max_index = i;
        }
        if (value < min) {
            min = value;
            min_index = i;
        }
    }
    printf("Maximum element: %d (at index %d)\n", max, max_index);
    printf("Minimum element: %d (at index %d)\n", min, min_index);

    // Find the most common element
    qsort((*pointers_to_arrays)[position], (*is_exist)[position], sizeof(int), compare_ints_plus);
    int max_count = 1;
    int max_element = (*pointers_to_arrays)[position][0];
    int current_count = 1;

    for (int i = 1; i < (*is_exist)[position]; i++) {
        if ((*pointers_to_arrays)[position][i] == (*pointers_to_arrays)[position][i - 1]) {
            current_count++;
        } else {
            if (current_count > max_count) {
                max_count = current_count;
                max_element = (*pointers_to_arrays)[position][i - 1];
            }
            current_count = 1;
        }
    }

    if (current_count > max_count) {
        max_count = current_count;
        max_element = (*pointers_to_arrays)[position][(*is_exist)[position] - 1];
    }
    printf("The most frequently occurring element is %d, which appears %d times.\n", max_element, max_count);

    // Calculate the average value
    int sum = 0;
    for (int i = 0; i < (*is_exist)[position]; i++) {
        sum += (*pointers_to_arrays)[position][i];
    }
    double average = (double)sum / (*is_exist)[position];
    printf("Average value: %f\n", average);

    // Find the maximum deviation from the average
    double max_deviation = 0;
    for (int i = 0; i < (*is_exist)[position]; i++) {
        double deviation = fabs((*pointers_to_arrays)[position][i] - average);
        if (deviation > max_deviation) {
            max_deviation = deviation;
        }
    }
    printf("Maximum deviation from the average: %f\n", max_deviation);
}
