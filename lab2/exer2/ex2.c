#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int find_len(char* word) {
    int count = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        count++;
    }
    return count;
}

char* do_r(char* word, int len) {
    char *rev_word = (char*)malloc(sizeof(char) * (len+1));
    if (rev_word == NULL) {
        return NULL;
    }
    char *ptr = rev_word;
    for (int i = len - 1; i >= 0; i--) {
        *ptr++ = word[i];
    }
    *ptr = 0;
    return rev_word;
}

char* do_u(char* word, int len) {
    char *rev_word = (char*)malloc(sizeof(char) * (len+1));
    if (rev_word == NULL) {
        return NULL;
    }
    char *ptr = rev_word;
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0) {
            *ptr++ = isalpha(word[i]) ? toupper(word[i]) : word[i];
        } else {
            *ptr++ = word[i];
        }
    }
    *ptr = 0;
    return rev_word;
}

char* do_n(char* word, int len) {
    char *rev_word = (char*)malloc(sizeof(char) * (len+1));
    if (rev_word == NULL) {
        return NULL;
    }
    char *ptr = rev_word;
    int indexex[len];
    for (int i = 0; i < len; i++) {
        if (isdigit(word[i])) {
            indexex[i] = 0;
            *ptr++ = word[i];
        } else if (isalpha(word[i])){
            indexex[i] = 2;
        } else {
            indexex[i] = 3;
        }
    }
    for (int i = 0; i < len; i++) {
        if (indexex[i] == 3) {
            *ptr++ = word[i];
        }
    }
    for (int i = 0; i < len; i++) {
        if (indexex[i] == 2) {
            *ptr++ = word[i];
        }
    }
    *ptr = 0;
    return rev_word;
}

char* do_c(char* word1, char* word2, int len1) {
    int len2 = find_len(word2);
    char *rev_word = (char*)malloc(sizeof(char) * (len1+len2+1));
    if (rev_word == NULL) {
        return NULL;
    }
    char *ptr = rev_word;
    for (int i = 0; i < len1; i++) {
        *ptr++ = word1[i];
    }
    for (int i = 0; i < len2; i++) {
        *ptr++ = word2[i];
    }
    *ptr = 0;
    return rev_word;
}

int main(int argc, char* argv[]) {
    if (argc != 3 && argc != 4) {
        printf("Incorrect input\n");
        return 0;
    }
    int len = find_len(argv[2]);
    if (strcmp(argv[1], "-l") == 0) {
        if (argc != 3) {
            printf("Incorrect input\n");
            return 0;
        }
        printf("%d\n", len);
    } else if (strcmp(argv[1], "-r") == 0) {
        if (argc != 3) {
            printf("Incorrect input\n");
            return 0;
        }
        char* word = do_r(argv[2], len);
        if (word == NULL) {
            printf("Memory was not allocated\n");
            return 0;
        }
        printf("%s\n", word);
        free(word);
    } else if (strcmp(argv[1], "-u") == 0) {
        if (argc != 3) {
            printf("Incorrect input\n");
            return 0;
        }
        char* word = do_u(argv[2], len);
        if (word == NULL) {
            printf("Memory was not allocated\n");
            return 0;
        }
        printf("%s\n", word);
        free(word);
    } else if (strcmp(argv[1], "-n") == 0) {
        if (argc != 3) {
            printf("Incorrect input\n");
            return 0;
        }
        char* word = do_n(argv[2], len);
        if (word == NULL) {
            printf("Memory was not allocated\n");
            return 0;
        }
        printf("%s\n", word);
        free(word);
    } else if (strcmp(argv[1], "-c") == 0) {
        if (argc != 4) {
            printf("Incorrect input\n");
            return 0;
        }
        char* word = do_c(argv[2], argv[3], len);
        if (word == NULL) {
            printf("Memory was not allocated\n");
            return 0;
        }
        printf("%s\n", word);
        free(word);
    } else {
        printf("Incorrect flag\n");
    }
    
    return 0;
}
