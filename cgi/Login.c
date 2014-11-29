#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readLine(FILE* file) {
    int current = ftell(file);
    int n = 0;
    int c;
    do {
        c = fgetc(file);
        n++;
    } while (c != '\n' && c != '\r' && c != EOF);
    n--;

    if (c == EOF) {
        return NULL;
    }

    char* line = (char*) calloc(n + 1, sizeof(char));

    fseek(file, current, SEEK_SET);
    int i;
    for (i = 0; i < n; i++) {
        line[i] = fgetc(file);
    }

    fgetc(file);
    line[i] = '\0';

    return line;
}

void getExistingUserPassword(char* name, char* pass, int n) {
    FILE* members = fopen("../database/Members.csv", "r");

    char* line;
    while (1) {
        line = readLine(members);
        if (!line) {
            break;
        }
        free(line);
    }

    fclose(members);
}

void getUserInfo(char* input, char* name, char* pass, int n) {
    char* token;

    token = strtok(input, "=");
    token = strtok(NULL, "&");
    strncpy(name, token, n);

    token = strtok(NULL, "=");
    token = strtok(NULL, "&");
    strncpy(pass, token, n);
}

int main() {
    int n = atoi(getenv("CONTENT_LENGTH"));
    char* content = (char*) calloc(n + 1, sizeof(char));

    int i = 0;
    for (i = 0; i < n; i++) {
        char c = getchar();
        if (c == EOF) {
            break;
        }
        content[i] = c;
    }
    content[i] = '\0';

    printf("Content-Type: text/plain;charset=us-ascii\n\n");

    char username[201];
    char password[201];

    getUserInfo(content, username, password, 201);

    printf("username: %s, password: %s\n", username, password);

    getExistingUserPassword(NULL, NULL, 0);

    free(content);

    printf("Done!\n");
    fflush(stdout);

    return EXIT_SUCCESS;
}
