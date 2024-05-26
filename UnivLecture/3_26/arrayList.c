#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
    element *array; // 배열 포인터 정의
    int size; // 데이터 크기(개수)
    int capacity; // 크기(용량)
} ArrayListType;

// 프린트 함수
void print_list(ArrayListType *list) {
    // size값을 토대로 반복 출력
    for(int i=0; i<list->size; i++) {
        printf("%d  ", list->array[i]);
    }
    printf("\n");
} 
int is_full(ArrayListType *list) {
    if(list->size >= list->capacity) {
        return 1;
    }
    return 0;
}
int is_empty(ArrayListType *list) {
    if(list->size == 0) {
        return 1;
    }
    return 0;
}

// 초기화 함수
void init(ArrayListType *list) {
    printf("배열 리스트의 크기를 입력해주세요 >> ");
    scanf("%d", &list->capacity);
    list->size = 0; // 리스트 항목 개수 초기화
    list->array = (element *)malloc(sizeof(element) * list->capacity); // 입력받은 값 토대로 배열 동적할당
}

// 첫 인덱스에 데이터를 삽입하는 함수
void insert_first(ArrayListType *list, element value) {
    if(is_full(list)) {
        printf("리스트가 가득 찼습니다\n");
        return;
    }
    list->size++; // 개수 증가
    for(int i = list->size - 1; i > 0; i--) {
        // 원소들 뒤로 미루기
        list->array[i] = list->array[i - 1];
    }

    list->array[0] = value; // 0번째 인덱스에 값 넣어주기
}

// 마지막에 데이터를 넣어주는 함수
void insert_last(ArrayListType *list, element value) {
    if(is_full(list)) {
        printf("리스트가 가득 찼습니다\n");
        return;
    }
    list->array[list->size++] = value; // 값 넣어주기
    list->size++; // 개수 증가
}

// 첫 인덱스의 데이터를 지우는 함수
void delete_first(ArrayListType *list) {
    if(is_empty(list)) {
        printf("리스트가 비어있습니다\n");
        return;
    }
    // 원소들을 당겨줍니다
    for(int i=0; i<list->size-1; i++) {
        list->array[i] = list->array[i+1];
    }

    list->size--; // 개수 감소
}

// 마지막 요소 지우는 함수
void delete_last(ArrayListType *list) {
    if(is_empty(list)) {
        printf("리스트가 비어있습니다\n");
        return;
    }

    list->size--; // 개수 감소
}

// 넣고 싶은 자리에 데이터를 넣어주는 함수
void insert(ArrayListType *list, element value, int index_position) {
    if (index_position < 0 || index_position > list->size) { // 유효하지 않은 인덱스 위치인 경우
        printf("유효하지 않은 인덱스 위치입니다\n");
        return;
    }
    if(is_full(list)) { // 리스트가 가득 찬 경우
        printf("리스트가 가득 찼습니다\n");
        return;
    }
    
    // 인덱스 위치에 데이터를 삽입하기 위해 기존의 데이터를 한 칸씩 뒤로 이동시킵니다.
    for (int i = list->size; i > index_position; i--) {
        list->array[i] = list->array[i - 1];
    }
    // 새로운 데이터를 인덱스 위치에 삽입합니다.
    list->array[index_position] = value;
    list->size++; // 데이터 크기 증가
}

// 특정 위치의 데이터를 삭제하는 함수
void delete(ArrayListType *list, int index_position) {
    if (index_position < 0 || index_position >= list->size) { // 유효하지 않은 인덱스 위치인 경우
        printf("유효하지 않은 인덱스 위치입니다\n");
        return;
    }
    if (is_empty(list)) { // 리스트가 비어 있는 경우
        printf("리스트가 비어있습니다\n");
        return;
    }

    // 삭제하려는 데이터의 인덱스 위치 이후의 데이터를 한 칸씩 앞으로 당겨줍니다.
    for (int i = index_position; i < list->size - 1; i++) {
        list->array[i] = list->array[i + 1];
    }
    list->size--; // 데이터 크기 감소
}

int main(void) {
    ArrayListType list; // 배열 리스트 생성
    init(&list); // 초기화

    // 요소 추가
    insert_last(&list, 10);
    insert_last(&list, 20);
    insert_last(&list, 30);
    insert(&list, 50, 2);
    insert_first(&list, 90);
    // 리스트 출력
    printf("리스트 출력: ");
    print_list(&list);

    // 요소 삭제
    delete_last(&list);
    delete(&list, 2);
    delete_first(&list);
    // 리스트 출력
    printf("요소 삭제 후 리스트 출력: ");
    print_list(&list);

    // 동적 메모리 할당 해제
    free(list.array);
    return 0;
}