#include <stdio.h>
#include <stdlib.h>

typedef int Element; // 큐에 저장할 요소의 타입을 정의합니다.
typedef struct Node {
    Element data;
    struct Node *next; // SinglyLinkedList : 각 노드는 다음 노드를 가리키는 포인터만 존재
} Node;

typedef struct {
    Node *front;
    Node *rear;
    int size; // 리스트는 동적으로 계속 연결될 수 있음 : capacity가 존재할 필요 X
} Queue;

// 큐 초기화 함수
void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

// 큐가 비어있는지 확인하는 함수
int isEmpty(Queue *q) {
    return (q->size == 0);
}

// 큐에 요소를 추가하는 함수 (enqueue)
void enqueue(Queue *q, Element item) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = item;
    newNode->next = NULL;
    if (isEmpty(q)) {
        q->front = newNode;
    } else {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    q->size++;
}

// 큐에서 요소를 제거하는 함수 (dequeue)
Element dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        exit(1);
    }
    Node *temp = q->front;
    Element item = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    q->size--;
    return item;
}

// 큐의 앞에 있는 요소를 반환하는 함수 (peek)
Element peek(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        exit(1);
    }
    return q->front->data;
}

// 큐의 모든 요소를 출력하는 함수
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    Node *current = q->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 큐 메모리 해제 함수
void freeQueue(Queue *q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    displayQueue(&q);

    enqueue(&q, 30);
    displayQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    displayQueue(&q);

    printf("Peek: %d\n", peek(&q));
    displayQueue(&q);

    freeQueue(&q); // 큐 메모리 해제

    return 0;
}
