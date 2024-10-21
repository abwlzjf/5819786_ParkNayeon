#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

GraphType* create_graph() {
    return (GraphType*)malloc(sizeof(GraphType));
}

void init_graph(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            g->adj_mat[i][j] = 0;
}

void insert_vertex(GraphType* g, int v) {
    if ((g->n + 1) > MAX_VERTICES) {
        fprintf(stderr, "Over number of vertex\n");
        return;
    }
    (g->n)++;
}

void insert_edge(GraphType* g, int s, int e) {
    if (s >= g->n || e >= g->n) {
        fprintf(stderr, "Vertex number error\n");
        return;
    }
    g->adj_mat[s][e] = 1;
    g->adj_mat[e][s] = 1;
}

// 깊이 우선 탐색
void dfs(GraphType* g, int start, int target) {
    int visited[MAX_VERTICES] = { 0 };
    int stack[MAX_VERTICES], top = -1;
    int visit_count = 0;

    stack[++top] = start;
    visited[start] = 1;  // 시작점
    printf("%d ", start);

    while (top != -1) {
        int v = stack[top--];
        visit_count++;

        if (v == target) {
            printf("\n탐색 성공: %d\n", target);
            printf("방문한 노드의 수: %d\n", visit_count);
            return;
        }

        // 인접 노드 탐색
        int backtrack = 1;
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[v][i] && !visited[i]) {
                stack[++top] = v;  // 백트래킹
                stack[++top] = i; 
                visited[i] = 1;
                printf("%d ", i);
                backtrack = 0;
                break;
            }
        }

        if (backtrack && top != -1) {
            printf("%d ", stack[top]);
        }
    }
    // 탐색 실패
    printf("\n탐색 실패: %d\n", target);
    printf("방문한 노드의 수: %d\n", visit_count);
}

void bfs(GraphType* g, int start, int target) {
    int visited[MAX_VERTICES] = { 0 };
    int queue[MAX_VERTICES], front = 0, rear = 0;
    int visit_count = 0;

    queue[rear++] = start;
    visited[start] = 1;
    printf("%d ", start);

    while (front != rear) {
        int v = queue[front++];
        visit_count++;

        if (v == target) {
            printf("\n탐색 성공: %d\n", target);
            printf("방문한 노드의 수: %d\n", visit_count);
            return;
        }

        // 인접 노드 탐색
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[v][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1; 
                printf("%d ", i);
            }
        }
    }
    
    printf("\n탐색 실패: %d\n", target);
    printf("방문한 노드의 수: %d\n", visit_count);
}

void runUserInterface(GraphType* g) {
    int choice, s, e;

    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    printf(" 1\t: 깊이 우선 탐색 \tㅣ\n");
    printf(" 2\t: 너비 우선 탐색 \tㅣ\n");
    printf(" 3\t: 종료    \t\tㅣ\n");
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n");

    while (1) {
        printf("\n");
        printf("메뉴입력: ");
        scanf_s("%d", &choice);
        switch (choice) {
        case 1:
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d %d", &s, &e);
            dfs(g, s, e);
            break;
        case 2:
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d %d", &s, &e);
            bfs(g, s, e);
            break;
        case 3:
            printf("프로그램 종료\n");
            exit(0);
            break;
        default:
            printf("다시 입력.\n");
            break;
        }
    }
}

int main() {
    GraphType* g;
    g = create_graph();
    init_graph(g);
    for (int i = 0; i < 11; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 2);
    insert_edge(g, 0, 4);
    insert_edge(g, 0, 5);
    insert_edge(g, 0, 6);
    insert_edge(g, 0, 9);
    insert_edge(g, 1, 4);
    insert_edge(g, 1, 5);
    insert_edge(g, 1, 7);
    insert_edge(g, 1, 10);
    insert_edge(g, 2, 3);
    insert_edge(g, 2, 4);
    insert_edge(g, 3, 4);
    insert_edge(g, 3, 5);
    insert_edge(g, 4, 5);
    insert_edge(g, 4, 6);
    insert_edge(g, 4, 7);
    insert_edge(g, 6, 7);
    insert_edge(g, 6, 8);
    insert_edge(g, 7, 10);
    insert_edge(g, 8, 9);
    insert_edge(g, 8, 10);

    runUserInterface(g);

    free(g);
    return 0;
}