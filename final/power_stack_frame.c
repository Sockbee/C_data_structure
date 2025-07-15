#include <stdio.h>

// 호출 깊이(스택 레벨) 추적용 전역 변수
int call_level = 0;

// 각 호출마다 들여쓰기
void print_indent() {
    for(int i=0; i<call_level; i++) printf("  ");
}

// 실제 power 함수 시뮬레이션
int power(int x, int n) {
    int ret_addr = 7; // power 함수 return 직후 주소 (임의, 실제 주소 대신)

    // 스택 프레임 진입(push)
    print_indent();
    printf("[Push] power(x=%d, n=%d), ret_addr=%d\n", x, n, ret_addr);
    call_level++;

    int return_value = 0;
    if(n == 0) {
        return_value = 1;
        print_indent();
        printf("  [Return value] %d\n", return_value);
        call_level--;
        print_indent();
        printf("[Pop] power(x=%d, n=%d), ret_addr=%d\n", x, n, ret_addr);
        return return_value;
    }
    if(n % 2 == 0) {
        return_value = power(x * x, n / 2);
        print_indent();
        printf("  [Return value] %d\n", return_value);
        call_level--;
        print_indent();
        printf("[Pop] power(x=%d, n=%d), ret_addr=%d\n", x, n, ret_addr);
        return return_value;
    } else {
        return_value = x * power(x * x, n / 2);
        print_indent();
        printf("  [Return value] %d\n", return_value);
        call_level--;
        print_indent();
        printf("[Pop] power(x=%d, n=%d), ret_addr=%d\n", x, n, ret_addr);
        return return_value;
    }
}

int main() {
    int ret_addr = 203; // main에서 power 호출 뒤 주소
    int x = 2, n = 12;
    printf("[Push] main(), ret_addr=%d\n", ret_addr);
    call_level++;
    int result = power(x, n);
    printf("[Return value to main] %d\n", result);
    call_level--;
    printf("[Pop] main(), ret_addr=%d\n", ret_addr);
    return 0;
}
