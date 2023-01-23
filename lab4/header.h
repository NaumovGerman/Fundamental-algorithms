#ifndef HEADER_H
#define HEADER_H

enum error {
    its_ok = 1,
    not_allocated = -1,
    impossible_action = -2,
    no_memmory = -3,
    end_of_file = -4,
    incor_brackets = -5,
    no_file = -6
};

typedef struct Array{
    int size;
    int* my_array;
} Array;

int analize_command_file(FILE *f1);
int command_load(char* name_arr, char* file_name, Array** my_array);
int command_save(char* name_arr, char* file_name, Array** my_array);
int command_rand(char* name_arr, char* amount, char* left_bound, char* right_bound, Array** my_array);
int comand_concat(char* first, char* second, Array** my_array);
int command_free(char* name_arr, Array** my_array);
int command_remove(char* name_arr, char* f_pos, char* s_pos, Array** my_array);
int command_copy(char* name_arr, char* lb, char* rb, char* destination, Array** my_array);
int command_sort(char* name_arr, int mark, Array** my_array); // * 2
int command_shuffle(char* name_arr, Array** my_array);
int command_print_range(char* name_arr, char* lb, char* rb, Array** my_array);
int command_print_all(char* name_arr, Array** my_array);
int command_stats(char* name_arr, Array** my_array);
#endif