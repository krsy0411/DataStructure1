#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIMULATION_COUNT 1000
#define WORKING_TIME 3600 // 1 hour in seconds
#define INTERVAL 15       // 15 seconds interval for new tasks

typedef enum {
    A = 12,
    B = 15,
    C = 24
} Task;

Task generate_random_task() {
    int rand_value = rand() % 3;
    if (rand_value == 0) return A;
    if (rand_value == 1) return B;
    return C;
}

int simulate_cpu(int queue_length) {
    int time = 0;
    int queue[queue_length];
    int queue_start = 0, queue_end = 0, queue_size = 0;
    int task_time_left = 0;

    while (time < WORKING_TIME) {
        // 15초마다 새 Task 생성
        if (time % INTERVAL == 0) {
            Task new_task = generate_random_task();
            // 큐 길이보다 큐 사이즈가 작으면 큐에 Task 넣기
            if (queue_size < queue_length) {
                queue[queue_end] = new_task;
                queue_end = (queue_end + 1) % queue_length;
                queue_size++;
            } else {
                return 0; // 작업 드롭, 실패
            }
        }

        // 현재 작업이 없으면 큐에서 새 작업 가져오기
        if (task_time_left == 0 && queue_size > 0) {
            task_time_left = queue[queue_start];
            queue_start = (queue_start + 1) % queue_length;
            queue_size--;
        }

        // 작업이 진행 중이면 남은 시간 감소
        if (task_time_left > 0) {
            task_time_left--;
        }

        // 시간이 흐름
        time++;
    }

    // 시뮬레이션 종료 시 대기 큐와 남은 작업 확인
    return (queue_size == 0 && task_time_left == 0); // 작업이 모두 처리되었으면 성공
}

int main() {
    srand(time(NULL));
    int success_count;
    int queue_length = 1;

    while (1) {
        success_count = 0;
        for (int i = 0; i < SIMULATION_COUNT; i++) {
            if (simulate_cpu(queue_length)) {
                success_count++;
            }
        }

        float success_rate = (float)success_count / SIMULATION_COUNT * 100;
        printf("Queue Length: %d, Success Rate: %.2f%%\n", queue_length, success_rate);

        if (success_rate >= 90.0) {
            printf("Minimum queue length with at least 90%% success rate: %d\n", queue_length);
            break;
        }

        queue_length++;
    }

    return 0;
}
