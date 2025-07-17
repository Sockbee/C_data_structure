#include <stdio.h>

void print_indent(int depth) {
    for(int i=0; i<depth; i++) printf("  ");
}

int foo(int n, int depth, const char* return_addr) {
    // 파라미터, 리턴주소 출력 (스택프레임 생성)
    print_indent(depth);
    printf("[Frame 생성] foo(n=%d), parameter: n=%d, local: prev=?, result=?, return_address: %s\n", n, n, return_addr);

    if(n == 1) {
        int prev = 0;   // 정의되지 않음
        int result = 1; // n==1이므로
        print_indent(depth);
        printf("[Frame 종료] foo(n=%d), parameter: n=%d, local: prev=?, result=%d, return_address: %s, return_value=%d\n", n, n, result, return_addr, result);
        print_indent(depth);
        printf("printf: n: %d, prev: ?, result: %d\n", n, result);
        return result;
    }

    // 재귀 호출: prev의 값을 받음
    int prev = foo(n-1, depth+1, "foo+1(4/5/6)"); // 호출자의 라인 위치 대략 기입
    int result = prev + n*n;

    // 스택프레임의 모든 값 출력 (리턴 직전)
    print_indent(depth);
    printf("[Frame 종료] foo(n=%d), parameter: n=%d, local: prev=%d, result=%d, return_address: %s, return_value=%d\n", n, n, prev, result, return_addr, result);

    print_indent(depth);
    printf("printf: n: %d, prev: %d, result: %d\n", n, prev, result);

    return result;
}

int main() {
    printf("[Frame 생성] main(), parameter: 없음, local: total=?, return_address: OS\n");
    int total = foo(4, 1, "main+1(202)");
    printf("[Frame 종료] main(), parameter: 없음, local: total=%d, return_address: OS, return_value=%d\n", total, total);
    printf("printf: Total sum of squares: %d\n", total);
    return 0;
}
