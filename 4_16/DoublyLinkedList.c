#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
=======
#include <time.h>
>>>>>>> 5c67d1e (더블 링크드 리스트 과제)

// 구조체 선언
typedef int elementType;
typedef struct Node {
    elementType data;
    struct Node* prevNode;
    struct Node* nextNode;
} Node;

// 노드 생성
Node* CreateNode(elementType newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->prevNode = NULL;
    newNode->nextNode = NULL;

    return newNode;
}

// 노드 소멸
void DestroyNode(Node* node) {
    free(node);
}

// 노드 삽입 : 뒤에
void InsertAfter(Node* current, Node* newNode) {
    // 새로 삽입할 노드의 앞뒤 링크를, 현재노드를 이용해서 연결
    newNode->nextNode = current->nextNode;
    newNode->prevNode = current;
    
    // 현재노드의 다음노드가 있는 경우에는
    if(current->nextNode != NULL) {
        current->nextNode->prevNode = newNode;
        current->nextNode = newNode;
    }
}

// 노드 삽입 : 앞에
void InsertPrev(Node* current, Node* newNode) {
    // 새로 삽입할 노드의 앞뒤 링크를, 현재노드를 이용해서 연결
    newNode->prevNode = current->prevNode;
    newNode->nextNode = current;
    
    // 현재노드의 이전노드가 있는 경우에는
    if(current->prevNode != NULL) {
        current->prevNode->nextNode = newNode;
        current->prevNode = newNode;
    }
}

// 노드 추가
void AppendNode(Node** head, Node* newNode) {
    if( (*head)==NULL ) {
        *head = newNode;
    } else {
        Node* tail = (*head);
        // 헤드에서 시작해서 꼬리노드 찾기
        while(tail->nextNode != NULL) {
            tail = tail->nextNode;
        }
        // 찾았으면 새로운 노드를 연결
        tail->nextNode = newNode;
        // 새로운 노드를 삽입하기 이전의 꼬리노드를 새로운 노드와 이어줍니다
        newNode->prevNode = tail;
    }
}

void PrintNode(Node* headNode) {
    if(headNode == NULL) {
        printf("아직 노드가 존재하지 않습니다");
    }

    for(Node* p=headNode; p!=NULL; p=p->nextNode) {
        printf("%d -> ", p->data);
    }
    printf("NULL \n");
}

Node* GetNode(Node* head, int location) {
    Node* current = head;

    while(current!=NULL && (--location)>=0) {
        current = current->nextNode;
    }

    return current;
}

<<<<<<< HEAD
=======
int GetNodeCount(Node* head) {
    unsigned int count= 0;
    Node* current = head;

    while(current != NULL) {
        current = current->nextNode;
        count++;
    }

    return count;
}

>>>>>>> 5c67d1e (더블 링크드 리스트 과제)
int main(void) {
    Node* list = NULL;
    Node* current = NULL;

<<<<<<< HEAD
    for(int i=1; i<11; i++) {
        Node* newNode = CreateNode(i*10);
=======
    srand((unsigned int)time(NULL));

    int ListSize = (rand() % 10) + 1; // 1-10
    list = (Node*)malloc(sizeof(Node)*ListSize); // 랜덤한 리스트 사이즈만큼 메모리 동적할당


    for(int i=0; i<4; i++) {
        int randomValue = (rand() % 100) + 1; // 1-100
        Node* newNode = CreateNode(randomValue);
>>>>>>> 5c67d1e (더블 링크드 리스트 과제)
        AppendNode(&list, newNode);
    }

    current = GetNode(list, 0);
    printf("노드 생성(초기화) 후 : ");
    PrintNode(current);

<<<<<<< HEAD
    for(int i=1; i<5; i++) {
        current = GetNode(list, i);
        Node* newNode = CreateNode(i);
        InsertPrev(current, newNode);
    }
=======
    // 2번째 노드 위치 찾기
    current = GetNode(list, 2);
    // 노드 삽입
    Node* newNode = CreateNode(599);
    InsertAfter(current, newNode);
>>>>>>> 5c67d1e (더블 링크드 리스트 과제)

    current = GetNode(list, 0);
    printf("노드 삽입 후 : ");
    PrintNode(current);

    return 0;
}