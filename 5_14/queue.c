#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int capacity; // 큐의 크기
    int front;    // 프론트 인덱스
    int rear;     // 리어 인덱스
    int size;     // 현재 큐의 원소 개수
    int *array;   // 큐 배열의 주소
} Queue;

Queue* initialize(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = capacity - 1;
    queue->size = 0;
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

void enqueue(Queue* q, int value) {
    if (q->size == q->capacity) {
        printf("큐가 가득 찼습니다.\n");
        return;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->array[q->rear] = value;
    q->size++;
    printf("삽입된 값: %d\n", value);
}

void dequeue(Queue* q) {
    if (q->size == 0) {
        printf("큐가 비어 있습니다.\n");
        return;
    }
    printf("빠진 값: %d\n", q->array[q->front]);
    q->front = (q->front + 1) % q->capacity;
    q->size--;
}

int is_full(Queue* q) {
    return q->size == q->capacity;
}

int is_empty(Queue* q) {
    return q->size == 0;
}

void print_queue(Queue* q) {
    if (is_empty(q)) {
        printf("큐가 비어 있습니다.\n");
        return;
    }

    printf("큐 내용: ");
    for (int i = 0; i < q->size; i++) {
        int index = (q->front + i) % q->capacity;
        printf("%d ", q->array[index]);
    }
    printf("\n");
}

int main(void) {
    int capacity;
    printf("큐의 사이즈를 입력하세요: ");
    scanf("%d", &capacity);

    Queue* q = initialize(capacity);

    // enqueue 테스트
    for (int i = 1; i <= capacity; i++) {
        enqueue(q, i * 10);
    }
    print_queue(q);

    // dequeue 테스트
    for (int i = 1; i <= capacity; i++) {
        dequeue(q);
    }
    print_queue(q);

    free(q->array);
    free(q);

    return 0;
}
