#include <stdio.h>
#include <stdlib.h>

typedef int Element; // 큐에 저장할 요소의 타입을 정의
typedef struct {
    Element *data;
    int front;
    int rear;
    int capacity;
    int size;
} Queue;

// 큐 초기화 함수
void initQueue(Queue *q, int initialCapacity) {
    q->data = (Element *)malloc(initialCapacity * sizeof(Element));
    if (q->data == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    q->front = 0;
    q->rear = -1;
    q->capacity = initialCapacity;
    q->size = 0;
}

// 큐가 비어있는지 확인하는 함수
int isEmpty(Queue *q) {
    return (q->size == 0);
}

// 큐가 꽉 찼는지 확인하는 함수
int isFull(Queue *q) {
    return (q->size == q->capacity);
}

// 큐의 크기를 두 배로 늘리는 함수
void resizeQueue(Queue *q) {
    int newCapacity = q->capacity * 2;
    Element *newData = (Element *)malloc(newCapacity * sizeof(Element));
    if (newData == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < q->size; i++) {
        newData[i] = q->data[(q->front + i) % q->capacity];
    }

    free(q->data);
    q->data = newData;
    q->front = 0;
    q->rear = q->size - 1;
    q->capacity = newCapacity;
}

// 큐에 요소를 추가하는 함수 (enqueue)
void enqueue(Queue *q, Element item) {
    if (isFull(q)) {
        resizeQueue(q);
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = item;
    q->size++;
}

// 큐에서 요소를 제거하는 함수 (dequeue)
Element dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        exit(1);
    }
    Element item = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return item;
}

// 큐의 앞에 있는 요소를 반환하는 함수 (peek)
Element peek(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        exit(1);
    }
    return q->data[q->front];
}

// 큐의 모든 요소를 출력하는 함수
void printQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    for (int i = 0; i < q->size; i++) {
        printf("%d ", q->data[(q->front + i) % q->capacity]);
    }
    printf("\n");
}

// 큐 메모리 해제 함수
void freeQueue(Queue *q) {
    free(q->data);
}

int main() {
    Queue q;
    initQueue(&q, 2); // 초기 용량을 2로 설정

    enqueue(&q, 10);
    enqueue(&q, 20);
    printQueue(&q);

    enqueue(&q, 30); // 큐가 가득 차면 크기를 늘립니다.
    printQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    printQueue(&q);

    printf("Peek: %d\n", peek(&q));
    printQueue(&q);

    freeQueue(&q); // 큐 메모리 해제

    return 0;
}
