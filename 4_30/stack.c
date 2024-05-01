#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    int size;
    int top;
    int* array;
} stack;

int is_empty(stack *s) {
    return s->top == -1;
}

int is_full(stack *s) {
    return s->top == s->size-1;
}

void push(int element, struct stack* s) {
    if(is_full(s)) {
        printf("포화 상태\n");
    } else {
        s->array[++(s->top)] = element;
    }
}

void pop(stack* s) {
    if(is_empty(s)) {
        printf("없는 상태\n");
    } else {
        printf("뽑힌 원소의 값 : %d\n", s->array[(s->top)--]);
    }
}

// 스택 생성 및 초기화
void createStack(stack *s, int size) {
    s->top = -1;
    s->array = (int *)malloc(size * sizeof(int));
    s->size = size;
}

void peek(stack *s) {
    if(is_full(s)) {
        printf("포화 상태\n");
    }
    else {
        printf("제일 마지막에 들어온 값 : %d\n", s->array[s->top]);
    }
}

void print_stack(stack *s) {
    for(int i=s->top; i!=-1; i--) {
        printf("%d -> ", s->array[i]);
    }
    printf("\n");
}

int main() {
    // 구조체 사이즈만큼 동적 메모리 할당
    stack* st = (stack *)malloc(sizeof(stack)); 
    int size;

    printf("스택 사이즈를 입력해주세요 >> ");
    scanf("%d", &size);

    createStack(st, size);
    for(int i=1; i<=10; i++) {
        push(i, st);
    }

    peek(st);

    for(int i=0; i<3; i++) {
        pop(st);
    }

    print_stack(st);

    free(st->array);
    free(st);

    return 0;
}