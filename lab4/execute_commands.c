#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include </home/german/fundi/lab4/exer4/header.h>

int command_load(char* name_arr, char* file_name, Array** my_array) {
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
    if ((*my_array)[position].size == 0) { // shows len of arrays
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
        (*my_array)[position].my_array = temp;
        (*my_array)[position].size = temp_lenth;
        printf("%d\n", (*my_array)[position].size);

    } else if ((*my_array)[position].size != 0) {
        // printf("two\n");
        temp = (*my_array)[position].my_array;
        temp_lenth = (*my_array)[position].size;
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
        (*my_array)[position].size = temp_lenth+1;
        
        (*my_array)[position].my_array = temp;
    }
    fclose(f1);
    return its_ok;
}

int command_save(char* name_arr, char* file_name, Array** my_array) {
    char a = name_arr[0];
    // int my_number;
    int position = a - 65;

    if ((*my_array)[position].size == 0) {
        return impossible_action;
    }
    FILE *f1;
    f1 = fopen(file_name, "a");
    // if (!f1) ? а же создает файл в случае чего
    for (int i = 0; i < (*my_array)[position].size; i++) {
        fprintf(f1, "%d ", ((*my_array)[position].my_array)[i]);
    }
    fclose(f1);
    return its_ok;
}

int command_rand(char* name_arr, char* amount, char* left_bound, char* right_bound, Array** my_array) {
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

    if ((*my_array)[position].size != 0) {
        return impossible_action;
    }
    temp = (int*)malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) {
        temp[i] = (rand()%(rb - lb + 1)) + lb;
    }
    (*my_array)[position].my_array = temp;
    (*my_array)[position].size = count;
}

int command_remove(char* name_arr, char* f_pos, char* s_pos, Array** my_array) {
    int from = atoi(f_pos), num = atoi(s_pos);
    char a = name_arr[0];
    // int my_number;
    int position = a - 65;
    if ((*my_array)[position].size < from + num || from < 0 || num < 0) {
        return impossible_action;
    }
    int temp_length = (*my_array)[position].size - num;
    int* temp = (int*)malloc(sizeof(int) * temp_length);
    int* ptr = temp;
    for (int i = 0; i < (*my_array)[position].size; i++) {
        if (i >= from && i <= from + num - 1){
            continue;
        }
        *ptr = ((*my_array)[position].my_array)[i];
        ptr++;
    }
    (*my_array)[position].size = temp_length;
    free((*my_array)[position].my_array);
    (*my_array)[position].my_array = temp;
    return its_ok;
}

int command_free(char* name_arr, Array** my_array) {
    char a = name_arr[0];
    // int my_number;
    int position = a - 65;

    if ((*my_array)[position].size == 0) {
        return its_ok;
    }
    free((*my_array)[position].my_array); 
    (*my_array)[position].my_array = NULL; // сопоставить с 0 ???????????
    (*my_array)[position].size = 0;
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


int command_sort(char* name_arr, int mark, Array** my_array) {
    char a = name_arr[0];
    // int my_number;
    int position = a - 65;
    if ((*my_array)[position].size == 0) {
        return impossible_action;
    }
    if (mark == 1) {
        qsort((*my_array)[position].my_array, (*my_array)[position].size, sizeof(int), compare_ints_plus);
    } else {
        qsort((*my_array)[position].my_array, (*my_array)[position].size, sizeof(int), compare_ints_minus);
    }
    return its_ok;
}


int command_print_all(char* name_arr, Array** my_array) {
    char a = name_arr[0];
    // int my_number;
    int position = a - 65;
    if ((*my_array)[position].size == 0) {
        return impossible_action;
    }
    for (int i = 0; i < (*my_array)[position].size; i++) {
        printf("%d ", ((*my_array)[position].my_array)[i]);
    }
    return its_ok;
}

int command_print_range(char* name_arr, char* lb, char* rb, Array** my_array) {
    char a = name_arr[0];
    // int my_number;
    int position = a - 65;
    if ((*my_array)[position].size == 0) {
        return impossible_action;
    }
    int left = atoi(lb), right = atoi(rb);
    if (left < 1 || left > right || (*my_array)[position].size < right) {
        return impossible_action;
    }
    for (int i = left - 1; i < right; i++) {
        printf("%d ", ((*my_array)[position].my_array)[i]);
    }
    return its_ok;
}

int comand_concat(char* first, char* second, Array** my_array) {
    char a = first[0];
    // int my_number;
    int position_first = a - 65;
    if ((*my_array)[position_first].size == 0) {
        return impossible_action;
    }
    
    char b = second[0];
    // int my_number;
    int position_second = b - 65;
    if ((*my_array)[position_second].size == 0) {
        return impossible_action;
    }
    int new_length = (*my_array)[position_first].size + (*my_array)[position_second].size;
    int q = (*my_array)[position_first].size;
    int* temp = (int*)realloc((*my_array)[position_first].my_array, sizeof(int) * (new_length+1)); // почему + 1
    if (!temp) {
        free((*my_array)[position_first].my_array);
        return not_allocated;
    } else {
        (*my_array)[position_first].my_array = temp;
    }
    int *ptr = (*my_array)[position_first].my_array;
    for (int i = 0; i < position_second; i++) {
        ((*my_array)[position_first].my_array)[q] = ((*my_array)[position_second].my_array)[i];
        q++;
    }
    return its_ok;
    
}

int command_shuffle(char* name_arr, Array** my_array) {
    int temp, index;
    char a = name_arr[0];
    int position = a - 65;
    if ((*my_array)[position].size == 0) {
        return impossible_action;
    }
    for (int i = 0; i < (*my_array)[position].size; i++)  {
        index = rand() % (*my_array)[position].size;
        temp = ((*my_array)[position].my_array)[i];
        ((*my_array)[position].my_array)[i] = ((*my_array)[position].my_array)[index];
        ((*my_array)[position].my_array)[index] = temp;
    }

    return its_ok;
}

int command_copy(char* name_arr, char* lb, char* rb, char* destination, Array** my_array) {
    char a = name_arr[0];
    int position_first = a - 65;
    if ((*my_array)[position_first].size == 0) {
        return impossible_action;
    }
    int left = atoi(lb), right = atoi(rb);
    if (((*my_array)[position_first].size < right) || (left > right) || (left < 1)) {
        return impossible_action;
    }
    
    a = destination[0];
    int position_second = a - 65;
    if ((*my_array)[position_second].size != 0) {
        free((*my_array)[position_second].my_array);
        (*my_array)[position_second].my_array = NULL;
        (*my_array)[position_second].size = 0;
    }
    (*my_array)[position_second].my_array = (int*)malloc(sizeof(int) * (right - left + 1));
    if (!(*my_array)[position_second].my_array) {
        return no_memmory;
    }
    int q = 0;
    for (int i = left - 1; i < right; i++) {
        ((*my_array)[position_second].my_array)[q] = ((*my_array)[position_first].my_array)[i];
        q++;
    }
    return its_ok;
}

int command_stats(char* name_arr, Array** my_array) {
    int max, max_index, min, min_index;
    char a = name_arr[0];
    int position = a - 65;
    if ((*my_array)[position].size == 0) {
        return impossible_action;
    }
    printf("Statistics for array '%s':\n", name_arr);
    printf("Size: %d\n", (*my_array)[position].size);

    max = ((*my_array)[position].my_array)[0];
    min = ((*my_array)[position].my_array)[0];
    max_index = 0;
    min_index = 0;

    for (int i = 1; i < (*my_array)[position].size; i++) {
        int value = ((*my_array)[position].my_array)[i];
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
    qsort((*my_array)[position].my_array, (*my_array)[position].size, sizeof(int), compare_ints_plus);
    int max_count = 1;
    int max_element = ((*my_array)[position].my_array)[0];
    int current_count = 1;

    for (int i = 1; i < (*my_array)[position].size; i++) {
        if (((*my_array)[position].my_array)[i] == ((*my_array)[position].my_array)[i - 1]) {
            current_count++;
        } else {
            if (current_count > max_count) {
                max_count = current_count;
                max_element = ((*my_array)[position].my_array)[i - 1];
            }
            current_count = 1;
        }
    }

    if (current_count > max_count) {
        max_count = current_count;
        max_element = ((*my_array)[position].my_array)[(*my_array)[position].size - 1];
    }
    printf("The most frequently occurring element is %d, which appears %d times.\n", max_element, max_count);

    // Calculate the average value
    int sum = 0;
    for (int i = 0; i < (*my_array)[position].size; i++) {
        sum += ((*my_array)[position].my_array)[i];
    }
    double average = (double)sum / (*my_array)[position].size;
    printf("Average value: %f\n", average);

    // Find the maximum deviation from the average
    double max_deviation = 0;
    for (int i = 0; i < (*my_array)[position].size; i++) {
        double deviation = fabs(((*my_array)[position].my_array)[i] - average);
        if (deviation > max_deviation) {
            max_deviation = deviation;
        }
    }
    printf("Maximum deviation from the average: %f\n", max_deviation);
}