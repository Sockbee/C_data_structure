#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_N 40

long long fib_recursive(int n) {
    if (n <= 1)
        return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

long long memo[MAX_N + 1];
void init_memo() {
    for (int i = 0; i <= MAX_N; i++)
        memo[i] = -1;
}

long long fib_memo(int n) {
    if (memo[n] != -1)
        return memo[n];
    if (n <= 1)
        return memo[n] = n;
    return memo[n] = fib_memo(n - 1) + fib_memo(n - 2);
}

int main() {
    FILE *fp = fopen("fib_times.csv", "w");
    if (!fp) {
        perror("파일 생성 오류");
        return 1;
    }

    fprintf(fp, "n,recursive,memo\n");

    for (int n = 1; n <= MAX_N; n++) {
        clock_t start, end;
        double time_recursive, time_memo;

        // Recursive
        start = clock();
        fib_recursive(n);
        end = clock();
        time_recursive = (double)(end - start) / CLOCKS_PER_SEC;

        // Memoization
        init_memo();
        start = clock();
        fib_memo(n);
        end = clock();
        time_memo = (double)(end - start) / CLOCKS_PER_SEC;

        printf("n=%2d | 재귀: %.9f초 | 메모이제이션: %.9f초\n", n, time_recursive, time_memo);
        fprintf(fp, "%d,%.9f,%.9f\n", n, time_recursive, time_memo);
    }

    fclose(fp);
    printf("결과를 'fib_times.csv' 파일로 저장했습니다.\n");
    return 0;
}
