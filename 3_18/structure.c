#include <stdio.h>
#include <stdlib.h>

// 구조체 선언
struct Student {
    char name[3];
    int age;
    float score;
};

float get_avg(struct Student *students) {
    float result = 0;
    for(int i=0; i<3; i++) {
        // 주소값 통해서 스코어 뽑아내서 합산
        result += (students + i)->score;
    }
    // 인원수만큼 나눠줘서 값 얻기
    result /= 3;

    return result;
}

int main(void) {
    // 구조체 배열 생성 후 메모리 동적 할당
    struct Student *students = (struct Student*)malloc(sizeof(struct Student) * 3);
    // 평균 성적 초기화
    float avg_score = 0;
    // 메모리 할당
    for(int i=0; i<3; i++) {
        // 각 학생 정보 동적 할당
        scanf("%s %d %f", students[i].name, &students[i].age, &students[i].score);
    }

    // 평균 점수 출력
    printf("평균 성적 : %.2f\n", get_avg(students));
    // 동적 메모리 할당 해제
    free(students);
    return 0;
}