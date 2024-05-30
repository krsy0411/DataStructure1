#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep함수
#include <time.h>

typedef struct Queue {
    int *array; // 큐 배열의 포인터 
    int front; // 프론트 index
    int rear; // 마지막 index
    int capacity; // 큐의 현재 최대 크기
    int size; // 현재 큐에서 사용중인 크기(<= capacity)
} Queue;

// 큐 초기화 함수
Queue* initialize(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = capacity - 1;
    queue->size = 0;
    // task들을 담아둘 데이터 생성
    queue->array = (int *)malloc(capacity * sizeof(int));
    return queue;
}

// 큐가 비어있는지 확인하는 함수
int isEmpty(Queue* q) {
    return q->size == 0;
}

// 큐가 가득 찼는지 확인하는 함수
int isFull(Queue* q) {
    return q->size == q->capacity;
}

void printQueue(Queue* q) {
    printf("현재 큐 상태 : ");
    for(int i=0; i<q->size; i++) {
        printf("%d ", q->array[i]);
    }
    printf("\n");
}

void freeQueue(Queue* q) {
    free(q->array);
    free(q);
}

void enQueue(Queue* q, int clockOfTask) {
    if(isFull(q)) {
        printf("큐가 가득찬 상태. enqueue 불가능\n");
        return;
    }

    q->rear = (q->rear+1) % q->capacity;
    q->array[q->rear] = clockOfTask;
    q->size = q->size+1;
}

int deQueue(Queue* q) {
    if(isEmpty(q)) {
        printf("큐가 빈 상태. dequeue 불가능\n");
        return 0;
    }

    int clock = q->array[q->front];
    q->front = (q->front+1) % q->capacity;
    q->size = q->size-1;

    return clock;
}


// 프로세스가 10초 간격으로 task를 생성 : 6개
// task는 1~20초 사이의 랜덤 제너레이터가 필요 : 1~20초 사이의 clock
// cpu의 성능은 1 clock per second : 초당 처리 가능한 clock이 1개

// 만약 task가 10clock? -> cpu가 해당 업무를 처리하는데에 10초가 소요(task 완료)
// 프로세스가 10초마다 또 다른 task들을 계속 생성
// 문제는, task가 10초 안에 처리가 아직 안 되었는데 새로운 task가 생성됨 -> 바로 실행할 수 없음 -> cpu 스케쥴링 필요
// cpu에 큐를 만들어서 처리가 되는대로 순차적으로 처리하도록 구현할 것
// 전체 수행되는데 걸리는 시간을 출력해보세요

// 1. queue 자료구조 필요
// 2. sleep(1000) 필요 -> 1초 단위로 처리가 다 되면 다른 업무 수행
int main() {
    int t = 0; // 총 걸린 시간 측정을 위한 변수(time)
    int capa = 6; // 큐의 크기(요구 업무 개수)
    Queue* queue = initialize(capa);

    srand(time(NULL));
    // 큐에 task의 클록수들 할당
    for(int i=0; i<capa; i++) {
        enQueue(queue, ((rand() % 20) + 1));
    }
    printQueue(queue);

    // dequeue 시작
    int currentTaskClock = deQueue(queue);
    while(1) {
        sleep(1); // 딜레이를 만들기 위한 1초 sleep
        currentTaskClock--;
        t++;
        printf("현재 time : %d\n", t);

        // 현재 업무의 클록수가 0이면, 다시 dequeue
        if(currentTaskClock == 0) {
            printf("task가 완료되었습니다. 다시 업무를 할당받습니다.\n");
            currentTaskClock = deQueue(queue);
        }

        // 큐가 비었고, 현재 업무의 클록수가 0이면, 이제 업무처리 끝
        if(isEmpty(queue) && (currentTaskClock == 0)) {
            break;
        }
    }

    printf("--------------------------------\n");
    printf("걸린시간은 다음과 같습니다 : %d초\n", t);

    freeQueue(queue);
    return 0;
}