#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// List of keywords
const char* keywords[] = {
    "int", "float", "if", "else", "while", "do", "return", "for", "char", "double", "void"
};
int keywordCount = sizeof(keywords) / sizeof(keywords[0]);

// Function to check if a string is a keyword
int isKeyword(const char* word) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>';
}

// Main lexer function
void lexicalAnalyzer(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Unable to open file.\n");
        return;
    }

    char ch, buffer[MAX];
    int i = 0;

    while ((ch = fgetc(fp)) != EOF) {
        // If the character is a separator
        if (isspace(ch) || ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}') {
            if (i > 0) {
                buffer[i] = '\0';
                if (isKeyword(buffer))
                    printf("Keyword: %s\n", buffer);
                else
                    printf("Identifier: %s\n", buffer);
                i = 0;
            }
        }
        // If the character is an operator
        else if (isOperator(ch)) {
            if (i > 0) {
                buffer[i] = '\0';
                if (isKeyword(buffer))
                    printf("Keyword: %s\n", buffer);
                else
                    printf("Identifier: %s\n", buffer);
                i = 0;
            }
            printf("Operator: %c\n", ch);
        }
        // If it's part of a word/identifier
        else {
            buffer[i++] = ch;
        }
    }

    fclose(fp);
}

// Entry point
int main() {
    const char* filename = "input.txt";
    lexicalAnalyzer(filename);
    return 0;
}
