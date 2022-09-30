#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* fill_array(int size) {
    int* arr = (int*)malloc(sizeof(int) * size);
    if (arr == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        arr[i] = -50 + rand()%101;
    }
    return arr;
}

int main() {
    srand(time(NULL));
    int a_size = 1 + rand()%31;
    int b_size = 1 + rand()%31;
    int* a_array = fill_array(a_size);
    if (a_array == NULL) {
        printf("Memory was not allocated\n");
        return 0;
    }
    int* b_array = fill_array(b_size);
    if (b_array == NULL) {
        printf("Memory was not allocated\n");
        return 0;
    }
    int* c_array = (int*)calloc(a_size, sizeof(int));
    if (c_array == NULL) {
        printf("Memory was not allocated\n");
        return 0;
    }
    if (a_size == b_size) {
        for (int i = 0; i < a_size; i++) {
            c_array[i] = a_array[i] + b_array[i];
        }
    } else if (a_size > b_size) {
        for (int i = 0; i < b_size; i++) {
            c_array[i] = a_array[i] + b_array[i];
        }
        for (int i = b_size; i < a_size; i++) {
            c_array[i] += a_array[i] + b_array[b_size - 1];
        }
    } else {
        for (int i = 0; i < a_size; i++) {
            c_array[i] = a_array[i] + b_array[i];
        }
    }
    printf("Array A: ");
    for (int i = 0; i < a_size; i++) {
        printf("%3d ", a_array[i]);
    }
    printf("\n");
    printf("Array B: ");
    for (int i = 0; i < b_size; i++) {
        printf("%3d ", b_array[i]);
    }
    printf("\n");
    printf("Array C: ");
    for (int i = 0; i < a_size; i++) {
        printf("%3d ", c_array[i]);
    }
    printf("\n");
    free(a_array);
    free(b_array);
    free(c_array);
    return 0;
}
