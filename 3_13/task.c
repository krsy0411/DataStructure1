#include <stdio.h>
#define SIZE 3

// 가로 합 계산 함수
void sum_horizontal(int matrix[SIZE][SIZE], int result[]) {
    for(int i=0; i<SIZE; i++) {
        int sum = 0;
        for(int j=0; j<SIZE; j++) {
            sum += matrix[i][j];
        }

        result[i] = sum;
    }
}

// 세로 합 계산 함수
void sum_vertical(int matrix[SIZE][SIZE], int result[]) {
    for (int i = 0; i < SIZE; i++) {
        int sum = 0;
        for (int j = 0; j < SIZE; j++) {
            sum += matrix[i][j];
        }
        result[i] = sum;
    }
}

// 2차원 배열 전체 합 연산 함수
int sum_all(int matrix[SIZE][SIZE]) {
    int sum = 0;
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            sum += matrix[i][j];
        }
    }

    return sum;
}

int main(void) {
    int matrix[SIZE][SIZE] = {1,2,3,4,5,6,7,8,9};
    int horizontal_sum[SIZE];
    int vertical_sum[SIZE];
    int total = 0;
    
    // 가로,세로 합 계산 수행
    sum_horizontal(matrix, horizontal_sum);
    sum_vertical(matrix, vertical_sum);
    // 전체 합 계산 수행
    total = sum_all(matrix);

    // 가로 합 출력
    printf("가로 합: ");
    for (int i = 0; i < 3; i++) {
        printf("%d행의 합: %d\t", i+1, horizontal_sum[i]);
    }
    printf("\n");

    // 세로 합 출력
    printf("세로 합: ");
    for (int j = 0; j < 3; j++) {
        printf("%d열의 합: %d\t", j+1, vertical_sum[j]);
    }
    printf("\n");

    // 전체 합 출력
    printf("전체 합: %d\n", total);

    return 0;
}