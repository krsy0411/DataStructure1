#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedListNode {
    int data;
    struct LinkedListNode *nextNodePtr;
} LinkedListNode;

typedef struct StackLL {
    int capacity;
    int size;
    LinkedListNode *array;
} StackLL;

int is_full(StackLL* s) {
    // 최대용량과 현재 링크드리스트의 사이즈가 같다면, 꽉찬상태를 의미
    return s->capacity == s->size;
}

int is_empty(StackLL* s) {
    // 링크드리스트의 헤드노드의 데이터값이 null이면, 비어있음을 의미
    return s->array == NULL;
}

StackLL* create() {
    StackLL* stack = (StackLL *)malloc(sizeof(StackLL));

    printf("리스트 사이즈 입력해주세요 >> ");
    scanf("%d", &stack->capacity);
    
    stack->size = 0; stack->array = NULL;

    return stack;
}

void push(StackLL* s, int data) {
    if(is_full(s)) {
        printf("스택 overflow 발생\n");
        return;
    }

    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->data = data;
    newNode->nextNodePtr = s->array;
    s->array = newNode; 
    s->size++; 
}

void pop(StackLL* s) {
    if (is_empty(s)) {
        printf("스택 underflow 발생\n");
        return;
    }

    LinkedListNode* temp = s->array; 
    s->array = s->array->nextNodePtr; 
    free(temp); 
    s->size--; 
}

void peek(StackLL* s) {
    if (is_empty(s)) {
        printf("empty 스택\n");
        return;
    }
    printf("꼭대기 위치 원소 값: %d\n", s->array->data);
}

void print_stack(StackLL* s) {
    if (is_empty(s)) {
        printf("Stack is empty\n");
        return;
    }
    for(LinkedListNode* temp = s->array; temp != NULL; temp = temp->nextNodePtr) {
        if(temp->nextNodePtr == NULL) {
            printf("%d", temp->data);
        } else {
            printf("%d -> ", temp->data);
        }
    }
    printf("\n");
}

int main() {
    StackLL* stack = create();

    for(int i=1; i<= 6; i++) {
        push(stack, i*10);
    }

    for(int i=0; i<3; i++) {
        pop(stack);
    }

    print_stack(stack);

    return 0;
}