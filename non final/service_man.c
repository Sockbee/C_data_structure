#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE_SIZE 100
#define TRUE 1
#define FALSE 0
#define NoServiceMan 1  // 서비스맨 수: 1 또는 3으로 바꿔서 실험

// ====== 구조체 정의 ======
typedef struct {
    int id;
    int arrival_time;
    int service_time;
} element;

typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

// ====== 전역 변수 ======
QueueType queue;

int duration = 100;              // 시뮬레이션 시간
double arrival_prob = 0.7;      // 고객 도착 확률
int max_serv_time = 15;          // 최대 서비스 시간
int clock_time = 0;             // 현재 시각 (전역 clock 변수와 이름 충돌 방지)

int customers = 0;              // 전체 고객 수
int served_customers = 0;       // 서비스 받은 고객 수
int waited_time = 0;            // 총 대기 시간
int service_idle_time[NoServiceMan]; // 서비스맨별 유휴 시간 누적

// ====== 큐 연산 ======
void init_queue(QueueType *q) {
    q->front = q->rear = 0;
}

int is_empty(QueueType *q) {
    return q->front == q->rear;
}

int is_full(QueueType *q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void enqueue(QueueType *q, element item) {
    if (is_full(q)) {
        printf("큐가 가득 찼습니다!\n");
        exit(1);
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

element dequeue(QueueType *q) {
    if (is_empty(q)) {
        printf("큐가 비었습니다!\n");
        exit(1);
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

// ====== 유틸 함수 ======
double random_prob() {
    return rand() / (double)RAND_MAX;
}

int is_customer_arrived() {
    return random_prob() < arrival_prob ? TRUE : FALSE;
}

void insert_customer(int arrival_time) {
    element customer;
    customer.id = customers++;
    customer.arrival_time = arrival_time;
    customer.service_time = (int)(max_serv_time * random_prob()) + 3;

    enqueue(&queue, customer);

    printf("고객 %d이 %d분에 도착. 서비스시간: %d분\n",
           customer.id, customer.arrival_time, customer.service_time);
}

int remove_customer() {
    if (is_empty(&queue)) return 0;

    element customer = dequeue(&queue);
    int service_time = customer.service_time - 1;
    served_customers++;
    waited_time += clock_time - customer.arrival_time;

    printf("고객 %d이 %d분에 서비스 시작. 대기시간: %d분\n",
           customer.id, clock_time, clock_time - customer.arrival_time);

    return service_time;
}

void print_stat() {
    printf("\n[시뮬레이션 결과: 서비스맨 %d명]\n", NoServiceMan);
    printf("서비스 받은 고객 수 = %d\n", served_customers);
    printf("전체 대기 시간 = %d분\n", waited_time);
    printf("1인당 평균 대기 시간 = %.2f분\n",
           served_customers == 0 ? 0 : (double)waited_time / served_customers);
    printf("대기 중인 고객 수 = %d\n", customers - served_customers);

    int total_idle = 0;
    for (int i = 0; i < NoServiceMan; i++)
        total_idle += service_idle_time[i];

    printf("전체 서비스 유휴 시간 (idle time) = %d분\n", total_idle);
}

// ====== 메인 시뮬레이션 함수 ======
int main() {
    int service_time[NoServiceMan] = {0};  // 각 서비스맨의 남은 서비스 시간 초기화
    srand((unsigned)time(NULL));           // 랜덤 시드 초기화

    init_queue(&queue);

    for (clock_time = 0; clock_time < duration; clock_time++) {
        printf("\n[현재 시각: %d분]\n", clock_time);

        if (is_customer_arrived()) {
            insert_customer(clock_time);
        }

        for (int k = 0; k < NoServiceMan; k++) {
            if (service_time[k] > 0) {
                service_time[k]--;
            } else {
                if (!is_empty(&queue)) {
                    service_time[k] = remove_customer();
                } else {
                    service_idle_time[k]++;
                    printf("서비스맨 %d은 유휴 상태입니다.\n", k);
                }
            }
        }
    }

    print_stat();
    return 0;
}
