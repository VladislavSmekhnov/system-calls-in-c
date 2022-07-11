#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int input_read(FILE **file, char **file_path);
void output(FILE *file);
void input_file_path(char **file_path);
int read_mode(char **file_path);
int write_mode(char *file_path);

int main() {
    char *file_path = NULL, ch;
    int stop_var, contin = 1;

    if (scanf("%d%c", &stop_var, &ch) != 2 || ch != '\n' || (stop_var != -1 && stop_var != 1 &&
        stop_var != 2)) {
        printf("n/a");
    } else {
        while (stop_var == 1 || stop_var == 2) {
            switch (stop_var) {
                case 1:
                    if (read_mode(&file_path) != 0)
                        contin = 0;
                    break;
                case 2:
                    if (write_mode(file_path) != 0)
                        contin = 0;
                    break;
            }
            if (contin != 1 || scanf("%d%c", &stop_var, &ch) != 2 || ch != '\n' ||
                (stop_var != -1 && stop_var != 1 && stop_var != 2))
                printf("n/a");
        }
    }
    return 0;
}

int input_read(FILE **file, char **file_path) {
    char *tmp_file_path_main = NULL;
    int state = 0;
    FILE *tmp_file = NULL;

    input_file_path(&tmp_file_path_main);
    printf("Successfully specified file path\n");
    printf("Current file path: %s\n", tmp_file_path_main);
    if (chmod(tmp_file_path_main, S_IRWXU | S_IRWXO | S_IRWXG) != 0) {
        printf("Cannot change access mode for reading\n");
        state = 1;
    } else {
        //printf("Changed file access for reading\n");
        printf("No problems with opening file\n");
        if ((tmp_file = fopen(tmp_file_path_main, "r")) == NULL) {
            //printf("Any problems here!!\n");
            state = 1;
        } else {
            //printf("Opened file successfully!\n");
            *file = tmp_file;
            *file_path = tmp_file_path_main;
            // printf("\nSuccess to open file!\n");
        }
    }
    free(tmp_file_path_main);
    free(tmp_file);
    return state;
}

int input_write(FILE **file, char *file_path) {
    FILE *tmp_file;
    int state = 0;
    char ch = 0;

    if (chmod(file_path, S_IRWXU | S_IRWXO | S_IRWXG) != 0) {
        state = 1;
    } else {
        if ((tmp_file = fopen(file_path, "a+")) == NULL) {
            state = 1;
        } else {
            while (ch != '\n') {
                scanf("%c", &ch);
                if (ch != '\n')
                    fprintf(tmp_file, "%c", ch);
            }
            *file = tmp_file;
        }
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
    printf("Enter file path: ");
    while (ch != '\n' && ch != '\0') {
        ch = getchar();
        if (ch != '\n' && ch != '\0') {
            tmp_file_path = (char *)realloc(tmp_file_path, ++i * sizeof(char));
            tmp_file_path[i - 1] = ch;
        }
    }
    *file_path = tmp_file_path;
}

int read_mode(char **file_path) {
    printf("Read mode\n");
    int state = 0;
    FILE *file;
    if (input_read(&file, file_path) != 0)
        state = 1;
    else
        output(file);
    return state;
}

int write_mode(char *file_path) {
    int state = 0;
    if (file_path == NULL) {
        state = 1;
    } else {
        FILE *file;
        if (input_write(&file, file_path) != 0)
            state = 1;
        else
            output(file);
    }
    return state;
}

