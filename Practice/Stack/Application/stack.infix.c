#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

// 스택의 기본적인 함수
typedef struct Stack {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isFull(Stack* s) {
    return s->top == MAX-1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->data[++(s->top)] = value;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return -1;
    }

    return s->data[(s->top)--];
}

int peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }

    return s->data[s->top];
}

////////////////////////////////////////////////////////////

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

// 중위표기법 계산 함수
// 문자열 배열을 인자로 받습니다
int evaluateInfix(char* expression) {
    Stack values;
    Stack ops;
    initStack(&values);
    initStack(&ops);

    for (int i = 0; expression[i]; i++) {
        if (expression[i] == ' ') {
            continue;
        } else if (isdigit(expression[i])) {
            int val = 0;
            while (i < strlen(expression) && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            push(&values, val);
            i--;
        } else if (expression[i] == '(') {
            push(&ops, expression[i]);
        } else if (expression[i] == ')') {
            while (!isEmpty(&ops) && peek(&ops) != '(') {
                int val2 = pop(&values);
                int val1 = pop(&values);
                char op = pop(&ops);
                push(&values, applyOp(val1, val2, op));
            }
            if (!isEmpty(&ops)) {
                pop(&ops);
            }
        } else {
            while (!isEmpty(&ops) && precedence(peek(&ops)) >= precedence(expression[i])) {
                int val2 = pop(&values);
                int val1 = pop(&values);
                char op = pop(&ops);
                push(&values, applyOp(val1, val2, op));
            }
            push(&ops, expression[i]);
        }
    }
    return pop(&values);
}

int main() {
    char infixExpression[] = "3+5*2-8";
    printf("Infix Evaluation : %s = %d\n", infixExpression, evaluateInfix(infixExpression));
}