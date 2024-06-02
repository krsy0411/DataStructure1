#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

// 전위표기법 계산 함수
// 인자로 문자열 배열을 받습니다
int evaluatePrefix(char* exp) {
    Stack stack;
    initStack(&stack);
    
    int length = 0;
    while (exp[length] != '\0') {
        length++;
    }
    
    for (int i = length - 1; i >= 0; i--) {
        if (isdigit(exp[i])) {
            push(&stack, exp[i] - '0');
        } else {
            int val1 = pop(&stack);
            int val2 = pop(&stack);
            switch (exp[i]) {
                case '+': push(&stack, val1 + val2); break;
                case '-': push(&stack, val1 - val2); break;
                case '*': push(&stack, val1 * val2); break;
                case '/': push(&stack, val1 / val2); break;
            }
        }
    }
    return pop(&stack);
}

int main() {
    char prefixExp[] = "-+2319";
    printf("Prefix Evaluation: %s = %d\n", prefixExp, evaluatePrefix(prefixExp));

    return 0;
}