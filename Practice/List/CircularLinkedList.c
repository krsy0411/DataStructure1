#include <stdio.h>
#include <stdlib.h>

// 원형(링크드)리스트 : 마지막 노드가 첫 번째 노드를 가리키는 리스트 : <단일 및 이중 연결 리스트 형태 둘 다 구현 가능>
// 지금은 단일 링크드 리스트로 구현합니다
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 노드 생성
Node* createNode(int data) {
    Node* node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;

    return node;
}

// 리스트에 노드 추가
// 이중포인터를 통해 : 헤드 포인터의 주소값 받아옴
void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);

    // 만약 헤드 노드가 비어있으면 헤드 노드에 추가
    if((*head) == NULL) {
        *head = newNode;
        // 헤드 노드가 비어있다면, 헤드 노드의 다음 노드 포인터는 자기 자신을 가리켜야함(노드가 하나뿐이니까)
        newNode->next = *head;
        return;
    }
    // 헤드 노드가 비어있지 않은 경우의 로직

    // 우선 헤드 노드 가리키는 포인터로 초기화
    Node* tempNode = *head; 
    while(tempNode->next != *head) {
        // 일시적 노드를 마지막 노드로 찾아서 할당하고
        tempNode = tempNode->next;
    }
    // 원형 단일 링크드 리스트 형태로 만들기 : 마지막 노드가 첫번째 노드를 가리키도록
    tempNode->next = newNode;
    newNode->next = *head;
}

// (원형 단일)리스트에서 노드 삭제
void deleteNode(Node** head, int index) {
    if (*head == NULL) return; // 리스트가 비어있으면 아무것도 하지 않음

    Node* temp = *head;

    // 1. 헤드 노드를 삭제하는 경우
    if(index == 0) {
        // 1.1 헤드 노드만 존재하는 경우
        if(temp->next == *head) {
            free(temp); // 헤드 노드의 주소값을 가리키는 포인터 변수의 메모리 해제
            *head = NULL; // 헤드 노드 주소값이 참조하는 값을 NULL로 만들기
            return;
        } 

        // 1.2 리스트에 헤드 노드말고도 노드가 있는 경우
        Node* last = *head; // 마지막 노드 표현을 위한 임시 변수
        while(last->next != *head) {
            // 마지막 노드를 찾아주고
            last = last->next;
        }

        last->next = temp->next; // 마지막 노드의 next를 헤드노드의 다음 노드로 연결
        *head = temp->next; // 헤드 노드를 다음 노드로 옮기기
        free(temp); // 메모리 할당 해제
        return;
    }

    // 2. 헤드 노드가 아닌 노드를 삭제하는 경우(인덱스가 0이 아닌 경우)
    Node* prev = NULL;
    for (int i = 0; i < index; i++) {
        prev = temp; // 삭제할 노드의 이전 노드에 해당
        temp = temp->next; // temp가 삭제할 노드에 해당

        // 인덱스가 리스트의 길이를 초과하는 경우 : 반복문의 조건문에 달아도 괜찮음
        if (temp == *head) {
            printf("Index out of bounds\n");
            return;
        }
    }
    prev->next = temp->next; // 삭제할 노드의 이전노드를, 삭제 노드의 다음 노드와 연결
    free(temp);
}

// 헤드 노드 포인터를 인자로
void printList(Node* head) {
    if(head == NULL) return;

    Node* tempNode = head;
    printf("\n------------------------------\n");
    while(tempNode->next != head) {
        printf("%d -> ", tempNode->data);
        tempNode = tempNode->next;
    }
    printf("HEAD");
    printf("\n------------------------------\n");
}

int main() {
    // 헤드 노드를 가리키는 포인터 변수 생성
    Node* head = NULL;
    for(int i=1; i<10; i++) {
        // 헤드 포인터가 가리키는 주소값 전달
        appendNode(&head, i*10);
    }
    printList(head);

    deleteNode(&head, 1);
    printList(head);


    return 0;
}