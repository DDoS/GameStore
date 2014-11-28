#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int n = atoi(getenv("CONTENT_LENGTH")) + 1;
    char* content = (char*) calloc(n, sizeof(char));

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

    printf("username: %s, password: %s", username, password);

    free(content);

    return EXIT_SUCCESS;
}
