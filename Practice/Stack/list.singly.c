#include <stdio.h>
#include <stdlib.h>

// 스택 노드 정의
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 스택 초기화
void initialize(Node** top) {
    *top = NULL;
}

// 스택이 비어있는지 확인
int isEmpty(Node* top) {
    return top == NULL;
}

// 스택에 데이터를 추가
void push(Node** top, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error!\n");
        return;
    }
    newNode->data = value;
    newNode->next = *top;
    *top = newNode;
}

// 스택에서 데이터를 제거
int pop(Node** top) {
    if (isEmpty(*top)) {
        printf("Stack is empty!\n");
        return -1; // 에러 값을 반환
    }
    Node* temp = *top;
    int poppedValue = temp->data;
    *top = (*top)->next;
    free(temp);
    return poppedValue;
}

// 스택의 최상단 데이터를 확인
int peek(Node* top) {
    if (isEmpty(top)) {
        printf("Stack is empty!\n");
        return -1; // 에러 값을 반환
    }
    return top->data;
}

int main() {
    Node* stack;
    initialize(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top element is %d\n", peek(stack));

    printf("Popped element is %d\n", pop(&stack));
    printf("Popped element is %d\n", pop(&stack));

    return 0;
}
