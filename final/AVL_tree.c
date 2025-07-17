#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int height;
    struct Node *left, *right;
} Node;

// 높이 반환
int height(Node *node) {
    return node ? node->height : 0;
}

// 최대값 반환
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 노드 생성
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->height = 1; // 처음 삽입 시 높이 = 1
    node->left = node->right = NULL;
    return node;
}

// 높이 갱신
void updateHeight(Node *node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

// 균형 인수 계산
int getBalance(Node *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// LL 회전
Node* rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// RR 회전
Node* rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* insert(Node* node, int key) {
    // 1. BST 삽입
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    // 2. 높이 갱신
    updateHeight(node);

    // 3. 균형 인수 계산
    int balance = getBalance(node);

    // 4. 불균형 처리 및 분석
    if (balance > 1) {
        if (key < node->left->key) {
            printf("Unbalanced at node %d: BF = %d → LL case (insertion in left-left)\n", node->key, balance);
            printf("LL Rotation at node %d\n", node->key);
            return rotateRight(node);
        }
        if (key > node->left->key) {
            printf("Unbalanced at node %d: BF = %d → LR case (insertion in left-right)\n", node->key, balance);
            printf("LR Rotation at node %d\n", node->key);
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    if (balance < -1) {
        if (key > node->right->key) {
            printf("Unbalanced at node %d: BF = %d → RR case (insertion in right-right)\n", node->key, balance);
            printf("RR Rotation at node %d\n", node->key);
            return rotateLeft(node);
        }
        if (key < node->right->key) {
            printf("Unbalanced at node %d: BF = %d → RL case (insertion in right-left)\n", node->key, balance);
            printf("RL Rotation at node %d\n", node->key);
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    return node;
}



// 중위 순회
void inorder(Node *root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// 트리 출력 (들여쓰기 기반 구조 출력)
void printTree(Node *root, int level) {
    if (root == NULL) return;

    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++) printf("    ");
    printf("%d\n", root->key);
    printTree(root->left, level + 1);
}

int main() {
    Node* root = NULL;
    int keys[] = {5, 26, 31, 36, 14, 9, 19, 33, 23, 20};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        printf("\nInserting %d...\n", keys[i]);
        root = insert(root, keys[i]);
        printTree(root, 0);
    }

    printf("\nInorder traversal: ");
    inorder(root);
    printf("\n");

    return 0;
}
