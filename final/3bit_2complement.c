#include <stdio.h>

// 3비트 2의 보수: -4 ~ +3
int to_twos_complement(int x) {
    // 3비트 마스크
    x &= 0x7;
    return x;
}

// 3비트 이진수 -> signed int
int from_twos_complement(int x) {
    if(x & 0x4) // 3번째 비트가 1이면 음수
        return x - 8;
    return x;
}

// 3비트 2의 보수 출력
void print_bits(int x) {
    for(int i=2; i>=0; i--)
        printf("%d", (x>>i)&1);
}

// Overflow 판별: 입력 두 수 부호 같고, 결과 부호 다르면 Overflow
int is_overflow(int a, int b, int sum) {
    int sign_a = (a & 0x4) != 0;
    int sign_b = (b & 0x4) != 0;
    int sign_sum = (sum & 0x4) != 0;
    return (sign_a == sign_b) && (sign_a != sign_sum);
}

int main() {
    // (a) 십진수를 3비트 2의 보수로 변환
    int decs[] = {2, 3, -2, -3};
    printf("== (a) 3비트 2의 보수 변환 ==\n");
    for(int i=0; i<4; i++) {
        int val = decs[i];
        int tc = to_twos_complement(val);
        printf("%+d --> ", val);
        print_bits(tc);
        printf("\n");
    }
    printf("\n");

    // (b) 네 가지 연산 시뮬레이션
    struct { int a, b; } tests[] = {
        {+3, -2},
        {+3, +2},
        {-3, -2},
        {-3, +2}
    };
    printf("== (b) 3비트 덧셈 및 Overflow 판별 ==\n");
    for(int i=0; i<4; i++) {
        int a = tests[i].a, b = tests[i].b;
        int tca = to_twos_complement(a);
        int tcb = to_twos_complement(b);
        int sum = (tca + tcb) & 0x7; // 3비트만 유지
        int result = from_twos_complement(sum);

        printf("(%+d) + (%+d): ", a, b);
        print_bits(tca); printf(" + "); print_bits(tcb); printf(" = ");
        print_bits(sum);
        printf(" (=%+d) ", result);
        if(is_overflow(tca, tcb, sum))
            printf("[Overflow]");
        printf("\n");
    }
    return 0;
}
