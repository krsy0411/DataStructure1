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

int main(void) {
    // 일단 메모리 동적할당 및 초기화 작업 수행
    ListNode* head = (ListNode *)malloc(sizeof(ListNode));
    head->data = 10;
    head->link = NULL;

    // 값 삽입
    for(int i=1; i<6; i++) {
        insert_first(head, i*10);
    }
    // 끝에 삽입
    insert_last(head, 90);
    // 출력
    print_list(head);

    free(head);
    return 0;
}