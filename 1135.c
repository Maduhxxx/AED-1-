#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 100005

typedef struct Edge {
    int to;
    long long weight;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
int parent[MAXN];
long long dist_from_root[MAXN];
int depth[MAXN];
int n;

void add_edge(int u, int v, long long w) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = v;
    e->weight = w;
    e->next = adj[u];
    adj[u] = e;
    
    e = (Edge*)malloc(sizeof(Edge));
    e->to = u;
    e->weight = w;
    e->next = adj[v];
    adj[v] = e;
}

void dfs(int u, int p, long long dist, int d) {
    parent[u] = p;
    dist_from_root[u] = dist;
    depth[u] = d;
    
    for (Edge* e = adj[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v != p) {
            dfs(v, u, dist + e->weight, d + 1);
        }
    }
}

int lca(int u, int v) {
    // Leva ambos para a mesma profundidade
    while (depth[u] > depth[v]) {
        u = parent[u];
    }
    while (depth[v] > depth[u]) {
        v = parent[v];
    }
    
    // Sobe até encontrar o ancestral comum
    while (u != v) {
        u = parent[u];
        v = parent[v];
    }
    
    return u;
}

long long query(int s, int t) {
    int ancestor = lca(s, t);
    return dist_from_root[s] + dist_from_root[t] - 2 * dist_from_root[ancestor];
}

void free_graph() {
    for (int i = 0; i < n; i++) {
        Edge* e = adj[i];
        while (e != NULL) {
            Edge* next = e->next;
            free(e);
            e = next;
        }
        adj[i] = NULL;
    }
}

int main() {
    while (scanf("%d", &n) && n != 0) {
        // Inicializa
        memset(adj, 0, sizeof(adj));
        memset(parent, -1, sizeof(parent));
        
        // Lê a árvore
        for (int i = 1; i < n; i++) {
            int a;
            long long l;
            scanf("%d %lld", &a, &l);
            add_edge(a, i, l);
        }
        
        // Pré-processa a árvore com DFS da raiz (formigueiro 0)
        dfs(0, -1, 0, 0);
        
        // Processa consultas
        int q;
        scanf("%d", &q);
        
        for (int i = 0; i < q; i++) {
            int s, t;
            scanf("%d %d", &s, &t);
            
            if (i > 0) printf(" ");
            printf("%lld", query(s, t));
        }
        printf("\n");
        
        // Libera memória
        free_graph();
    }
    
    return 0;
}
