#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int capacity; // 큐의 크기
    int front;    // 프론트 인덱스
    int rear;     // 리어 인덱스
    int *array;   // 큐 배열의 주소
} Queue;

// 큐 초기화 함수
Queue* initialize(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

// 큐가 비어있는지 확인하는 함수
int is_empty(Queue* q) {
    return q->front > q->rear;
}

// 큐가 가득 찼는지 확인하는 함수
int is_full(Queue* q) {
    return q->rear == q->capacity - 1;
}

// 큐에 원소를 추가하는 함수
void enqueue(Queue* q, int value) {
    if (is_full(q)) {
        printf("큐가 가득 찼습니다.\n");
        return;
    }
    q->rear++;
    q->array[q->rear] = value;
    printf("삽입된 값: %d\n", value);
}

// 큐에서 원소를 제거하는 함수
void dequeue(Queue* q) {
    if (is_empty(q)) {
        printf("큐가 비어 있습니다.\n");
        return;
    }
    printf("빠진 값: %d\n", q->array[q->front]);
    q->front++;
}

// 큐의 내용을 출력하는 함수
void print_queue(Queue* q) {
    if (is_empty(q)) {
        printf("큐가 비어 있습니다.\n");
        return;
    }

    printf("큐 내용: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->array[i]);
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
    for (int i = 1; i <= 4; i++) {
        dequeue(q);
    }
    print_queue(q);

    free(q->array);
    free(q);

    return 0;
}