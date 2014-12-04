#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeCSVRow(FILE* file, char** entries, int n) {
    fputc('\n', file);

    int i;
    for (i = 0; i < n; i++) {
        char* entry = entries[i];

        char c;
        while (c = *(entry++)) {
            if (c == ',') {
                fputc('\\', file);
            }
            fputc(c, file);
        }

        if (i < n - 1) {
            fputc(',', file);
        }
    }
}

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
    FILE* members = fopen("database/Members.csv", "r");

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
    int last;

    token = strtok(input, "=");
    token = strtok(NULL, "\n");
    strncpy(name, token, n);
    last = strlen(name) - 1;
    if (name[last] == '\r') {
        name[last] = '\0';
    }

    token = strtok(NULL, "=");
    token = strtok(NULL, "\n");
    strncpy(pass, token, n);
    last = strlen(pass) - 1;
    if (pass[last] == '\r') {
        pass[last] = '\0';
    }
}

void copyWithInject(FILE* from, FILE* to, char* match, char* inject) {
    int c;
    int n = strlen(match), i = 0;
    while ((c = fgetc(from)) != EOF) {

        if (c == match[i]) {
            i++;
        } else {
            i = 0;
        }

        fputc(c, to);

        if (i == n) {
            char* injectPointer = inject;
            while (c = *(injectPointer++)) {
                fputc(c, to);
            }
            i = 0;
        }
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
        FILE* loggedIn = fopen("database/LoggedIn.csv", "a");
        char* usernamePointer = username;
        writeCSVRow(loggedIn, &usernamePointer, 1);
        fclose(loggedIn);
        FILE* catalogue = fopen("catalogue.html", "r");
        char* injectFormat = "<input type='hidden' name='username' value=\"%s\"/>";
        char inject[260];
        sprintf(inject, injectFormat, username);
        copyWithInject(catalogue, stdout, "<!--INPUT_USERNAME-->", inject);
        fclose(catalogue);
    } else {
        printRedirect("login_error.html");
    }

    free(content);

    fflush(stdout);

    return EXIT_SUCCESS;
}
