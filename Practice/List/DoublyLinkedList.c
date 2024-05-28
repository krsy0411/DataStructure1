#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// 노드 생성
Node* createNode(int data) {
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    return newNode;
}

// 노드 삽입
void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);

    // 헤드노드 포인터의 참조값(= 주소값)이 NULL : 데이터가 없다
    if(*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void deleteNode(Node** head, int index) {
    if(*head == NULL) return;

    Node* temp = *head;

    if(index == 0) {
        *head = temp->next;
        if(*head != NULL) {
            (*head)->prev = NULL;
        }
        free(temp);
    }

    for(int i=0; temp != NULL && i<index; i++) {
        temp = temp->next;
    }
    if(temp == NULL) return;
    // temp(지울 노드)의 prev, next 포인터에 잘 연결시키기
    if(temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    if(temp->prev != NULL) {
        temp->prev->next = temp->next;
    }


    free(temp);
}

// 인자 : 포인터
void printList(Node* head) {
    Node* temp = head;

    if(temp == NULL) {
        printf("데이터가 존재하지 않습니다\n");
    }

    while(temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;
    for(int i=1; i<=6; i++) {
        appendNode(&head, i*10);
    }

    deleteNode(&head, 1);
    deleteNode(&head, 2);

    printList(head);
}