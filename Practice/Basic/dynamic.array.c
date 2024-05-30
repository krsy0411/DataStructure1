#include <stdio.h>
#include <stdlib.h>

// 다이나믹 배열이란 : 크기를 동적으로 조정할 수 있는 배열
// 동적으로 크기를 조정 가능하다면, 리스트와 차이점이 뭔가요?
// 1. 필요한 경우 새로운 더 큰 배열을 할당하고 기존 데이터를 복사 | 각 요소(노드)들이 독립적으로 메모리에 할당되는건 아님.
// 2. 인덱스를 사용하여 O(1) 시간 복잡도로 요소에 접근 가능
// 3. 배열의 중간에서 요소를 삽입하거나 삭제하면, 해당 위치 이후의 모든 요소를 이동시켜야 하기 때문에 평균 O(n) 시간이 소요
// 4. 요소들이 연속적인 메모리 공간에 저장되기 때문에 메모리 사용이 더 효율적. 하지만 배열 크기를 변경할 때는 새로운 배열을 할당하고 데이터를 복사해야 하므로 오버헤드가 발생

typedef struct DynamicArray {
    int *array; // 배열
    int size; // 배열의 킈기
    int index; // 현재 인덱스
} DynamicArray;

void freeDynamicArray(DynamicArray *da) {
    free(da->array);
    da->array = NULL;
    da->index = 0;
    da->size = 0;
}

void initArray(DynamicArray *da, int size) {
    da->array = (int *)malloc(sizeof(int) * size);
    da->index = 0;
    da->size = size;
}

void insertArray(DynamicArray *da, int data) {
    // 현재 사용된 인덱스가 사이즈와 동일한 경우
    if(da->index == da->size) {
        // 배열 사이즈를 동적으로 현재의 2배로 늘리기
        da->size *= 2;
        da->array = (int *)realloc(da->array, da->size * sizeof(int));
    }
    da->array[da->index++] = data;
}

// 특정 인덱스의 원소를 삭제
void deleteElement(DynamicArray *da, int index) {
    if(index < 0 || index >= da->size) {
        printf("삭제할 수 없습니다.");
        return;
    }

    // 삭제할 인덱스부터 그 이후 인덱스들의 원소를 앞으로 당겨줍니다.
    for(int i=index; i<da->size-1; i++) {
        da->array[i] = da->array[i+1];
    }
    // 다이나믹 배열의 사이즈를 줄여줍니다.
    da->size--;
}

void printDynamicArray(DynamicArray* da) {
    for(int i=0; i<da->size; i++) {
        printf("%d ", da->array[i]);
    }
    printf("\n");
}

int main() {    
    DynamicArray* da = (DynamicArray *)malloc(sizeof(DynamicArray));
    int size;
    
    printf("배열의 초기 사이즈를 입력해주세요 >> "); scanf("%d", &size);
    initArray(da, size);

    for(int i=1; i<=size; i++) {
        insertArray(da, i*10);
    }
    printf("\n-------- 삭제 이전 --------\n");
    printDynamicArray(da);
    deleteElement(da, 2);
    printf("\n-------- 삭제 이후 --------\n");
    printDynamicArray(da);

    freeDynamicArray(da);
    return 0;   
}