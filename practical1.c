

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100


int stack[MAX];
int top = -1;

void push(int val) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    stack[++top] = val;
}

int pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}


int evaluatePostfix(char *exp) {
    int i = 0;
    while (exp[i] != '\0') {
        char ch = exp[i];


        if (ch == ' ') {
            i++;
            continue;
        }


        if (isdigit(ch)) {
            int num = 0;

            while (isdigit(exp[i])) {
                num = num * 10 + (exp[i] - '0');
                i++;
            }
            push(num);
            continue; // i already incremented, isliye i++ skip
        }

        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            int val2 = pop();
            int val1 = pop();
            int result;

            switch (ch) {
                case '+': result = val1 + val2; break;
                case '-': result = val1 - val2; break;
                case '*': result = val1 * val2; break;
                case '/':
                    if (val2 == 0) {
                        printf("Error: Division by zero\n");
                        exit(1);
                    }
                    result = val1 / val2;
                    break;
                case '^': {
                    int r = 1;
                    for (int j = 0; j < val2; j++) r *= val1;
                    result = r;
                    break;
                }
                default: result = 0;
            }
            push(result);
        }
        else {
            printf("Invalid character in expression: %c\n", ch);
            exit(1);
        }
        i++;
    }

    int finalResult = pop();

    if (!isEmpty()) {
        printf("Error: Invalid postfix expression\n");
        exit(1);
    }

    return finalResult;
}


int main() {
    char exp[MAX];

    printf("Enter postfix expression (space separated for multi-digit numbers): ");
    fgets(exp, MAX, stdin);

    // remove trailing newline
    exp[strcspn(exp, "\n")] = '\0';

    int result = evaluatePostfix(exp);
    printf("Result = %d\n", result);
