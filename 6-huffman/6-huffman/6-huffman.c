#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_NODES 100

// ��� ����ü ����
typedef struct Node {
    char character;
    int fre;
    struct Node* left;
    struct Node* right;
} Node;

// �켱���� ť�� ���� ��� ����ü
typedef struct MinHeap {
    int size;
    Node* array[MAX_TREE_NODES];
} MinHeap;

// ��� ����
Node* createNode(char cha, int fre) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = cha;
    newNode->fre = fre;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// �ּ� �� ����
MinHeap* createMinHeap() {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    return minHeap;
}

// �ּ� ���� ���� ���¸� ���
void printMinHeap(MinHeap* minHeap) {
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->array[i]->fre);
    }
    printf("\n");
}

// �ּ� ���� ��� �߰�
void insertMinHeap(MinHeap* minHeap, Node* newNode) {
    minHeap->array[minHeap->size++] = newNode;
    int i = minHeap->size - 1;

    // �θ�� ���Ͽ� ��ġ ����
    while (i && newNode->fre < minHeap->array[(i - 1) / 2]->fre) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = newNode;
}

// �ּ� ������ �ּ� ��� ����
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[--minHeap->size];
    int i = 0;

    // �� �Ӽ��� �����ϱ� ���� ������
    while (1) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < minHeap->size && minHeap->array[left]->fre < minHeap->array[smallest]->fre) {
            smallest = left;
        }
        if (right < minHeap->size && minHeap->array[right]->fre < minHeap->array[smallest]->fre) {
            smallest = right;
        }
        if (smallest == i) break;

        // �ڸ��� �ٲ�
        Node* tempNode = minHeap->array[i];
        minHeap->array[i] = minHeap->array[smallest];
        minHeap->array[smallest] = tempNode;
        i = smallest;
    }
    return temp;
}

// ���� ������ ������ Ʈ�� ����
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    MinHeap* minHeap = createMinHeap();

    // �� ���ڿ� �󵵷� ��带 �����Ͽ� �ּ� ���� �߰�
    for (int i = 0; i < size; i++) {
        insertMinHeap(minHeap, createNode(characters[i], frequencies[i]));
        // �ּ� �� ���¸� ���
        printMinHeap(minHeap);  // �� ��� �߰� �� �� ���¸� ���
    }

    while (minHeap->size > 1) {
        Node* left = extractMin(minHeap);
        Node* right = extractMin(minHeap);

        Node* newNode = createNode('\0', left->fre + right->fre); // ���� ���
        newNode->left = left;
        newNode->right = right;

        printf("///%d + %d -> %d\n", left->fre, right->fre, newNode->fre);
        insertMinHeap(minHeap, newNode);

        // ������ �� ���� �� ���� ���
        printMinHeap(minHeap);  // ���� ���� �ִ� �� ���� ���
    }

    return extractMin(minHeap);
}

// ������ �ڵ带 �����ϴ� ��� �Լ�
void generateHuffmanCodes(Node* root, int* code, int top) {
    if (root->left) {
        code[top] = 1; // ���� �ڽ��� 1
        generateHuffmanCodes(root->left, code, top + 1);
    }
    if (root->right) {
        code[top] = 0; // ������ �ڽ��� 0
        generateHuffmanCodes(root->right, code, top + 1);
    }
    if (!root->left && !root->right) { // ���� ����� ���
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%d", code[i]);
        }
        printf("\n");
    }
}

// ������ �ڵ带 �����ϴ� �ֿ� �Լ�
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int code[MAX_TREE_NODES], top = 0;
    generateHuffmanCodes(root, code, top);
}

int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}