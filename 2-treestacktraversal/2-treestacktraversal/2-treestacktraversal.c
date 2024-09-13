#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
}TreeNode;

typedef struct Stack {
    TreeNode* node;
    struct Stack* next;
}Stack;

Stack* init() {
    return NULL;
}

int isempty(Stack* stack) {
    return stack == NULL;
}

void push(Stack** stack, TreeNode* node) {
    Stack* new_node = (Stack*)malloc(sizeof(Stack));
    new_node->node = node;
    new_node->next = *stack;
    *stack = new_node;
    printf("push(%d) ", node->data);
}

TreeNode* pop(Stack** stack) {
    if (isempty(*stack)) return NULL;
    Stack* temp = *stack;
    TreeNode* node = temp->node;
    *stack = temp->next;
    free(temp);
    printf("pop(%d) ", node->data);  // pop 출력 추가
    return node;
}

void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode;
    }
    else {
        node->right = newNode;
    }
}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);

    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);

    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);

    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);

    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);

    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);

    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

void LinkPreOrder(TreeNode* root) {
    printf("LinkedPreOrder: \n");
    Stack* stack = init();
    TreeNode* current = root;

    while (current != NULL || !isempty(stack)) {
        while (current != NULL) {
            printf("visit(%d) ", current->data);  // visit 출력
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        current = current->right;
        printf("\n");
    }
}

void LinkInOrder(TreeNode* root) {
    printf("LinkedInOrder: \n");
    Stack* stack = init();
    TreeNode* current = root;

    while (current != NULL || !isempty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }

        current = pop(&stack);
        printf("visit(%d) ", current->data);
        current = current->right;
        printf("\n");
    }
}

void LinkPostOrder(TreeNode* root) {
    printf("LinkedPostOrder: \n");
    Stack* stack1 = init();
    Stack* stack2 = init();
    TreeNode* current = root;

    if (current == NULL) return;

    push(&stack1, current);

    while (!isempty(stack1)) {
        current = pop(&stack1);
        push(&stack2, current);

        if (current->left) push(&stack1, current->left);
        if (current->right) push(&stack1, current->right);
        printf("\n");
    }

    while (!isempty(stack2)) {
        current = pop(&stack2);
        printf("visit(%d) ", current->data);
    }
}

void LinkOrders(TreeNode* root) {
    LinkPreOrder(root);
    printf("\n");
    LinkInOrder(root);
    printf("\n");
    LinkPostOrder(root);
}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = root->right = NULL;

    GenerateLinkTree(root);
    LinkOrders(root);
    return 0;
}