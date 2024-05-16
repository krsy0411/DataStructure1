#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int capacity; // 큐의 크기
    int front;    // 프론트 인덱스
    int rear;     // 리어 인덱스
    int size;     // 현재 큐의 원소 개수
    int *array;   // 큐 배열의 주소
} Queue;

// 큐 초기화 함수
Queue* initialize(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = capacity - 1;
    queue->size = 0;
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

// 큐가 비어있는지 확인하는 함수
int is_empty(Queue* q) {
    return q->size == 0;
}

// 큐가 가득 찼는지 확인하는 함수
int is_full(Queue* q) {
    return q->size == q->capacity;
}

// 큐에 원소를 추가하는 함수
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

// 큐에서 원소를 제거하는 함수
void dequeue(Queue* q) {
    if (is_empty(q)) {
        printf("큐가 비어 있습니다.\n");
        return;
    }
    printf("빠진 값: %d\n", q->array[q->front]);
    q->front = (q->front + 1) % q->capacity;
    q->size--;
}

// 큐의 내용을 출력하는 함수
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

// 배열이 정방향인지 역방향인지 확인하는 함수
int is_reverse_order(Queue* q) {
    if (q->size < 2) {
        return 0; // 원소가 하나 이하일 경우 정방향으로 간주
    }

    int first = q->array[q->front];
    int last = q->array[q->rear];
    
    // 첫번째 원소보다 마지막 원소가 작으면 역방향
    return first > last;
}

// 역방향 배열을 정방향으로 재배열하는 함수
void reverse_to_forward(Queue* q) {
    if (!is_reverse_order(q)) {
        return; // 이미 정방향인 경우
    }

    int* temp_array = (int*)malloc(q->size * sizeof(int));
    int index = 0;

    // 큐의 원소를 순서대로 temp_array에 저장
    for (int i = 0; i < q->size; i++) {
        int current_index = (q->front + i) % q->capacity;
        temp_array[index++] = q->array[current_index];
    }

    // temp_array를 오름차순으로 정렬
    for (int i = 0; i < q->size - 1; i++) {
        for (int j = 0; j < q->size - i - 1; j++) {
            if (temp_array[j] > temp_array[j + 1]) {
                int temp = temp_array[j];
                temp_array[j] = temp_array[j + 1];
                temp_array[j + 1] = temp;
            }
        }
    }

    // 정렬된 temp_array를 큐에 저장
    for (int i = 0; i < q->size; i++) {
        q->array[(q->front + i) % q->capacity] = temp_array[i];
    }

    free(temp_array);
}

int main(void) {
    int capacity;
    printf("큐의 사이즈를 입력하세요: ");
    scanf("%d", &capacity);

    Queue* q = initialize(capacity);

    // enqueue 테스트
    enqueue(q, 50);
    enqueue(q, 40);
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    printf("우선 enqueue 테스트 : ");
    print_queue(q);

    printf("\n-----------------------------------------\n");

    printf("정방향이면, 그대로 출력 | 역방향이면, 정렬 후 출력\n");
    if (is_reverse_order(q)) {
        printf("[역방향]\n");
        reverse_to_forward(q);
    } else {
        printf("[정방향]\n");
    }

    printf("정렬 후 : ");
    print_queue(q);

    printf("\n-----------------------------------------\n");

    free(q->array);
    free(q);

    return 0;
}
