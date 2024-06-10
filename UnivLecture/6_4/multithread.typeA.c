#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TIME 3600

typedef struct Task {
    int duration; // 각 task가 걸리는 시간
    struct Task* next;
} Task;

typedef struct Queue {
    Task* front;
    Task* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void enQueue(Queue* q, int time) {
    // 새로운 task 생성
    Task* newTask = (Task *)malloc(sizeof(Task));
    newTask->duration = time;
    newTask->next = NULL;

    if(isEmpty(q)) {
        q->front = newTask;
    } else {
        q->rear->next = newTask;
    }
    q->rear = newTask;
    // printf("Enqueued: %d\n", time);
}

int deQueue(Queue* q) {
    if(isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    // 큐에서 front 노드를 다음 노드로 변경
    Task* tempTask = q->front;
    q->front = q->front->next;
    int duration = tempTask->duration;
    free(tempTask); // deQueue된 업무의 메모리 할당 해제

    return duration;
}

// main함수의 taskCount(배열)을 인자로 받습니다.
void printCount(int* array) {
    printf("- Task A : %d\n", array[0]);
    printf("- Task B : %d\n", array[1]);
    printf("- Task C : %d\n", array[2]);
}

int main() {
    int totalTime = TIME; 
    int term = 15; // 작업이 추가되는 시간
    // A,B,C 작업들의 수행시간, 수행횟수
    int tasks[] = { 12, 15, 24 }; int taskCount[] = { 0, 0, 0 }; 
    int currentTaskDuration = 0;
    // 큐 자료구조 생성
    Queue queue; 
    initQueue(&queue);

    // 난수 생성기를 초기화하는 시드 설정
    srand(time(NULL));  
    // 15초 마다 1개의 작업 입력받고, 만약 15초 안에 처리가 안되면, 큐에 담아두기
    while(totalTime > 0) {  
        int index = rand() % 3;
        int randomTaskTime = tasks[index];
        taskCount[index] += 1; // 호출횟수 증가
        
        if(currentTaskDuration > 0) {
            currentTaskDuration -= term;
            enQueue(&queue, randomTaskTime);
        } else {
            if(!isEmpty(&queue)) {
                currentTaskDuration = deQueue(&queue);
            }
        }

        // 15초씩 제거
        totalTime -= term;
    }
    printCount(taskCount);
    return 0;
}