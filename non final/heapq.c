#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

// 힙 배열 구조체
typedef struct {
    int data[MAX_SIZE];  // 힙 데이터를 저장할 배열
    int size;            // 힙의 현재 크기
} MinHeap;

// 힙 초기화
void initHeap(MinHeap* heap) {
    heap->size = 0;
}

// 부모 인덱스 구하기
int parent(int i) {
    return (i - 1) / 2;
}

// 왼쪽 자식 인덱스 구하기
int leftChild(int i) {
    return 2 * i + 1;
}

// 오른쪽 자식 인덱스 구하기
int rightChild(int i) {
    return 2 * i + 2;
}

// 힙 구조를 재정렬하는 함수 (부모-자식 관계 유지)
void heapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    // 왼쪽 자식이 더 작은 경우
    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }

    // 오른쪽 자식이 더 작은 경우
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }

    // 만약 부모가 가장 작지 않으면, 자식과 교환하고 다시 heapify
    if (smallest != i) {
        int temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;

        heapify(heap, smallest);  // 교환 후 재귀적으로 heapify
    }
}

// 힙에 요소 삽입
void insert(MinHeap* heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("Heap is full\n");
        return;
    }

    // 배열의 끝에 새로운 값 삽입
    int i = heap->size++;
    heap->data[i] = value;

    // 부모와 비교하여 힙 속성 유지 (상향식 조정)
    while (i != 0 && heap->data[parent(i)] > heap->data[i]) {
        // 부모와 자식 교환
        int temp = heap->data[i];
        heap->data[i] = heap->data[parent(i)];
        heap->data[parent(i)] = temp;

        // 부모 인덱스로 이동
        i = parent(i);
    }
}

// 힙에서 최솟값을 제거하고 반환
int pop(MinHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return -1;  // 힙이 비어있을 때
    }

    // 루트(최솟값)를 가져오고, 마지막 요소를 루트로 이동
    int root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];

    // 힙 구조를 재정렬
    heapify(heap, 0);

    return root;
}

// 힙의 루트 요소 출력 (최솟값)
int peek(MinHeap* heap) {
    if (heap->size > 0) {
        return heap->data[0];
    }
    printf("Heap is empty\n");
    return -1;  // 힙이 비어있을 때
}

// 힙 상태 출력
void printHeap(MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

// 메인 함수
int main() {
    MinHeap heap;
    initHeap(&heap);  // 힙 초기화

    insert(&heap, 10);
    insert(&heap, 20);
    insert(&heap, 5);
    insert(&heap, 1);
    insert(&heap, 7);

    printf("Heap after insertions: ");
    printHeap(&heap);

    printf("Peek (minimum value): %d\n", peek(&heap));

    printf("Popped value: %d\n", pop(&heap));
    printf("Heap after pop: ");
    printHeap(&heap);

    printf("Popped value: %d\n", pop(&heap));
    printf("Heap after pop: ");
    printHeap(&heap);
    printf("\n");

    return 0;
}