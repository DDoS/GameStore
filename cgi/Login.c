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

void copyStringNoEscape(char* dest, char* source, int n) {
    int i, j;
    char c;
    for (i = 0, j = 0; i < n && (c = source[i]); i++) {
        if (c != '\\') {
            dest[j++] = c;
        }
    }
}

int parseElements(char* line, char** elements, int n) {
    int i = 0, j = 0, start = 0;
    char c, escaped = 0;
    while (1) {
        c = line[i];
        if (c == '\\') {
            escaped = 1;
        } else if (c == ',' && !escaped || !c) {
            int size = i - start;
            elements[j] = (char*) calloc(size + 1, sizeof(char));
            copyStringNoEscape(elements[j], line + start * sizeof(char), size);
            elements[j][size] = '\0';
            if (++j >= n || !c) {
                break;
            }
            start = i + 1;
        } else {
            escaped = 0;
        }
        i++;
    }

    int k;
    for (k = j; k < n; k++) {
        elements[k] = NULL;
    }

    return j;
}

char validatePassword(char* name, char* pass) {
    FILE* members = fopen("../database/Members.csv", "r");

    char* line;
    char valid = 0;
    while (!valid) {
        line = readLine(members);
        if (!line) {
            break;
        }

        char* elements[3];
        parseElements(line, elements, 3);

        if (strcmp(elements[1], name) == 0) {
            valid = strcmp(elements[2], pass) == 0;
        }

        free(line);
        free(elements[0]);
        free(elements[1]);
        free(elements[2]);
    }

    fclose(members);

    return valid;
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

void copyFile(FILE* from, FILE* to) {
    int c;
    while ((c = fgetc(from)) != EOF) {
        fputc(c, to);
    }
}

void printRedirect(char* file) {
    printf("<html>\n<head>\n<meta http-equiv=\"REFRESH\"\ncontent=\"0;url=%s\">\n</head>\n</html>\n", file);
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

    char username[201];
    char password[201];
    getUserInfo(content, username, password, 201);
    char goodPassword = validatePassword(username, password);

    printf("Content-Type:text/html\n\n");

    if (goodPassword) {
        FILE* loggedIn = fopen("../database/LoggedIn.csv", "a");
        fprintf(loggedIn, "%s\n", username);
        fclose(loggedIn);
        printRedirect("../catalogue.html");
    } else {
        printRedirect("../login_error.html");
    }

    free(content);

    fflush(stdout);

    return EXIT_SUCCESS;
}
