#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef int Element; // 큐에 저장할 요소의 타입 정의
typedef struct {
    Element data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// 큐 초기화 함수
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// 큐가 비어있는지 확인하는 함수
int isEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

// 큐가 꽉 찼는지 확인하는 함수
int isFull(Queue *q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// 큐에 요소를 추가하는 함수 (enqueue) : rear+1
void enqueue(Queue *q, Element item) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    }
    q->data[q->rear] = item;
}

// 큐에서 요소를 제거하는 함수 (dequeue) ; front+1
Element dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        exit(1);
    }
    Element item = q->data[q->front];
    if (q->front == q->rear) { // 큐가 비게 된 경우 : 이건 아예 비어있는 경우는 아님
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    }
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
    int i = q->front;
    while (i != q->rear) {
        printf("%d ", q->data[i]);
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    printf("%d\n", q->data[i]);
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    printQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    printQueue(&q);

    printf("Peek: %d\n", peek(&q));
    printQueue(&q);

    return 0;
}
