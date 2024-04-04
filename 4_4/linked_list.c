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

ListNode* insert_position(ListNode* head, int position, element value) {
    int k = 1;
    // q는 이전 노드의 주소(즉, 삽입될 노드의 위치), p는 현재 위치하고있는 노드
    ListNode* p = NULL, *q = NULL;
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = value;
    p = head;

    // 1번 위치에 입력
    if(position == 1) {
        newNode->link = p;
        // 헤드의 주소값을 새로운 노드의 주소값으로 설정
        return newNode;
    }
    else {
        // 위치(position)를 찾는 과정
        while((p!=NULL) && (k<position)) {
            k++;
            // 이전 노드 위치 갱신
            q = p;
            // 현재 위치 노드 주소값 갱신
            p = p->link;
        }
        // 끝 노드에 추가되는 경우
        if(p==NULL) {
            // newNode의 이전 노드의 링크값은 newNode로 갱신
            q->link = newNode;
            // newNode의 다음 노드 링크값은 null
            newNode->link = NULL;
        } 
        // position 노드에 추가하는 경우
        else {
            // q는 이전노드 : q의 다음 노드의 링크값을 newNode로 갱신
            q->link = newNode;
            // newNode의 다음 노드의 링크값을 p로 갱신
            newNode->link = p;
        }
        return head;
    }

}

ListNode* delete_position(ListNode* head, int position) {
    ListNode* currentNode = head;
    ListNode* prevNode = NULL;
    int current_index = 1;

    // 만약 1번 위치 노드를 삭제하는 경우
    if(position == 1) {
        ListNode* temp = head;
        // 헤드를 1번 노드의 다음 노드를 가리키도록 설정
        head = temp->link;
        free(temp);
        return head;
    }
    else {
        // 링크드 리스트의 범위를 벗어나지 않는 한에서 포인터 업데이트
        while((currentNode != NULL) && (current_index < position)) {
            current_index++;
            prevNode = currentNode;
            currentNode = currentNode->link;
        }
        // 현 위치 노드는 메모리 할당을 해제해주고, 이전 노드를 현위치의 다음노드에 연결
        if(currentNode != NULL) {
            prevNode->link = currentNode->link;
            free(currentNode);
        }
        return head;
    }
}

void search(ListNode *head, int value) {
    ListNode *p = head;
    int located_index = 0;

    while(p != NULL) {
        ++located_index;
        if(p->data == value) {
            printf("%d번째에 위치하고 있습니다.\n", located_index);
            break;
        }
        // 다음 노드로 이동
        p = p->link;
    }
}

int main(void) {
    ListNode* head = NULL;

    head = insert_position(head, 1, 10);
    head = insert_position(head, 2, 20);
    head = insert_position(head, 3, 30);
    head = insert_position(head, 4, 40);

    head = delete_position(head, 1);
    head = delete_position(head, 3);
    head = delete_position(head, 2);
    print_list(head);

    search(head, 20);

    free(head);
    return 0;
}
