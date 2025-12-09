
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 2005

int adj[MAXN][MAXN];
int adj_rev[MAXN][MAXN];
int grau[MAXN];
int grau_rev[MAXN];
bool visited[MAXN];
int n, m;

void dfs(int v, int g[], int a[][MAXN]) {
    visited[v] = true;
    for (int i = 0; i < g[v]; i++) {
        int u = a[v][i];
        if (!visited[u]) {
            dfs(u, g, a);
        }
    }
}

int count_reachable(int start, int g[], int a[][MAXN]) {
    memset(visited, false, sizeof(visited));
    dfs(start, g, a);
    
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (visited[i]) count++;
    }
    return count;
}

int main() {
    while (scanf("%d %d", &n, &m) && (n || m)) {
        // Inicializa os grafos
        memset(grau, 0, sizeof(grau));
        memset(grau_rev, 0, sizeof(grau_rev));
        
        for (int i = 0; i < m; i++) {
            int v, w, p;
            scanf("%d %d %d", &v, &w, &p);
            
            if (p == 1) {
                // Rua de mão única: V -> W
                adj[v][grau[v]++] = w;
                adj_rev[w][grau_rev[w]++] = v;
            } else {
                // Rua de mão dupla: V <-> W
                adj[v][grau[v]++] = w;
                adj[w][grau[w]++] = v;
                adj_rev[v][grau_rev[v]++] = w;
                adj_rev[w][grau_rev[w]++] = v;
            }
        }
        
        // Verifica conectividade forte usando algoritmo de Kosaraju simplificado
        // 1. Verifica se todos os vértices são alcançáveis do vértice 1
        int reachable_from_1 = count_reachable(1, grau, adj);
        
        // 2. Verifica se o vértice 1 é alcançável de todos (usando grafo reverso)
        int can_reach_1 = count_reachable(1, grau_rev, adj_rev);
        
        // Se ambos == n, então o grafo é fortemente conexo
        if (reachable_from_1 == n && can_reach_1 == n) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }
    
    return 0;
}
