#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double** create_matr(int row, int col) {
    double** matr = (double**)malloc(sizeof(double*) * row);
    for (int i = 0; i < row; i++) {
        matr[i] = (double*)malloc(sizeof(double) * col);
        for (int j = 0; j < col; j++) {
            matr[i][j] = -100 + rand()%(201);
        }
    }
    return matr;
}

double** multiplication(double** matr_fir, double** matr_sec, int row, int col, int num) {
    double** temp = (double**)malloc(sizeof(double*) * row);
    for (int i = 0; i < row; i++) {
        temp[i] = (double*)malloc(sizeof(double) * col);
        for (int j = 0; j < col; j++) {
            int res = 0;
            for (int k = 0; k < num; k++) {
                res += matr_fir[i][k] * matr_sec[k][j];
            }
            temp[i][j] = res;
        }
    }
    return temp;
}

double** det(double** matr, int num, int *pre_row, int *pre_col, double *res) {
    int a = 0;
    for (int i = *pre_row; i < num; i++) {
        if (fabs(matr[i][*pre_col] - 0.0) < 0.000000001) {
            continue;
        }
        double temp = matr[i][*pre_col];
        *res *= temp;
        for (int j = *pre_col; j < num; j++) {
            matr[i][j] /= temp;
        }
    }
    
    for (int k = *pre_row + 1; k < num; k++) {
        if (fabs(matr[k][*pre_col] - 0.0) < 0.000000001) {
            continue;
        }
        for (int q = *pre_col; q < num; q++) {
            matr[k][q] =  matr[k][q] - matr[*pre_row][q];
        }
    }
    return matr;
}

void print_matr(double** matr, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%10.3lf", matr[i][j]);
        }
        printf("\n");
    }   
    printf("\n");
}

void clean_matr(double** matr, int row) {
    for (int i = 0; i < row; i++) {
        free(matr[i]);
    }
    free(matr);
}

int main() {
    srand(time(NULL));
    int pre_row = 0;
    int pre_col = 0;
    double res = 1.0;
    int row_fir = 1 + rand()%10;
    int col_fir = 1 + rand()%10;
    // int row_fir = 4;
    // int col_fir = 4;
    int row_sec = 1 + rand()%10;
    int col_sec = 1 + rand()%10;
    double** matr_fir = create_matr(row_fir, col_fir);
    double** matr_sec = create_matr(row_sec, col_sec);

    printf("Part A:\n");
    printf("%d %d\n", row_fir, col_fir);
    print_matr(matr_fir, row_fir, col_fir);

    //
    printf("%d %d\n", row_sec, col_sec);
    print_matr(matr_sec, row_sec, col_sec);

    printf("Part B:\n");
    if (col_fir == row_sec) {
        double** temp = multiplication(matr_fir, matr_sec, row_fir, col_sec, col_fir);  // col_fir - кол-во произведений в сумме для подсчета ячейки
        print_matr(temp, row_fir, col_sec);
        clean_matr(temp, row_fir);
    } else {
        printf("The number of columns of the first matrix is not equal to the number of rows of the second matrix\n");
    }

    printf("Part C:\n");
    if (row_fir == col_fir) {
        for (int i = 0; i < row_fir - 1; i++) {
            matr_fir = det(matr_fir, row_fir, &pre_row, &pre_col, &res);
            pre_row++;
            pre_col++;
            print_matr(matr_fir, row_fir, col_fir);
        }
        res *= matr_fir[row_fir - 1][row_fir - 1];
        matr_fir[row_fir - 1][row_fir - 1] = 1.0;
        print_matr(matr_fir, row_fir, col_fir);
        printf("Determinant = %.2lf\n", res);   

    } else {
        printf("The determinant cannot be calculated\n");
    }

    clean_matr(matr_fir, row_fir);
    clean_matr(matr_sec, row_sec);
    return 0;
}
