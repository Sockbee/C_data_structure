#include <stdio.h>

// 호출 깊이 추적용 (stack level)
int call_level = 0;

// 들여쓰기
void print_indent() {
    for(int i=0; i<call_level; i++) printf("  ");
}

int sum(int n) {
    int ret_addr = 4; // return 직후 주소(예시)
    print_indent();
    printf("[Push] sum(n=%d), ret_addr=%d\n", n, ret_addr);
    call_level++;

    int return_value;
    if(n == 1) {
        return_value = 1;
        print_indent();
        printf("  [Return value] %d\n", return_value);
        call_level--;
        print_indent();
        printf("[Pop] sum(n=%d), ret_addr=%d\n", n, ret_addr);
        return return_value;
    }
    else {
        return_value = n + sum(n-1);
        print_indent();
        printf("  [Return value] %d\n", return_value);
        call_level--;
        print_indent();
        printf("[Pop] sum(n=%d), ret_addr=%d\n", n, ret_addr);
        return return_value;
    }
}

int main() {
    int n = 3;
    int ret_addr = 100; // main에서 sum 호출 뒤 주소(임의)
    printf("[Push] main(), ret_addr=%d\n", ret_addr);
    call_level++;
    int result = sum(n);
    printf("[Return value to main] %d\n", result);
    call_level--;
    printf("[Pop] main(), ret_addr=%d\n", ret_addr);
    return 0;
}
