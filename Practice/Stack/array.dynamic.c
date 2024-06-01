#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int *data;
    int top;
    int capacity;
} Stack;

// 스택 초기화
void initialize(Stack *stack, int initialCapacity) {
    stack->data = (int *)malloc(initialCapacity * sizeof(int));
    stack->top = -1;
    stack->capacity = initialCapacity;
}

// 스택이 비어있는지 확인
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// 스택이 가득 찼는지 확인
int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

// 스택의 크기를 두 배로 증가
void resize(Stack *stack) {
    stack->capacity *= 2;
    stack->data = (int *)realloc(stack->data, stack->capacity * sizeof(int));
    if (!stack->data) {
        printf("Memory allocation error!\n");
        exit(1);
    }
}

// 스택에 데이터를 추가
void push(Stack *stack, int value) {
    if (isFull(stack)) {
        resize(stack);
    }
    stack->data[++stack->top] = value;
}

// 스택에서 데이터를 제거
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return -1; // 에러 값을 반환
    }
    return stack->data[stack->top--];
}

// 스택의 최상단 데이터를 확인
int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return -1; // 에러 값을 반환
    }
    return stack->data[stack->top];
}

// 스택 해제
void freeStack(Stack *stack) {
    free(stack->data);
}

int main() {
    Stack stack; // 구조체 변수 선언
    initialize(&stack, 2); // 초기 용량을 2로 설정

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30); // 용량이 부족할 때 자동으로 증가

    printf("Top element is %d\n", peek(&stack));

    printf("Popped element is %d\n", pop(&stack));
    printf("Popped element is %d\n", pop(&stack));

    freeStack(&stack); // 스택 해제

    return 0;
}