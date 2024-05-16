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
    // 실제 데이터를 담아두는 배열(포인터)에, 동적 메모리 할당 : 인자로 받은 capacity값만큼
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

int is_full(Queue* q) {
    // full 판별 : 큐의 현재 원소 개수(사이즈)가 최대 수용 개수(capacity)와 같은지 체크
    return q->size == q->capacity;
}

int is_empty(Queue* q) {
    // empty 판별 : 큐의 현재 원소 개수(사이즈)가 0인지 체크
    return q->size == 0;
}

void enqueue(Queue* q, int value) {
    if (is_full(q)) {
        printf("큐가 가득 찼습니다.\n");
        return;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->array[q->rear] = value;
    q->size++;
    printf("삽입된 값: %d\n", value);
}

void dequeue(Queue* q) {
    if (is_empty(q)) {
        printf("큐가 비어 있습니다.\n");
        return;
    }
    printf("빠진 값: %d\n", q->array[q->front]);
    q->front = (q->front + 1) % q->capacity;
    q->size--;
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
    // 큐의 사이즈를 capacity 변수에 저장
    int capacity;
    printf("큐의 사이즈를 입력하세요: ");
    scanf("%d", &capacity);
    // 큐 구조체 포인터 변수(: 변수의 주소값 저장)에, (큐 구조체) 포인터 변수(: 변수 주소값 저장)를 반환하는 "초기화"함수 실행 : 인자로 최대 수용공간 값을 넘겨줌
    Queue* q = initialize(capacity);

    // enqueue 테스트
    for (int i = 1; i <= capacity; i++) {
        enqueue(q, i * 10);
    }
    printf("우선 enqueue 테스트 : ");
    print_queue(q);
    printf("\n-----------------------------------------\n");

    // dequeue 테스트
    for (int i = 1; i <= 5; i++) {
        dequeue(q);
    }
    printf("enqueue하고 나서 원소 몇 개만 dequeue 테스트 : ");
    print_queue(q);
    printf("\n-----------------------------------------\n");

    // 빼고 난 후의 enqueue 테스트
    for (int i = 1; i <= 3; i++) {
        enqueue(q, i * 10);
    }
    printf("dequeue 이후 다시 enqueue 테스트 : ");
    print_queue(q);
    printf("\n-----------------------------------------\n");

    free(q->array);
    free(q);

    return 0;
}