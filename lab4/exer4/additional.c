#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include </home/german/fundi/lab4/exer4/header.h>

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

int identify_command_and_atributes(char* string, int** is_exist, int*** pointers_to_arrays) {
    // printf("%d %d\n", (*is_exist)[1], (*is_exist)[15]);
    int reply = 0, mark, w;
    char* command, *first_atrib, *sec_atrib, *thir_atrib, *fourth_atrib;
    char separator[] = ", ";
    int len_com, len_fir, len_sec, len_thir, len_fourth;
    char* ptr;
    char f = string[0], s = string[1], t = string[2];
    // printf("%c %c %c\n", f, s, t);
    switch (f)
    {
        case 'L':
        // printf("Case Load\n");
            ptr = string + 5;
            first_atrib = (char*)malloc(sizeof(char) * 2);
            first_atrib[0] = toupper(*ptr);
            first_atrib[1] = '\0';
            ptr += 2;
            while (*ptr != ';') {
                reply = join_char(&sec_atrib, *ptr, &len_sec);
                if (reply == no_memmory) {
                    return no_memmory;
                } else if (reply == not_allocated) {
                    return not_allocated;
                }
                ptr++;
            }
            printf("%d %d\n", (*is_exist)[1], (*is_exist)[15]);
            reply = command_load(first_atrib, sec_atrib, &(*is_exist), &(*pointers_to_arrays));
            // printf("shokk load\n");
            break;

        case 'S':
            switch (s)
            {
                case 'a':
                    // printf("Case Save\n");
                    ptr = string + 5;
                    first_atrib = (char*)malloc(sizeof(char) * 2);
                    first_atrib[0] = toupper(*ptr);
                    first_atrib[1] = '\0';
                    ptr += 2;
                    while (*ptr != ';') {
                        reply = join_char(&sec_atrib, *ptr, &len_sec);
                        if (reply == no_memmory) {
                            return no_memmory;
                        } else if (reply == not_allocated) {
                            return not_allocated;
                        }
                        ptr++;
                    }
                    reply = command_save(first_atrib, sec_atrib, &(*is_exist), &(*pointers_to_arrays));
                    break;

                case 'o':
                    // printf("Case Sort\n");
                    first_atrib = (char*)malloc(sizeof(char) * 2);
                    first_atrib[0] = toupper(string[5]);
                    first_atrib[1] = '\0';
                    mark = 1 ? string[6] == '+' : 0;
                    reply = command_sort(first_atrib, mark, &(*is_exist), &(*pointers_to_arrays));
                    break;

                case 'h':
                    // printf("Case Shuffle\n");
                    first_atrib = (char*)malloc(sizeof(char) * 2);
                    first_atrib[0] = toupper(string[8]);
                    first_atrib[1] = '\0';

                    reply = command_shuffle(first_atrib, &(*is_exist), &(*pointers_to_arrays));
                    // printf("shokk shuffle\n");
                    break;

                default:
                    // printf("Case Stats\n");
                    first_atrib = (char*)malloc(sizeof(char) * 2);
                    first_atrib[0] = toupper(string[8]);
                    first_atrib[1] = '\0';

                    reply = command_stats(first_atrib, &(*is_exist), &(*pointers_to_arrays));
                    break;
            }

            break;

        case 'R':
            if (s == 'a') {
                // printf("Case Rand\n");
                char* garbage = strtok(string, separator);
                sec_atrib = strtok(NULL, separator);
                thir_atrib = strtok(NULL, separator);
                fourth_atrib = strtok(NULL, separator);

                first_atrib = (char*)malloc(sizeof(char) * 2);
                first_atrib[0] = toupper(string[5]);
                first_atrib[1] = '\0';
                
                reply = command_rand(first_atrib, sec_atrib, thir_atrib, fourth_atrib, &(*is_exist), &(*pointers_to_arrays));
                
            } else {
                // printf("Case Remove\n");
                char* garbage = strtok(string, separator);
                sec_atrib = strtok(NULL, separator);
                thir_atrib = strtok(NULL, separator);

                first_atrib = (char*)malloc(sizeof(char) * 2);
                first_atrib[0] = toupper(string[7]);
                first_atrib[1] = '\0';
                reply = command_remove(first_atrib, sec_atrib, thir_atrib, &(*is_exist), &(*pointers_to_arrays));
                // printf("shokk remove\n");
            }
            break;

        case 'C':
            if (t == 'n') {
                // printf("Case Concat\n");
                first_atrib = (char*)malloc(sizeof(char) * 2);
                first_atrib[0] = toupper(string[7]);
                first_atrib[1] = '\0';

                sec_atrib = (char*)malloc(sizeof(char) * 2);
                sec_atrib[0] = toupper(string[10]);
                sec_atrib[1] = '\0';
                reply = comand_concat(first_atrib, sec_atrib, &(*is_exist), &(*pointers_to_arrays));
            } else {
                // printf("Case Copy\n");
                char* garbage = strtok(string, separator);
                sec_atrib = strtok(NULL, separator);
                thir_atrib = strtok(NULL, separator);
                char* garbage2 = strtok(NULL, separator);

                first_atrib = (char*)malloc(sizeof(char) * 2);
                first_atrib[0] = toupper(string[5]);
                first_atrib[1] = '\0';

                fourth_atrib = (char*)malloc(sizeof(char) * 2);
                fourth_atrib[0] = toupper(garbage2[0]);
                fourth_atrib[1] = '\0';
                reply = command_copy(first_atrib, sec_atrib, thir_atrib, fourth_atrib, &(*is_exist), &(*pointers_to_arrays));
                // printf("shokk copy\n\n");
            }
            break;

        case 'F':
            // printf("Case Free\n");
            first_atrib = (char*)malloc(sizeof(char) * 2);
            first_atrib[0] = toupper(string[5]);
            first_atrib[1] = '\0';
            reply = command_free(first_atrib, &(*is_exist), &(*pointers_to_arrays));
            break;
            
        default:
            w = strlen(string);
            if (w == 13) {
                // printf("Case Printall\n");
                first_atrib = (char*)malloc(sizeof(char) * 2);
                first_atrib[0] = toupper(string[6]);
                first_atrib[1] = '\0';
                reply = command_print_all(first_atrib, &(*is_exist), &(*pointers_to_arrays));
                // printf("shokk print\n\n");
            } else {
                // printf("Case Printrange\n");
                char* garbage = strtok(string, separator);
                sec_atrib = strtok(NULL, separator);
                thir_atrib = strtok(NULL, separator);

                first_atrib = (char*)malloc(sizeof(char) * 2);
                first_atrib[0] = toupper(string[6]);
                first_atrib[1] = '\0';
                reply = command_print_range(first_atrib, sec_atrib, thir_atrib, &(*is_exist), &(*pointers_to_arrays));
            }
            break;
    }
}


int analize_command_file(FILE *f1) {
    int x = 0, len = 0, reply = 0;
    char* my_string;
    int* is_exist = calloc(26, sizeof(int));
    int** pointers_to_arrays = (int**)malloc(sizeof(int*) * 26);
    if (is_exist == NULL) {
        return no_memmory;
    }
    while (x != end_of_file) {
        x = takestr(f1, &my_string, &len);
        printf("%s\n", my_string);
        if (x != end_of_file) {
            reply = identify_command_and_atributes(my_string, &is_exist, &pointers_to_arrays);
            
            if (reply == impossible_action) {
                free(my_string);
                my_string = NULL;
                //memory
                continue;
            }
            free(my_string);
            my_string = NULL;
            len = 0;
        }
    }
    fclose(f1);
}
