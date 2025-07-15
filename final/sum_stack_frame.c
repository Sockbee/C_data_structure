#include <stdio.h>
#include <string.h>

#define MAX_DEPTH 10

typedef struct {
    char funcname[16];
    int n;           // formal parameter
    int ret_addr;
    int retval;      // return value
    int local_result; // local variable (result)
    int valid;
} StackFrame;

StackFrame stack[MAX_DEPTH];
int sp = 0; // stack pointer

void print_stack(const char* msg) {
    printf("\n%s\n", msg);
    printf("-----------------------------------------------------------------------------\n");
    printf("| %-12s | %-7s | %-9s | %-7s | %-14s |\n", "function", "param n", "ret addr", "retval", "local variable");
    printf("-----------------------------------------------------------------------------\n");
    for(int i=0; i<=sp; i++) {
        if(stack[i].valid)
            printf("| %-12s | %-7d | %-9d | %-7d | result = %-6d   |\n",
                stack[i].funcname, stack[i].n, stack[i].ret_addr, stack[i].retval, stack[i].local_result);
    }
    printf("-----------------------------------------------------------------------------\n");
}

int sum(int n, int ret_addr) {
    // 프레임 생성(push)
    sp++;
    strcpy(stack[sp].funcname, "sum");
    stack[sp].n = n;
    stack[sp].ret_addr = ret_addr;
    stack[sp].retval = 0;
    stack[sp].local_result = 0;
    stack[sp].valid = 1;

    print_stack("[Stack Frame after call]");

    int result;
    if(n == 1) {
        result = 1;
        stack[sp].local_result = result;
        stack[sp].retval = result;
    } else {
        int recursive_result = sum(n-1, 100+sp); // 지역 변수 추적용
        result = n + recursive_result;
        stack[sp].local_result = result;
        stack[sp].retval = result;
    }

    print_stack("[Stack Frame before return]");

    // 프레임 소멸(pop)
    sp--;

    return result;
}

int main() {
    sp = 0;
    strcpy(stack[sp].funcname, "main");
    stack[sp].n = 3;
    stack[sp].ret_addr = 0;
    stack[sp].retval = 0;
    stack[sp].local_result = 0;
    stack[sp].valid = 1;

    print_stack("[Stack Frame after main entry]");

    int result = sum(3, 999);
    stack[sp].retval = result;
    stack[sp].local_result = result;

    print_stack("[Stack Frame after returning sum(3)]");

    printf("\nResult of sum(3) = %d\n", result);
    return 0;
}
