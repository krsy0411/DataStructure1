#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 스택 구조체 정의
typedef struct Stack {
    int data;
    struct Stack* next;
} Stack;

// 스택 초기화 함수
void initialize(Stack** top) {
    *top = NULL;
}

// 스택이 비어있는지 확인하는 함수
int is_empty(Stack* top) {
    return top == NULL;
}

// 스택에 원소 추가 함수
void push(Stack** top, int data) {
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

// 스택에서 원소 제거 함수
void pop(Stack** top) {
    if (is_empty(*top)) {
        //printf("스택이 비어있습니다.\n");
        return;
    }
    Stack* temp = *top;
    *top = (*top)->next;
    free(temp);
}

// 스택에서 가장 위의 원소 반환 함수
int peek(Stack* top) {
    if (is_empty(top)) {
        //printf("스택이 비어있습니다.\n");
        return 0; // 임의의 값 반환
    }
    return top->data;
}

// 연산자의 우선순위를 반환하는 함수
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0; // 연산자가 아닌 경우
}
// 중위 표현식을 후위 표현식으로 변환하는 함수
char* infixToPostfix(char* expression) {
    Stack* stack;
    initialize(&stack);

    int length = strlen(expression);
    char* postfix = (char*)malloc((length + 1) * sizeof(char));
    int index = 0;

    for (int i = 0; i < length; i++) {
        char token = expression[i];
        if ((token >= '0' && token <= '9') || (token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z')) {
            // 피연산자인 경우
            postfix[index++] = token;
        } else if (token == '(') {
            // 왼쪽 괄호인 경우
            push(&stack, token);
        } else if (token == ')') {
            // 오른쪽 괄호인 경우
            while (!is_empty(stack) && peek(stack) != '(') {
                postfix[index++] = peek(stack);
                pop(&stack);
            }
            if (!is_empty(stack) && peek(stack) == '(') {
                pop(&stack); // 왼쪽 괄호 제거
            } else {
                printf("괄호 짝이 맞지 않습니다.\n");
                free(postfix);
                return NULL;
            }
        } else {
            // 연산자인 경우
            while (!is_empty(stack) && precedence(peek(stack)) >= precedence(token)) {
                postfix[index++] = peek(stack);
                pop(&stack);
            }
            push(&stack, token);
        }
    }

    // 남아있는 연산자들을 후위 표현식에 추가
    while (!is_empty(stack)) {
        if (peek(stack) == '(') {
            printf("괄호 짝이 맞지 않습니다.\n");
            free(postfix);
            return NULL;
        }
        postfix[index++] = peek(stack);
        pop(&stack);
    }

    postfix[index] = '\0'; // 문자열 끝에 NULL 문자 추가
    return postfix;
}

// 후위 표현식을 계산하는 함수
int evaluate(char* postfix) {
    Stack* stack;
    initialize(&stack);

    int length = strlen(postfix);

    for (int i = 0; i < length; i++) {
        char token = postfix[i];
        if (token >= '0' && token <= '9') {
            // 피연산자인 경우
            push(&stack, token - '0'); // 문자를 숫자로 변환하여 스택에 push
        } else {
            // 연산자인 경우
            int operand2 = peek(stack);
            pop(&stack);
            int operand1 = peek(stack);
            pop(&stack);

            // 연산 수행 후 결과를 스택에 push
            switch (token) {
                case '+':
                    push(&stack, operand1 + operand2);
                    break;
                case '-':
                    push(&stack, operand1 - operand2);
                    break;
                case '*':
                    push(&stack, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("0으로 나눌 수 없습니다.\n");
                        return 0;
                    }
                    push(&stack, operand1 / operand2);
                    break;
                default:
                    printf("올바르지 않은 연산자입니다.\n");
                    return 0;
            }
        }
    }

    // 최종 결과 반환
    return peek(stack);
}



// 괄호 사용이 정상인지 체크하는 함수
void bracketCheck(char* expression) {
    Stack* stack;
    initialize(&stack);

    int length = strlen(expression);

    for (int i = 0; i < length; i++) {
        char token = expression[i];
        if (token == '(') {
            push(&stack, '(');
        } else if (token == ')') {
            if (is_empty(stack) || peek(stack) != '(') {
                printf("열린 괄호와 닫힌 괄호의 짝이 맞지 않습니다.\n");
                return;
            }
            pop(&stack);
        }
    }

    if (!is_empty(stack)) {
        printf("열린 괄호와 닫힌 괄호의 짝이 맞지 않습니다.\n");
    } else {
        printf("괄호 사용이 정상적입니다.\n");
    }
}

int main() {
    char expression[100];
    
    printf("수식을 입력하세요: ");
    fgets(expression, sizeof(expression), stdin);
    
    printf("입력한 수식: %s", expression);

    // 괄호 체크
    bracketCheck(expression);

    // 중위 표현식을 후위 표현식으로 변환
    char* postfix = infixToPostfix(expression);
    if(postfix != NULL) {
        printf("후위 표현식: %s\n", postfix);
        
        // 후위 표현식을 계산
        int result = evaluate(postfix);
        printf("계산 결과: %d\n", result);
        
        free(postfix);
    }

    return 0;
}
