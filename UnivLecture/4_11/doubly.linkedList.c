#include <stdio.h>
#include <stdlib.h>

// 구조체
typedef struct ListNode {
    int data;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

void printList(ListNode *head) {
    if(head == NULL) {
        printf("리스트가 비어 있습니다\n");
        return;
    }
    // 원소를 1번씩만 출력하기 위해 포인터 생성
    ListNode *current = head;
    while(current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

ListNode* insert(ListNode *head, char position, int value) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->data = value;

    // 새로운 노드를 삽입할 위치를 결정합니다.
    if (position == 'L') { // 왼쪽에 삽입
        newNode->next = head;
        newNode->prev = NULL;
        if (head != NULL) {
            head->prev = newNode;
        }
        head = newNode; // head가 새로운 노드를 가리키도록 업데이트
    } else if (position == 'R') { // 오른쪽에 삽입
        ListNode *last = head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
        newNode->prev = last;
        newNode->next = NULL;
    } else {
        printf("잘못된 위치입니다.\n");
        free(newNode);
        return head;
    }

    return head; // 변경된 head 반환
}

void delete(ListNode *head, char position) {
    if (head->next == NULL) { // 리스트가 비어있는 경우
        printf("리스트가 비어있습니다.\n");
        return;
    }

    ListNode *temp;
    if (position == 'L') { // 왼쪽 노드 삭제
        temp = head->next;
        if (temp->next != NULL) {
            temp->next->prev = NULL;
        }
        head->next = temp->next;
        free(temp);
    } else if (position == 'R') { // 오른쪽 노드 삭제
        ListNode *last = head;
        while (last->next != NULL) {
            last = last->next;
        }
        temp = last->prev;
        if (temp != NULL) {
            temp->next = NULL;
        }
        free(last);
    } else {
        printf("잘못된 위치입니다.\n");
        return;
    }
}

int main() {
    ListNode *head = (ListNode *)malloc(sizeof(ListNode)); 
    head->data = 0; head->next = NULL; head->prev = NULL;

    head = insert(head, 'R', 10);
    head = insert(head, 'R', 20);
    head = insert(head, 'R', 30);
    head = insert(head, 'L', 40);
    head = insert(head, 'L', 50);

    delete(head, 'L');
    delete(head, 'R');

    printList(head);

    return 0;
}