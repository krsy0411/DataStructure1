#include <stdio.h>
#include <stdlib.h>

// 구조체 정의
typedef int element;
typedef struct ListNode { 
    element data; // 해당 노드의 원소값
    struct ListNode *link; // 다음 노드 주소값을 가리키는 포인터
} ListNode;

void print_list(ListNode *head) {
    // 다음 노드가 없을때까지 반복
    for(ListNode *p = head; p != NULL; p = p->link) {
        printf("%d -> ", p->data);
    }
    printf("NULL \n");
}

void insert_first(ListNode *head, int value) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head->link; // 현재 헤드 포인터가 지니고 있는 주소값 복사
    head->link = p; // 삽입할 노드의 주소값을 헤드 포인터에게 전달
}

void insert_last(ListNode *head, int value) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = NULL;
    // 리스트가 비어 있는 경우
    if (head->link == NULL) {
        head->link = p;
        return;
    }

    // 리스트가 비어 있지 않은 경우
    ListNode *node_ptr = head;
    while (node_ptr->link != NULL) {
        node_ptr = node_ptr->link;
    }
    node_ptr->link = p;
}

void delete_first(ListNode *head) {
    ListNode *removed = head->link;
    if(head->link == NULL) {
        printf("빈 리스트입니다.\n");
    }
    // 헤드가 두 번째 노드를 가리키도록 조정
    head->link = removed->link;
    free(removed);
}

void delete_last(ListNode *head) {
    ListNode *removed = head;
    ListNode *prev;

    if(head->link == NULL) {
        printf("빈 리스트입니다.\n");
    }
    
    while(removed->link != NULL) {
        prev = removed;
        removed = removed->link;
    }

    if(prev == NULL) {
        head->link = NULL;
    } else {
        // 이전 노드가 마지막 노드순서가 될 수 있도록 링크값을 NULL로 설정
        prev->link = NULL;
    }

    // 메모리 할당 해제
    free(removed);
}

void search(ListNode *head, int value) {
    ListNode *p = head;
    int located_index = 0;

    while(p != NULL) {
        ++located_index;
        if(p->data == value) {
            printf("%d번째에 위치하고 있습니다.\n", located_index+1);
            break;
        }
        // 다음 노드로 이동
        p = p->link;
    }
}

int main(void) {
    // 일단 메모리 동적할당 및 초기화 작업 수행
    ListNode* head = (ListNode *)malloc(sizeof(ListNode));
    head->data = 10;
    head->link = NULL;

    // 값 삽입
    for(int i=2; i<6; i++) {
        insert_first(head, i*10);
    }
    // 끝에 삽입
    insert_last(head, 60);
    // 삭제
    delete_last(head);
    delete_first(head);
    // 출력
    print_list(head);
    // 탐색
    search(head, 10);

    free(head);
    return 0;
}