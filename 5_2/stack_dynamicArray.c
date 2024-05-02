#include <stdio.h>
#include <stdlib.h>

typedef struct DynamicArrayStack {
    int top;
    int capacity;
    int* array;
} DynamicArrayStack;

DynamicArrayStack* createStack() {
    DynamicArrayStack* dynamicStack = malloc(sizeof(DynamicArrayStack));

    printf("다이나믹 배열의 초기 사이즈를 입력하세요 >> ");
    scanf("%d", &dynamicStack->capacity);
    dynamicStack->top = -1;
    dynamicStack->array = (int *)malloc(dynamicStack->capacity * sizeof(int));

    return dynamicStack;
}

void destoryStack(DynamicArrayStack* stack) {
    if(stack->array) {
        free(stack->array);
    }
    free(stack);
}

int main() {
    DynamicArrayStack* stack = createStack();

    return 0;
}