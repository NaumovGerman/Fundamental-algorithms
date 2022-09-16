#include "stdio.h"
#include <stdlib.h>
#include <time.h>


int main() {
    int n = 30;
    int arr[n];
    int temp = 0;
    int min, max;
    int ind_min = 0, ind_max = 0;
    
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        temp = 1 + rand()%(10); // 1 + rand()%(10 - 1 + 1)
        arr[i] = (rand() % 100) * (temp % 3 == 1 ? -temp : temp); // 40% на выпадение отриц числа
        if (i == 0) {
            min = arr[i];
            ind_min = 0;
            max = arr[i];
            ind_max = 0;
        } else {
            if (arr[i] > max) {
                max = arr[i];
                ind_max = i;
            }
            if (arr[i] < min) {
                min = arr[i];
                ind_min = i;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    printf("Max = %d\n", max);
    printf("Min = %d\n", min);

    temp = arr[ind_max];
    arr[ind_max] = arr[ind_min];
    arr[ind_min] = temp;

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
