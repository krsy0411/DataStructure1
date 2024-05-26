#include <stdio.h>
#include <stdlib.h>

// 스택 구조체 정의
typedef struct Stack {
    char data;
    struct Stack* next;
} Stack;

// 스택 초기화 함수
void initialize(Stack** top) {
    *top = NULL;
}

// 스택이 비어있는지 확인하는 함수
int is_empty(Stack* top) {
    return top == NULL;
}

// 스택에 원소 추가 함수
void push(Stack** top, char data) {
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

// 스택에서 원소 제거 함수
void pop(Stack** top) {
    if (is_empty(*top)) {
        printf("스택이 비어있습니다.\n");
        return;
    }
    Stack* temp = *top;
    *top = (*top)->next;
    free(temp);
}

// 스택에서 가장 위의 원소 반환 함수
char peek(Stack* top) {
    if (is_empty(top)) {
        printf("스택이 비어있습니다.\n");
        return '\0';
    }
    return top->data;
}

// 수식의 괄호 사용이 올바른지 확인하는 함수
void checkParentheses(char* expression) {
    Stack* stack;
    initialize(&stack);
    int index = 0;
    char ch;
    while ((ch = expression[index]) != '\0') {
        if (ch == '(' || ch == '[' || ch == '{') {
            push(&stack, ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (is_empty(stack)) {
                printf("열린 괄호와 닫힌 괄호의 짝이 맞지 않습니다.\n");
                return;
            }
            char top = peek(stack);
            if ((ch == ')' && top == '(') || (ch == ']' && top == '[') || (ch == '}' && top == '{')) {
                pop(&stack);
            } else {
                printf("괄호의 짝이 맞지 않습니다.\n");
                return;
            }
        }
        index++;
    }
    if (!is_empty(stack)) {
        printf("열린 괄호와 닫힌 괄호의 짝이 맞지 않습니다.\n");
        return;
    }
    printf("수식의 괄호 사용이 정상적입니다.\n");
}

int main() {
    char expression[100];
    
    printf("수식을 입력하세요: ");
    fgets(expression, sizeof(expression), stdin);
    
    printf("입력한 수식: %s", expression);
    
    checkParentheses(expression);
    
    return 0;
}