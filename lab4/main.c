#include <stdio.h>
#include <stdlib.h>
#include </home/german/fundi/lab4/exer4/header.h>

int main(int argc, char* argv[]) {
    int reply = 0;
    FILE *f1;
    if (argc != 2) {
        printf("Incorrect input\n");
        return -1;
    }
    f1 = fopen(argv[1], "r");
    if (!f1) {
        printf("File does not exist\n");
        return -1;
    }
    reply = analize_command_file(f1);
    return 0; 
}