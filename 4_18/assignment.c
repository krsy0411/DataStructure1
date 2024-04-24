#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 50000
#define ITERATIONSIZE 1000

typedef struct ArrayList {
    int array[SIZE]; // 배열리스트를 저장할 배열
    int size; // 현재 배열 리스트에 저장된 요소 개수
} ArrayList;

typedef struct SLL_Node {
    int data; // 데이터 필드
    struct SLL_Node* next; // 다음 노드 가리키는 포인터
} SLL_Node;
typedef struct SinglyLinkedList {
    SLL_Node* head;
    int size;
} SinglyLinkedList;

typedef struct DLL_Node {
    int data;
    struct DLL_Node* next;
    struct DLL_Node* prev;
} DLL_Node;
typedef struct DoublyLinkedList {
    DLL_Node* head;
    DLL_Node* tail;
    int size;
} DoublyLinkedList;

// arrayList : insert_first
void ArrayList_Insert_first(ArrayList *list) {
    for(int i =0; i<SIZE; i++) {
        // 우선 요소를 오른쪽으로 shift
        for(int j = list->size; j>0; j--) {
            list->array[j] = list->array[j-1];
        }
        // 새로 들어갈 값은 맨 앞 인덱스에 추가하고, 사이즈++
        list->array[i] = i;
        list->size++;
    }
}
// arrayList : insert_last
void ArrayList_Insert_last(ArrayList *list) {
    if(list->size >= SIZE) {
        printf("배열리스트가 가득 찬 상태\n");
        return;
    }

    for(int i=0; i<SIZE; i++) {
        list->array[list->size++] = i;
    }
}

// LinkedList : insert_first
void SinglyLinkedList_Insert_First(SinglyLinkedList** list) {
    for(int i=0; i<SIZE; i++) {
        SLL_Node* newNode = (SLL_Node*)malloc(sizeof(SLL_Node));
        if (newNode == NULL) {
            printf("메모리 할당 실패\n");
            return;
        }
        newNode->data = i;

        // 새 노드를 리스트의 첫 번째 노드로 설정
        newNode->next = (*list)->head;
        (*list)->head = newNode;

        // 리스트 사이즈 증가
        (*list)->size++;
    }
}
// LinkedList : insert_last
void SinglyLinkedList_Insert_Last(SinglyLinkedList** list) {
    for(int i=0; i<SIZE; i++) {
        SLL_Node* newNode = (SLL_Node *)malloc(sizeof(SLL_Node));
        newNode->data = i; newNode->next = NULL;

        if((*list)->head == NULL) {
            (*list)->head = newNode;
        } else {
            SLL_Node* temp = (*list)->head;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        (*list)->size++;
    }
}

void DoublyLinkedList_Insert_First(DoublyLinkedList** list) {
    for(int i=0; i<SIZE; i++) {
        DLL_Node* newNode = (DLL_Node *)malloc(sizeof(DLL_Node));
        newNode->data = i; newNode->next = (*list)->head; newNode->prev = NULL;

        if((*list)->head != NULL) {
            (*list)->head->prev = newNode;
        }
        (*list)->head = newNode;

        if((*list)->tail == NULL) {
            (*list)->tail = newNode;
        }

        (*list)->size++;
    }
}

void DoublyLinkedList_Insert_Last(DoublyLinkedList** list) {
    for(int i=0; i<SIZE; i++) {
        DLL_Node* newNode = (DLL_Node *)malloc(sizeof(DLL_Node));
        newNode->data = i; newNode->next = NULL; newNode->prev = NULL;

        if((*list)->head == NULL) {
            (*list)->head = newNode;
            (*list)->tail = newNode;
        } else {
            newNode->prev = (*list)->tail;
            (*list)->tail->next = newNode;
            (*list)->tail = newNode;
        }

        (*list)->size++;
    }
}

int ArrayList_Get_Sum_Random(ArrayList *list) {
    int sum = 0;
    for(int i = 0; i < ITERATIONSIZE; i++) {
        int index = rand() % list->size; // 0과 list->size - 1 사이의 랜덤한 인덱스 생성
        sum += list->array[index];
    }
    return sum;
}

// SinglyLinkedList에서 랜덤하게 값을 골라 sum을 반환하는 함수
int SinglyLinkedList_Get_Sum_Random(SinglyLinkedList* list) {
    int sum = 0;
    for(int i = 0; i < ITERATIONSIZE; i++) {
        int index = rand() % list->size; // 0과 list->size - 1 사이의 랜덤한 인덱스 생성
        SLL_Node* current = list->head;
        for(int j = 0; j < index; j++) {
            current = current->next;
        }
        sum += current->data;
    }
    return sum;
}

// DoublyLinkedList에서 랜덤하게 값을 골라 sum을 반환하는 함수
int DoublyLinkedList_Get_Sum_Random(DoublyLinkedList* list) {
    int sum = 0;
    for(int i = 0; i < ITERATIONSIZE; i++) {
        int index = rand() % list->size; // 0과 list->size - 1 사이의 랜덤한 인덱스 생성
        DLL_Node* current;
        if (index < list->size / 2) {
            current = list->head;
            for(int j = 0; j < index; j++) {
                current = current->next;
            }
        } else {
            current = list->tail;
            for(int j = list->size - 1; j > index; j--) {
                current = current->prev;
            }
        }
        sum += current->data;
    }
    return sum;
}

// ArrayList에서 랜덤한 인덱스의 요소를 삭제하는 함수
void delete_arrayList(ArrayList *list) {
    for (int i = 0; i < ITERATIONSIZE; i++) {
        if (list->size == 0) {
            printf("배열리스트가 비어 있습니다.\n");
            return;
        }
        int index = rand() % list->size; // 0과 list->size - 1 사이의 랜덤한 인덱스 생성
        // 삭제할 요소 뒤의 요소들을 앞으로 이동하여 덮어씌움
        for (int j = index; j < list->size - 1; j++) {
            list->array[j] = list->array[j + 1];
        }
        list->size--; // 사이즈 감소
    }
}

// SinglyLinkedList에서 랜덤한 인덱스의 요소를 삭제하는 함수
void delete_singlyLinkedList(SinglyLinkedList* list) {
    for (int i = 0; i < ITERATIONSIZE; i++) {
        if (list->size == 0) {
            printf("싱글링크드리스트가 비어 있습니다.\n");
            return;
        }
        int index = rand() % list->size; // 0과 list->size - 1 사이의 랜덤한 인덱스 생성
        SLL_Node* current = list->head;
        SLL_Node* previous = NULL;
        // 삭제할 요소까지 이동
        for (int j = 0; j < index; j++) {
            previous = current;
            current = current->next;
        }
        if (previous == NULL) {
            // 삭제할 요소가 첫 번째 노드인 경우
            list->head = current->next;
        } else {
            // 이전 노드의 다음 포인터를 삭제할 요소의 다음 포인터로 설정
            previous->next = current->next;
        }
        free(current); // 노드 메모리 해제
        list->size--; // 사이즈 감소
    }
}

// DoublyLinkedList에서 랜덤한 인덱스의 요소를 삭제하는 함수
void delete_DoublyLinkedList(DoublyLinkedList* list) {
    for (int i = 0; i < ITERATIONSIZE; i++) {
        if (list->size == 0) {
            printf("더블링크드리스트가 비어 있습니다.\n");
            return;
        }
        int index = rand() % list->size; // 0과 list->size - 1 사이의 랜덤한 인덱스 생성
        DLL_Node* current = list->head;
        // 삭제할 요소까지 이동
        for (int j = 0; j < index; j++) {
            current = current->next;
        }
        if (current->prev == NULL) {
            // 삭제할 요소가 첫 번째 노드인 경우
            list->head = current->next;
            if (current->next != NULL) {
                current->next->prev = NULL;
            } else {
                // 리스트에 노드가 한 개인 경우
                list->tail = NULL;
            }
        } else if (current->next == NULL) {
            // 삭제할 요소가 마지막 노드인 경우
            list->tail = current->prev;
            current->prev->next = NULL;
        } else {
            // 삭제할 요소가 중간에 있는 경우
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        free(current); // 노드 메모리 해제
        list->size--; // 사이즈 감소
    }
}

int main(void) {
    clock_t start, end;
    srand((unsigned int) time(NULL));

    // 50000만개의 원소를 가질 수 있는 배열 리스트 생성
    ArrayList array; array.size = 0;
    SinglyLinkedList* sll_list = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
    sll_list->head = NULL; sll_list->size = 0;
    DoublyLinkedList* dll_list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
    dll_list->head = NULL; dll_list->tail = NULL; dll_list->size = 0;

    printf("\n데이터 크기 : 5만\n");
    printf("---Array vs SinglyLinkedList vs DoublyLinkedList---\n");
    printf("\n1번: 삽입\n");

    printf("\n\t배열리스트\n");

    printf("ArrayList : insert_last : ");
    start = clock(); // 수행시간 측정 시작
    ArrayList_Insert_last(&array);
    end = clock(); // 수행시간 측정 종료
    printf("%0.4f\n", (double)end-start / CLOCKS_PER_SEC);

    printf("ArrayList : insert_first : ");
    start = clock(); // 수행시간 측정 시작
    ArrayList_Insert_first(&array);
    end = clock(); // 수행시간 측정 종료
    printf("%0.4f\n", (double)end-start / CLOCKS_PER_SEC);

    printf("\n\t싱글링크드리스트\n");

    printf("SinglyLinkedList : insert_last : ");
    start = clock(); // 수행시간 측정 시작
    SinglyLinkedList_Insert_Last(&sll_list);
    end = clock(); // 수행시간 측정 종료
    printf("%0.4f\n", (double)end-start / CLOCKS_PER_SEC);

    printf("SinglyLinkedList : insert_first : ");
    start = clock(); // 수행시간 측정 시작
    SinglyLinkedList_Insert_First(&sll_list);
    end = clock(); // 수행시간 측정 종료
    printf("%0.4f\n", (double)end-start / CLOCKS_PER_SEC);

    printf("\n\t더블링크드리스트\n");

    printf("DoublyLinkedList : insert_last : ");
    start = clock(); // 수행시간 측정 시작
    DoublyLinkedList_Insert_Last(&dll_list);
    end = clock(); // 수행시간 측정 종료
    printf("%0.4f\n", (double)end-start / CLOCKS_PER_SEC);

    printf("DoublyLinkedList : insert_first : ");
    start = clock(); // 수행시간 측정 시작
    DoublyLinkedList_Insert_First(&dll_list);
    end = clock(); // 수행시간 측정 종료
    printf("%0.4f\n", (double)end-start / CLOCKS_PER_SEC);

    printf("\n2번: 읽기\n");
    printf("\n\t배열리스트\n");
    start = clock(); // 수행시간 측정 시작
    printf("ArrayList Sum Random: %d\n", ArrayList_Get_Sum_Random(&array));
    end = clock(); // 수행시간 측정 종료
    printf("time : %0.4f\n", (double)end-start / CLOCKS_PER_SEC);

    printf("\n\t싱글링크드리스트\n");
    start = clock(); // 수행시간 측정 시작
    printf("SinglyLinkedList Sum Random: %d\n", SinglyLinkedList_Get_Sum_Random(sll_list));
    end = clock(); // 수행시간 측정 종료
    printf("time : %0.4f\n", (double)end-start / CLOCKS_PER_SEC);

    printf("\n\t더블링크드리스트\n");
    start = clock(); // 수행시간 측정 시작
    printf("DoublyLinkedList Sum Random: %d\n", DoublyLinkedList_Get_Sum_Random(dll_list));
    end = clock(); // 수행시간 측정 종료
    printf("time : %0.4f\n", (double)end-start / CLOCKS_PER_SEC);

    printf("\n3번: 삭제\n");
    printf("\n\t배열리스트\n");
    start = clock(); // 수행시간 측정 시작
    delete_arrayList(&array);
    end = clock(); // 수행시간 측정 종료
    printf("time : %0.4f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("\n\t싱글링크드리스트\n");
    start = clock(); // 수행시간 측정 시작
    delete_singlyLinkedList(sll_list);
    end = clock(); // 수행시간 측정 종료
    printf("time : %0.4f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("\n\t더블링크드리스트\n");
    start = clock(); // 수행시간 측정 시작
    delete_DoublyLinkedList(dll_list);
    end = clock(); // 수행시간 측정 종료
    printf("time : %0.4f\n", (double)(end - start) / CLOCKS_PER_SEC);


    return 0;
}