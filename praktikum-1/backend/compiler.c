#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *keywords[] = {
    "if", "else", "for", "while", "return",
    "int", "float", "char", "double", "void",
    "do", "switch", "case", "break", "continue",
    "struct", "typedef", "enum", "const", "long",
    "short", "unsigned", "signed", "static", "extern"
};
int keywordCount = 25;

int isKeyword(char *str) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isSymbol(char c) {
    char symbols[] = "+-*/=(){};,<>!&|^~%[]:.?";
    for (int i = 0; i < (int)strlen(symbols); i++) {
        if (c == symbols[i])
            return 1;
    }
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '<' || c == '>' || c == '!' || c == '&' || c == '|' || c == '^';
}

int isMathExpression(char *str) {
    for (int i = 0; i < (int)strlen(str); i++) {
        if (isOperator(str[i]))
            return 1;
    }
    return 0;
}

void trim(char *str) {
    int start = 0;
    while (isspace((unsigned char)str[start])) start++;
    if (start > 0)
        memmove(str, str + start, strlen(str) - start + 1);

    int end = (int)strlen(str) - 1;
    while (end >= 0 && isspace((unsigned char)str[end])) {
        str[end] = '\0';
        end--;
    }
}

int main() {
    char line[1000];
    char input[10000];  
    input[0] = '\0';

    while (fgets(line, sizeof(line), stdin)) {
        if (strcmp(line, "END\n") == 0 || strcmp(line, "END") == 0)
            break;
        strcat(input, line);
    }

    int i = 0;
    char token[500];

    while (input[i] != '\0') {

        if (isspace((unsigned char)input[i])) {
            i++;
            continue;
        }

        if (input[i] == '/' && input[i+1] == '/') {
            char comment[500];
            int k = 0;
            while (input[i] != '\n' && input[i] != '\0')
                comment[k++] = input[i++];
            comment[k] = '\0';
            printf("%s:COMMENT\n", comment);
            continue;
        }

        if (input[i] == '/' && input[i+1] == '*') {
            char comment[500];
            int k = 0;
            comment[k++] = input[i++]; 
            comment[k++] = input[i++]; 
            while (!(input[i] == '*' && input[i+1] == '/') && input[i] != '\0') {
                comment[k++] = input[i++];
            }
            if (input[i] != '\0') {
                comment[k++] = input[i++]; 
                comment[k++] = input[i++]; 
            }
            comment[k] = '\0';
            printf("%s:COMMENT\n", comment);
            continue;
        }

        if (input[i] == '"') {
            char str_lit[500];
            int k = 0;
            str_lit[k++] = input[i++]; 
            while (input[i] != '"' && input[i] != '\0') {
                if (input[i] == '\\' && input[i+1] != '\0')
                    str_lit[k++] = input[i++]; 
                str_lit[k++] = input[i++];
            }
            if (input[i] == '"')
                str_lit[k++] = input[i++]; 
            str_lit[k] = '\0';
            printf("%s:STRING LITERAL\n", str_lit);
            continue;
        }

        if (input[i] == '\'') {
            char ch_lit[20];
            int k = 0;
            ch_lit[k++] = input[i++];
            while (input[i] != '\'' && input[i] != '\0') {
                if (input[i] == '\\' && input[i+1] != '\0')
                    ch_lit[k++] = input[i++];
                ch_lit[k++] = input[i++];
            }
            if (input[i] == '\'')
                ch_lit[k++] = input[i++];
            ch_lit[k] = '\0';
            printf("%s:CHAR LITERAL\n", ch_lit);
            continue;
        }

        if (isdigit((unsigned char)input[i]) ||
            (input[i] == '-' && isdigit((unsigned char)input[i+1]))) {
            char num[100];
            int k = 0;
            int isFloat = 0;
            if (input[i] == '-') num[k++] = input[i++];
            while (isdigit((unsigned char)input[i]) || input[i] == '.') {
                if (input[i] == '.') isFloat = 1;
                num[k++] = input[i++];
            }
            num[k] = '\0';
            printf("%s:%s\n", num, isFloat ? "FLOAT NUMBER" : "INTEGER NUMBER");
            continue;
        }

        if (isalpha((unsigned char)input[i]) || input[i] == '_') {
            int j = 0;
            while (isalnum((unsigned char)input[i]) || input[i] == '_') {
                token[j++] = input[i++];
            }
            token[j] = '\0';

            int temp = i;
            while (isspace((unsigned char)input[temp])) temp++;

            if (input[temp] == '=' && input[temp+1] != '=') {
                printf("%s:VARIABLE\n", token);
                printf("=:SYMBOL\n");
                i = temp + 1;

                int k = 0;
                char expr[500];
                while (input[i] != ';' && input[i] != '\n' && input[i] != '\0') {
                    expr[k++] = input[i++];
                }
                expr[k] = '\0';
                trim(expr);

                if (isMathExpression(expr))
                    printf("%s:MATH EXPRESSION\n", expr);
                else
                    printf("%s:VALUE\n", expr);

            } else if (isKeyword(token)) {
                printf("%s:RESERVED WORD\n", token);
            } else {
                printf("%s:IDENTIFIER\n", token);
            }
            continue;
        }

        if (isSymbol(input[i])) {
            char op[3] = {0};
            op[0] = input[i];
            op[1] = input[i+1];

            if ((input[i] == '=' && input[i+1] == '=') ||
                (input[i] == '!' && input[i+1] == '=') ||
                (input[i] == '<' && input[i+1] == '=') ||
                (input[i] == '>' && input[i+1] == '=') ||
                (input[i] == '&' && input[i+1] == '&') ||
                (input[i] == '|' && input[i+1] == '|') ||
                (input[i] == '+' && input[i+1] == '+') ||
                (input[i] == '-' && input[i+1] == '-') ||
                (input[i] == '+' && input[i+1] == '=') ||
                (input[i] == '-' && input[i+1] == '=') ||
                (input[i] == '*' && input[i+1] == '=') ||
                (input[i] == '/' && input[i+1] == '=')) {
                printf("%s:OPERATOR\n", op);
                i += 2;
            } else {
                printf("%c:SYMBOL\n", input[i]);
                i++;
            }
            continue;
        }

        printf("%c:UNKNOWN\n", input[i]);
        i++;
    }

    return 0;
}