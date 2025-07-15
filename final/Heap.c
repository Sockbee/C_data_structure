#include <stdio.h>
#define N 8

void printArray(int arr[], int size) {
    printf("Array: ");
    for(int i = 0; i < size; i++)
        printf("%2d ", arr[i]);
    printf("\n");
}

// 힙 삽입 (heapify up)
void insertHeap(int heap[], int* size, int value) {
    int i = (*size)++;
    heap[i] = value;
    printf("  [Insert %d at index %d]\n", value, i);
    // 부모와 swap
    while(i > 0 && heap[(i-1)/2] < heap[i]) {
        printf("    Swap heap[%d]=%d and heap[%d]=%d\n",
            (i-1)/2, heap[(i-1)/2], i, heap[i]);
        int temp = heap[(i-1)/2];
        heap[(i-1)/2] = heap[i];
        heap[i] = temp;
        i = (i-1)/2;
    }
    printArray(heap, *size);
}

// heapify down
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        printf("    Heapify swap arr[%d]=%d and arr[%d]=%d\n", i, arr[i], largest, arr[largest]);
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

int main() {
    int keys[N] = {14, 21, 11, 16, 18, 8, 20, 5};
    int heap[N] = {0};
    int size = 0;

    printf("=== [힙 삽입 단계] ===\n");
    for(int i = 0; i < N; i++) {
        insertHeap(heap, &size, keys[i]);
    }

    printf("\n최대 힙 완성 (배열): ");
    printArray(heap, size);

    printf("\n=== [Heap Sort 단계] ===\n");
    for(int i = size-1; i > 0; i--) {
        printf("[Step %d] Swap arr[0]=%d and arr[%d]=%d\n", N-i, heap[0], i, heap[i]);
        int temp = heap[0];
        heap[0] = heap[i];
        heap[i] = temp;
        printArray(heap, N);
        printf("Heapify (size=%d):\n", i);
        heapify(heap, i, 0);
        printArray(heap, N);
    }

    printf("\n정렬 결과 (오름차순): ");
    printArray(heap, N);

    return 0;
}
