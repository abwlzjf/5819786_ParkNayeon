#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

typedef struct QueueNode {
	TreeNode* data;
	struct QueueNode* next;
}QueueNode;

typedef struct LinkedQueueType {
	QueueNode* front, * rear;
}LinkedQueueType;

void init(LinkedQueueType* q) {
	q->front = q->rear = NULL;
}

int is_empty(LinkedQueueType* q) {
	return (q->front == NULL);
}

void enqueue(LinkedQueueType* q, TreeNode* data) {
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	newNode->data = data;
	newNode->next = NULL;

	if (is_empty(q)) {
		q->front = newNode;
	}
	else
		q->rear->next = newNode;
	q->rear = newNode;
}

TreeNode* dequeue(LinkedQueueType* q) {
	if (is_empty(q)) {
		fprintf(stderr, "큐가 비어있습니다.\n");
		exit(1);
	}
	QueueNode* temp = q->front;
	TreeNode* data = temp->data;
	q->front = q->front->next;
	if (q->front == NULL) {
		q->rear = NULL;
	}
	free(temp);
	return data;
}

void PlaceNode(TreeNode* node, int direction, int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = newNode->right = NULL;

	if (direction == 0) {
		node->left = newNode;
	}
	else
		node->right = newNode;
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

void GetSumOfNodes(TreeNode* root) {
	if (root == NULL)return 0;

	int sum = 0;
	LinkedQueueType q;
	init(&q);
	enqueue(&q, root);

	while (!is_empty(&q)) {
		TreeNode* current = dequeue(&q);
		sum += current->data;

		if (current->left != NULL) {
			enqueue(&q, current->left);
		}
		if (current->right != NULL) {
			enqueue(&q, current->right);
		}
	}
	printf("Sum of nodes: %d\n", sum);
}

void GetNumberOfNodes(TreeNode* root) {
	if (root == NULL) return 0;

	int count=0;
	LinkedQueueType q;
	init(&q);
	enqueue(&q, root);

	while (!is_empty(&q)) {
		TreeNode* current = dequeue(&q);
		count++;

		if (current->left != NULL) {
			enqueue(&q, current->left);
		}
		if (current->right != NULL) {
			enqueue(&q, current->right);
		}
	}
	printf("Number of nodes: %d\n", count);
}

void GetHeightOfTree(TreeNode* root) {
	if (root == NULL) {
		printf("Height of Tree: 0\n");
		return;
	}

	int height = 0;
	LinkedQueueType q;
	init(&q);
	enqueue(&q, root);

	while (!is_empty(&q)) {
		int levelSize = 0;
		QueueNode* temp = q.front;
		while (temp != NULL) {
			levelSize++;
			temp = temp->next;
		}
		height++;
		for (int i = 0; i < levelSize; i++) {
			TreeNode* current = dequeue(&q);

			if (current->left != NULL) {
				enqueue(&q, current->left);
			}
			if (current->right != NULL) {
				enqueue(&q, current->right);
			}
		}
	}
	printf("Height of Tree: %d\n", height);
}

void GetNumberOfLeafNodes(TreeNode* root) {
	if (root == NULL) return 0;
	
	int leafcount = 0;
	LinkedQueueType q;
	init(&q);
	enqueue(&q, root);

	while (!is_empty(&q)) {
		TreeNode* current = dequeue(&q);

		if (current->left == NULL && current->right == NULL) {
			leafcount++;
		}
		if (current->left != NULL) {
			enqueue(&q, current->left);
		}
		if (current->right != NULL) {
			enqueue(&q, current->right);
		}
	}
	printf("Number of leaf nodes: %d", leafcount);
}

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;

	GenerateLinkTree(root);

	GetSumOfNodes(root);
	GetNumberOfNodes(root);
	GetHeightOfTree(root);
	GetNumberOfLeafNodes(root);

	return 0;
}