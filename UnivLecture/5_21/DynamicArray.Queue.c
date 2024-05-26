#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Queue {
    int capacity;
    int size;
    int removedIndex;
    int front;
    int rear;
    int* array;
} Queue;

// 큐가 비어있는지 확인하는 함수
int is_empty(Queue* q) {
    return q->size == 0;
}

// 큐가 가득 찼는지 확인하는 함수
int is_full(Queue* q) {
    return q->rear == q->capacity-1;
}

// 큐의 내용을 출력하는 함수
void printQueue(Queue* q) {
    if (is_empty(q)) {
        printf("큐가 비어 있습니다.\n");
        return;
    }

    printf("큐 내용: ");
    for (int i = 0; i < q->size; i++) {
        printf("%d ", q->array[(q->front + i) % q->capacity]);
    }
    printf("\n");
}

// 큐에 원소를 추가하는 함수
void enQueue(Queue* q) {
    srand(time(0));
    for(int i=0; i<q->capacity; i++) {
        int value = (rand() % 100) + 1; // 1~100의 랜덤 값 생성

        q->rear = (q->rear + 1) % q->capacity;
        q->array[q->rear] = value;
        q->size++;
    }
}

int deQueue(Queue* q, int N) {
    if(is_empty(q)) {
        return 1;
    }

    // 제거 연산 수행
    srand(time(0));
    int K = (rand() % (N - 1)) + 1; // 1 ~ N-1 사이의 랜덤 값
    int index_to_remove = (q->removedIndex + K - 1) % q->capacity;

    // 선택된 위치의 데이터 제거
    for (int i = index_to_remove; i != q->rear; i = (i + 1) % q->capacity) {
        q->array[i] = q->array[(i + 1) % q->capacity];
    }

    q->size--; // capacity값 갱신
    q->rear = (q->rear - 1 + q->capacity) % q->capacity; // rear값 갱신

    // 큐의 내용 출력
    printQueue(q);

    return 0;
}

Queue* initialize() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = 5;
    queue->size = 0;
    queue->removedIndex = 0;
    queue->front = 0;
    queue->rear = 4;
    queue->array = (int *)malloc(5 * sizeof(int));
    enQueue(queue);

    return queue;
}

void freeQueue(Queue* q) {
    free(q->array);
    free(q);
}

int main(void) {
    Queue* queue = initialize();
    int isEnd = 0;
    printf("현재 큐의 사이즈는 5입니다.\n----------------------------\n");
    printf("[삭제 전] ");
    printQueue(queue);

    while(!isEnd) {
        int N;
        srand(time(0));
        N = rand() % 21;
        isEnd = deQueue(queue, N);
    }
    printf("----------------------------\n프로그램 종료.");

    free(queue);
    return 0;
}