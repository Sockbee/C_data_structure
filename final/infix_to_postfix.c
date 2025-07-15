#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// 스택 구조체
typedef struct {
    char data[MAX];
    int top;
} Stack;

void push(Stack *s, char c) {
    s->data[++(s->top)] = c;
    printf("  push('%c') → Stack: [", c);
    for(int i=0; i<=s->top; i++) printf("%c", s->data[i]);
    printf("]\n");
}

char pop(Stack *s) {
    char c = s->data[(s->top)--];
    printf("  pop('%c')  → Stack: [", c);
    for(int i=0; i<=s->top; i++) printf("%c", s->data[i]);
    printf("]\n");
    return c;
}

char peek(Stack *s) {
    if(s->top < 0) return '\0';
    return s->data[s->top];
}

int precedence(char op) {
    if(op == '(') return 0;
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

int main() {
    char infix[] = "(G+((B-(C/A)+D)*(E+F)))";
    char postfix[MAX] = "";
    int k = 0;
    Stack s; s.top = -1;

    printf("중위수식: %s\n\n", infix);
    printf("=== 변환 과정 ===\n");

    for(int i=0; infix[i]; i++) {
        char ch = infix[i];
        if(isspace(ch)) continue;

        if(isalpha(ch)) { // 피연산자
            postfix[k++] = ch;
            printf("출력: '%c' → Postfix: %.*s\n", ch, k, postfix);
        }
        else if(ch == '(') {
            push(&s, ch);
        }
        else if(ch == ')') {
            while(peek(&s) != '(') {
                postfix[k++] = pop(&s);
                printf("출력 → Postfix: %.*s\n", k, postfix);
            }
            pop(&s); // '(' pop
            printf("  pop('(')  → Stack: [");
            for(int x=0; x<=s.top; x++) printf("%c", s.data[x]);
            printf("]\n");
        }
        else if(strchr("+-*/", ch)) {
            while(s.top >= 0 && precedence(peek(&s)) >= precedence(ch)) {
                postfix[k++] = pop(&s);
                printf("출력 → Postfix: %.*s\n", k, postfix);
            }
            push(&s, ch);
        }
    }
    // 남은 연산자 pop
    while(s.top >= 0) {
        postfix[k++] = pop(&s);
        printf("출력 → Postfix: %.*s\n", k, postfix);
    }

    postfix[k] = '\0';

    printf("\n=== 최종 후위수식 ===\n");
    printf("%s\n", postfix);
    return 0;
}
