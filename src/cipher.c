#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int input_read(char **file_path);
void output(FILE *file);
void input_file_path(char **file_path);
int read_mode(char **file_path);
int write_mode(const char *file_path);
int input_write(const char *file_path);

int main() {
    char *file_path = NULL, ch;
    int stop_var, contin = 1;

    if (scanf("%d%c", &stop_var, &ch) != 2 || ch != '\n' || (stop_var != -1 && stop_var != 1 &&
        stop_var != 2)) {
        printf("n/a");
    } else {
        while ((stop_var == 1 || stop_var == 2) && contin == 1) {
            switch (stop_var) {
                case 1:
                    if (file_path != NULL)
                        free(file_path);
                    if (read_mode(&file_path) != 0)
                        contin = 0;
                    break;
                case 2:
                    if (write_mode(file_path) != 0)
                        contin = 0;
                    break;
            }
            if (contin == 0 || scanf("%d%c", &stop_var, &ch) != 2 || ch != '\n' || (stop_var != -1 && stop_var != 1 && stop_var != 2))
                printf("n/a");
        }
    }
    return 0;
}

int input_read(char **file_path) {
    char *tmp_file_path_main = NULL;
    int state = 0;
    FILE *tmp_file = NULL;

    input_file_path(&tmp_file_path_main);
    if (chmod(tmp_file_path_main, S_IRUSR | S_IROTH | S_IRGRP) != 0) {
        state = 1;
    } else if ((tmp_file = fopen(tmp_file_path_main, "r")) == NULL) {
        state = 2;
    } else {
        fclose(tmp_file);
        *file_path = tmp_file_path_main;
    }
    return state;
}

int input_write(const char *file_path) {
    FILE *tmp_file;
    int state = 0;
    char ch = 0;

    if (chmod(file_path, S_IRWXU | S_IRWXO | S_IRWXG) != 0) {
        state = 1;
    } else if ((tmp_file = fopen(file_path, "a+")) == NULL) {
        state = 2;
    } else {
        while (ch != '\n') {
            scanf("%c", &ch);
            if (ch != '\n')
                fprintf(tmp_file, "%c", ch);
        }
        fclose(tmp_file);
    }
    return state;
}

void output(FILE *file) {
    char ch;
    while (fscanf(file, "%c", &ch) != EOF) {
        printf("%c", ch);
    }
    printf("\n");
    fclose(file);
}

void input_file_path(char **file_path) {
    int i = 0;
    char ch = ' ';
    char *tmp_file_path = NULL;

    while (ch != '\n' && ch != '\0') {
        ch = getchar();
        if (ch != '\n' && ch != '\0') {
            tmp_file_path = (char *)realloc(tmp_file_path, ++i * sizeof(char));
            tmp_file_path[i - 1] = ch;
        }
    }
    *file_path = tmp_file_path;
    free(tmp_file_path);
}

int read_mode(char **file_path) {
    int state = 0;
    char *tmp_file_path = NULL;

    if (input_read(&tmp_file_path) != 0) {
        state = 1;
    } else {
        FILE *file;
        if ((file = fopen(tmp_file_path, "r")) == NULL)
            state = 2;
        else
            output(file);
        *file_path = tmp_file_path;
    }
    return state;
}

int write_mode(const char *file_path) {
    int state = 0;
    if (file_path == NULL) {
        state = 1;
    } else {
        if (input_write(file_path) != 0) {
            state = 1;
        } else {
            FILE *file;
            if ((file = fopen(file_path, "r")) == NULL)
                state = 2;
            else
                output(file);
        }
    }
    return state;
}
