#include <stdio.h>
#include <stdlib.h>

// 원형 큐 구조체 정의
typedef struct {
    int *array;
    int front;
    int rear;
    int size;
    int capacity;
} CircularQueue;

// 큐 초기화 함수
CircularQueue* createQueue(int capacity) {
    CircularQueue* queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

// 큐가 비었는지 확인
int isEmpty(CircularQueue* queue) {
    return (queue->size == 0);
}

// 큐가 가득 찼는지 확인
int isFull(CircularQueue* queue) {
    return (queue->size == queue->capacity);
}

// 큐의 크기 두 배로 늘리기
void resizeQueue(CircularQueue* queue) {
    int newCapacity = queue->capacity * 2;
    int *newArray = (int*)malloc(newCapacity * sizeof(int));

    // 원형 큐의 요소를 새로운 배열로 복사
    for (int i = 0; i < queue->size; i++) {
        newArray[i] = queue->array[(queue->front + i) % queue->capacity];
    }

    free(queue->array);
    queue->array = newArray;
    queue->capacity = newCapacity;
    queue->front = 0;
    queue->rear = queue->size - 1;
}

// 큐에 원소 추가 (enQueue)
void enQueue(CircularQueue* queue, int item) {
    if (isFull(queue)) {
        printf("큐가 가득 찼습니다. 크기를 두 배로 늘립니다.\n");
        resizeQueue(queue);
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size += 1;
    printf("%d 추가됨\n", item);
}

// 큐에서 원소 제거 (deQueue)
int deQueue(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("큐가 비었습니다.\n");
        return -1;
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size -= 1;
    return item;
}

// 큐의 front 원소 확인
int front(CircularQueue* queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    return queue->array[queue->front];
}

// 큐의 rear 원소 확인
int rear(CircularQueue* queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    return queue->array[queue->rear];
}

// 큐의 내용 출력
void printQueue(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("큐가 비어 있습니다.\n");
        return;
    }

    int i = queue->front;
    printf("큐 내용: ");
    for (int count = 0; count < queue->size; count++) {
        printf("%d ", queue->array[i]);
        i = (i + 1) % queue->capacity;
    }
    printf("\n");
}

// 메모리 해제
void freeQueue(CircularQueue* queue) {
    free(queue->array);
    free(queue);
}

int main() {
    CircularQueue* queue = createQueue(5);

    enQueue(queue, 10);
    enQueue(queue, 20);
    enQueue(queue, 30);
    enQueue(queue, 40);
    enQueue(queue, 50);

    printQueue(queue);

    enQueue(queue, 60);
    enQueue(queue, 70);

    printQueue(queue);

    printf("deQueue: %d\n", deQueue(queue));
    printf("deQueue: %d\n", deQueue(queue));

    printQueue(queue);

    freeQueue(queue);
    return 0;
}