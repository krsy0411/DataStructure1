#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data; // 실제 정수형 데이터를 보관하는 변수
    struct Node* next; 
} Node;

// 보통의 경우, 리스트의 ADT는 다음과 같습니다 : create, append, insert, remove, getAt

// 노드 생성
Node* createNode(int data) {
    Node* newNode = (Node *)malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

// 노드 삽입
// 이중 참조 연산자를 사용한 이유 : 헤드 노드의 주소를 가리키는 포인터의 주소를 인자로 받아옴으로써, 원본을 수정하기 위해서
void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);

    // 간접참조연산자(*)를 이용해서 헤드 노드를 가리키는 포인터의 주소값을 받아왔는데, NULL이면 헤드 노드에 생성한 노드를 바로 삽입
    if(*head == NULL) {
        *head = newNode;
        return ;
    }
    // 만약 헤드 노드가 존재하면, 게속 다음 노드로 넘어가면서 다음 노드가 NULL인 경우의 노드의 뒤에 생성한 노드를 연결
    Node* temp = *head; // 데이터 삽입을 위한 잠시 주소값을 보관해둘 포인터 변수
    while(temp->next != NULL) {
        temp = temp->next; // 다음 노드의 주소값이 NULL일때까지 계속 갱신
    }

    temp->next = newNode;
}

// 이중 포인터를 인자로 받는 이유 : 헤드노드를 가리키는 헤드포인터를 가리키는 포인터를 함수에서 사용하기 위해서
void deleteNode(Node** head, int index) {
    Node* temp = *head;

    if(index == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    // 삭제할 인덱스의 노드의 이전 주소값을 갱신시켜줍니다
    for(int i=0; i<index-1 && temp != NULL; i++) {
        temp = temp->next;
    }   

    // 임시 노드 : 삭제할 노드의 이전 노드 -> 이전 노드를 삭제 노드의 다음 노드와 연결
    Node* deletedNodeNext = temp->next->next;
    // 삭제할 노드의 메모리 할당 해제
    free(temp->next);
    temp->next = deletedNodeNext;
}

// 헤드 노드를 가리키는 포인터를 인자로
Node* getNodeAt(Node* head, int index) {
    // 헤드노드 포인터가 NULL -> 주소 할당받은적 없음을 의미
    if (head == NULL) return NULL;

    Node* temp = head;
    for(int i=0; i<index && temp->next != NULL; i++) {
        temp = temp->next;
    }

    return temp;
}

// 인자 : 헤드 포인터 : 헤드노드의 주소값을 받아옴
void printList(Node* head) {
    Node* temp = head;

    while(temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL \n");
}

int main() {    
    // 헤드 노드(리스트의 첫번째 노드) 초기화 : 값 할당 전엔 포인터 변수의 주소값은 NULL
    Node* head = NULL;
    for(int i=1; i<=5; i++) {
        appendNode(&head, i*10);
    }
    deleteNode(&head, 1);
    printList(head);

    return 0;
}