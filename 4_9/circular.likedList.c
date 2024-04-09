#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

void print_list(ListNode* head)
{
    ListNode* p;

    if (head == NULL) return;
    p = head->link;
    do {
        printf("%d -> ", p->data);
        p = p->link;
    } while ( p != head );
    printf("%d -> NULL", p->data); // 마지막 노드
}

ListNode* insert_first(ListNode* head, element data)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = data;
    if (head == NULL) {
        head =  node;
        node->link = head;
    }
    else {
        node->link =  head->link;
        head->link =  node;
    }
    return head;
}

ListNode* insert_last(ListNode* head, element data)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = data;
    if (head == NULL) {
        head =  node ;
        node->link = head;
    }
    else {
        node->link =  head->link;
        head->link =  node;
        head =  node; // 헤드를 새로운 마지막 노드로 업데이트
    }
    return head;    // 변경된 헤드 포인터 반환
}

void delete_first(ListNode *head) {
    // 빈 리스트인 경우
    if (head == NULL || head->link == head) {
        printf("리스트가 비어있습니다.\n");
        return;
    }

    ListNode *temp = head->link; // 삭제할 노드 임시 저장
    head->link = temp->link; // 헤드가 다음 노드를 가리키도록 설정
    free(temp); // 삭제할 노드의 메모리 해제
}

void delete_last(ListNode *head) {
    // 빈 리스트인 경우
    if (head == NULL || head->link == head) {
        printf("리스트가 비어있습니다.\n");
        return;
    }

    ListNode *current = head;
    ListNode *prev = NULL;

    // 마지막 노드와 그 이전 노드를 찾음
    while (current->link != head) {
        prev = current;
        current = current->link;
    }

    prev->link = head; // 이전 노드의 링크를 헤드로 설정하여 연결
    free(current); // 삭제할 노드의 메모리 해제
}

int main(void) {
    ListNode *head = NULL;
    // list = 10->20->30->40
    head = insert_last(head, 20);
    head = insert_last(head, 30);
    head = insert_last(head, 40);
    head = insert_first(head, 10);
    print_list(head);
    printf("\n");

    delete_first(head);
    delete_last(head);

    print_list(head);
    printf("\n");

    return 0;
}
