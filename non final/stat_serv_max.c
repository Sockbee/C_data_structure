#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE_SIZE 100
#define DURATION 100
#define NO_SERVICE_MAN 1
#define NUM_TRIALS 30
#define ARRIVAL_PROB 0.5  // 고정

typedef struct {
    int id;
    int arrival_time;
    int service_time;
} Customer;

typedef struct {
    Customer queue[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

void init_queue(Queue* q) {
    q->front = q->rear = 0;
}

int is_empty(Queue* q) {
    return q->front == q->rear;
}

int is_full(Queue* q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void enqueue(Queue* q, Customer item) {
    if (is_full(q)) return;
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

Customer dequeue(Queue* q) {
    Customer dummy = {-1, 0, 0};
    if (is_empty(q)) return dummy;
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

double rand_prob() {
    return rand() / (double)RAND_MAX;
}

void simulate(int max_serv_time, int* out_waited_time, int* out_served_customers) {
    Queue queue;
    init_queue(&queue);

    int service_time[NO_SERVICE_MAN] = {0};
    int service_idle_time[NO_SERVICE_MAN] = {0};

    int clock_time, customers = 0;
    int served_customers = 0;
    int waited_time = 0;
    int customer_id = 0;

    for (clock_time = 0; clock_time < DURATION; clock_time++) {
        if (rand_prob() < ARRIVAL_PROB) {
            Customer cust;
            cust.id = customer_id++;
            cust.arrival_time = clock_time;
            cust.service_time = (int)(max_serv_time * rand_prob()) + 1;
            enqueue(&queue, cust);
            customers++;
        }

        for (int k = 0; k < NO_SERVICE_MAN; k++) {
            if (service_time[k] > 0) {
                service_time[k]--;
            } else {
                if (!is_empty(&queue)) {
                    Customer next = dequeue(&queue);
                    service_time[k] = next.service_time - 1;
                    waited_time += clock_time - next.arrival_time;
                    served_customers++;
                } else {
                    service_idle_time[k]++;
                }
            }
        }
    }

    *out_waited_time = waited_time;
    *out_served_customers = served_customers;
}

int main() {
    FILE* fp = fopen("max_service_time_simulation_man1.csv", "w");
    if (fp == NULL) {
        printf("CSV 파일을 열 수 없습니다.\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    fprintf(fp, "max_service_time,avg_waited_time,avg_served_customers\n");

    for (int max_serv_time = 1; max_serv_time <= 20; max_serv_time++) {
        int total_waited_time = 0;
        int total_served_customers = 0;

        for (int trial = 0; trial < NUM_TRIALS; trial++) {
            int waited_time = 0;
            int served_customers = 0;
            simulate(max_serv_time, &waited_time, &served_customers);

            total_waited_time += waited_time;
            total_served_customers += served_customers;
        }

        double avg_waited_time = total_served_customers == 0 ? 0 : (double)total_waited_time / NUM_TRIALS;
        double avg_served_customers = (double)total_served_customers / NUM_TRIALS;

        fprintf(fp, "%d,%.2f,%.2f\n", max_serv_time, avg_waited_time, avg_served_customers);
    }

    fclose(fp);
    printf("CSV 파일이 생성되었습니다: max_service_time_simulation.csv\n");
    return 0;
}
