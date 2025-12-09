#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 1005

int adj[MAXN][MAXN];
int grau[MAXN];
int match[MAXN];
bool visited[MAXN];
int n;

bool dfs(int u) {
    for (int i = 0; i < grau[u]; i++) {
        int v = adj[u][i];
        if (visited[v]) continue;
        visited[v] = true;
        
        if (match[v] == -1 || dfs(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int max_matching() {
    memset(match, -1, sizeof(match));
    int result = 0;
    
    for (int u = 1; u <= n; u++) {
        memset(visited, false, sizeof(visited));
        if (dfs(u)) {
            result++;
        }
    }
    
    return result;
}

int main() {
    int m;
    
    while (scanf("%d %d", &n, &m) != EOF) {
        memset(grau, 0, sizeof(grau));
        
        for (int i = 0; i < m; i++) {
            int p, f;
            scanf("%d %d", &p, &f);
            adj[p][grau[p]++] = f;
        }
        
        int matching = max_matching();
        printf("%d\n", n - matching);
    }
    
    return 0;
}
