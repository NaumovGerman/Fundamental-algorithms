#include <stdio.h>
#include <stdlib.h>

int count_un(int num) {
    int count = 0;
    while (num != 0) {
        if (num&1 == 1) {
            count++;
        }
        num >>= 1;
    }
    return count;
}

int count_cons_un(int num, int l) {
    int count = 0, a = 0, b = 0;
    while (num != 0) {
        if (num&1 == 1) {
            count++;
        } else {
            if (count == l) {
                return 1;
            } else {
                count = 0;
            }
        }
        num >>= 1;
    }
    if (count == l) {
        return 1;
    }
    return 0;
}

void find_all_suitable_1(int** arr, int *size, int k, int l, int *status) {
    int a, b, amount = 0, ll = 2, mm = 0, t = 0;
    int* ls = NULL;
    int* tmp = NULL;
    if (k < 1 || l < 0 || k < l) {
        // arr = NULL;
        *status = -1;
    } else {
        a = 1<<(k - 1);
        b = 1<<k;
        if (l != 0) {
            ls = (int*)malloc(sizeof(int) * ll);
            if (ls == NULL) {
                *status = -3;
            }
            for (int i = a; i < b; i++) {
                if (count_un(i) == l) {
                    if (ll == mm) {
                        tmp = (int*)realloc(ls, sizeof(int) * ll*2);
                        if (!tmp) {
                            free(ls);
                            *status = -4;
                        } else {
                            ls = tmp;
                            ll *= 2;
                        }
                    }
                    ls[mm] = i;
                    mm++;
                    // printf("--------%d\n", ll);

                }
            }
            *size = mm;
            *arr = ls;
        } else {
            *status = -2;
        }
    }
}

void find_all_suitable_2(int** arr, int *size, int k, int l, int *status) {
    int a, b, amount = 0, ll = 2, mm = 0, t = 0;
    int* ls = NULL;
    int* tmp = NULL;
    if (k < 1 || l < 0 || k < l) {
        // arr = NULL;
        *status = -1;
    } else {
        a = 1<<(k - 1);
        b = 1<<k;
        if (l != 0) {
            ls = (int*)malloc(sizeof(int) * ll);
            if (ls == NULL) {
                *status = -3;
            }
            for (int i = a; i < b; i++) {
                if (count_cons_un(i, l)) {
                    if (ll == mm) {
                        tmp = (int*)realloc(ls, sizeof(int) * ll*2);
                        if (!tmp) {
                            free(ls);
                            *status = -4;
                        } else {
                            ls = tmp;
                            ll *= 2;
                        }
                    }
                    ls[mm] = i;
                    mm++;
                    // printf("--------%d\n", ll);

                }
            }
            *size = mm;
            *arr = ls;
        } else {
            *status = -2;
        }
    }
}

int main() {
    int k, l, size = 0, status = 0, choice = 0;
    int* arr = NULL;
    printf("Make a choice:\n");
    printf("1 - Use the search function for all k-bit integers of type int, in the binary notation of which there is exactly l, l≤k units;\n");
    printf("2 - Use the search function for all k-bit integers of type int, in the binary notation of which there are exactly l, l≤k consecutive units;\n");
    scanf("%d", &choice);
    printf("Please enter the size of the number in bits - k:\n");
    scanf("%d", &k);
    printf("Please enter the number of units in the binary representation of the number- l:\n");
    scanf("%d", &l);
    printf("\n");
    if (choice == 1) {
        find_all_suitable_1(&arr, &size, k, l, &status);
    } else if (choice == 2) {
        find_all_suitable_2(&arr, &size, k, l, &status);
    }
    else {
        printf("Incorrect choice\n");
        return 1;
    }

    if (status == -1) {
        printf("Incorrect input\n");
        return 1;
    } else if (status == -2) {
        arr = (int*)malloc(sizeof(int));
        arr[0] = 0;
        printf("%d\n", arr[0]);
    } else if (status == -3) {
        printf("Memory was not allocated\n");
        return 1;
    } else if (status == -4) {
        printf("Memory was not reallocated\n");
        return 1;
    } else {
        for (int i = 0; i < size; i++) {
            printf("%d\n", arr[i]);
        }
    }
    free(arr);

    return 0;
}
