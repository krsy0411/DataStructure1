#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Stack {
    int data[MAX]; // 배열 : 고정 사이즈를 사용합니다.
    int top;
} Stack;

// 스택 초기화
void initialize(Stack* stack) {
    stack->top = -1; // top이 -1이면, 비어있다는 소리
}

// 스택이 비어있는지 확인
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// 스택이 가득 찼는지 확인
int isFull(Stack* stack) {
    return stack->top == MAX - 1; // 주의 : MAX 사이즈의 -1이 top의 최대 인덱스값(0부터 시작이니까)
}

// 스택에 데이터를 추가
void push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack is full!\n");
        return;
    }
    stack->data[++stack->top] = value; // 스택의 (top 인덱스+1) 인덱스 위치에 value값 추가
}

// 스택에서 데이터를 제거
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return -1; // 에러 값을 반환
    }
    return stack->data[stack->top--]; // 주의 : pop할때의 값의 top은 --연산자 이전 -> top값 인덱스의 데이터를 반환하고, 직후 top값을 -1한다.
}

// 스택의 최상단 데이터를 확인
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return -1; // 에러 값을 반환
    }
    return stack->data[stack->top];
}

int main() {
    Stack stack;
    initialize(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top element is %d\n", peek(&stack));

    printf("Popped element is %d\n", pop(&stack));
    printf("Popped element is %d\n", pop(&stack));

    return 0;
}
