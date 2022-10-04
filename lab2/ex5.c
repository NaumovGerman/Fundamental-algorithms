#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

int* create_array(int size, int low, int up) {
    int* arr = (int*)malloc(sizeof(int) * size);
    if (arr == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        arr[i] = low + rand()%(up + 1 - low);
    }
    return arr;
}

void changer(int *max, int *min) {
    int ptr = *max;
    *max = *min;
    *min = ptr;
}

void do_first(int* arr, int size) {
    int ind_min = 0, ind_max = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[ind_max]) {
            ind_max = i;
        } else if (arr[i] < arr[ind_min]) {
            ind_min = i;
        } else {
            continue;
        }
    }
    changer(&arr[ind_max], &arr[ind_min]);
}

void output_arr(int* arr) {
    int *ptr = arr;
    while (*ptr) {
        printf("%d ", *ptr);
        ptr++;
    }
    printf("\n");
}

int* do_second(int* arr, int size) {
    int actual_size = 1;
    int flag;
    int* n = (int*)malloc(sizeof(int) * size);
    if (n == NULL) {
        return NULL;
    }
    n[0] = arr[0];
    for (int i = 1; i < size; i++) {
        flag = 0;
        for (int j = 0; j < actual_size; j++) {
            if (arr[i] == n[j]) {
                flag++;
            }
        }
        if (!flag) {
            n[actual_size++] = arr[i];
        }
    }
//     printf("%d\n", actual_size);
    return n;
}

int main() {
    srand(time(NULL));
    int size = 1 + rand()%31;
    int lower_bound, upper_bound, action;
    printf("Enter lower and upper bound: ");
    scanf("%d %d", &lower_bound, &upper_bound);
    int* arr = create_array(size, lower_bound, upper_bound);
    if (arr == NULL) {
        printf("Memory was not allocated\n");
        return 0;
    }
    printf("Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Please select an action:\n");
    printf("If you want to swap the maximum and minimum values of the array - 1:\n");
    printf("If you want to сreate an array that contains only the unique values of the original array - 2:\n");
    scanf("%d", &action);
    if (action == 1) {
        do_first(arr, size);
        output_arr(arr);
    } else if (action == 2) {
        int* new_arr = do_second(arr, size);
        if (new_arr == NULL) {
            printf("Memory was not allocated\n");
        } else {
            output_arr(new_arr);
            free(new_arr);
        }

    } else {
        printf("Incorrect choice\n");
    }
    free(arr);
    return 0;
}
