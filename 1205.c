#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct {
    int v;
    double prob;
    int bullets;
} State;

int adj[MAXN][MAXN];
int grau[MAXN];
int snipers[MAXN];
int n, m, k;
double p;

typedef struct {
    double prob;
    int bullets;
} Info;

Info best[MAXN];
bool visited[MAXN];

double max_prob(int start, int end) {
    // Inicializa
    for (int i = 1; i <= n; i++) {
        best[i].prob = 0.0;
        best[i].bullets = -1;
        visited[i] = false;
    }
    
    best[start].prob = 1.0;
    best[start].bullets = k;
    
    // Dijkstra modificado para maximizar probabilidade
    for (int iter = 0; iter < n; iter++) {
        int u = -1;
        double max_p = -1.0;
        
        // Encontra vértice não visitado com maior probabilidade
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && best[i].prob > max_p) {
                max_p = best[i].prob;
                u = i;
            }
        }
        
        if (u == -1 || max_p == 0.0) break;
        visited[u] = true;
        
        // Atualiza vizinhos
        for (int i = 0; i < grau[u]; i++) {
            int v = adj[u][i];
            if (visited[v]) continue;
            
            int bullets_needed = snipers[v];
            int bullets_after = best[u].bullets - bullets_needed;
            
            // Verifica se tem balas suficientes
            if (bullets_after < 0) continue;
            
            // Calcula nova probabilidade
            double new_prob = best[u].prob * pow(p, bullets_needed);
            
            // Atualiza se for melhor
            if (new_prob > best[v].prob) {
                best[v].prob = new_prob;
                best[v].bullets = bullets_after;
            }
        }
    }
    
    return best[end].prob;
}

int main() {
    int a, start, dest;
    
    while (scanf("%d %d %d %lf", &n, &m, &k, &p) != EOF) {
        // Inicializa grafo e atiradores
        memset(grau, 0, sizeof(grau));
        memset(snipers, 0, sizeof(snipers));
        
        // Lê arestas
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u][grau[u]++] = v;
            adj[v][grau[v]++] = u;
        }
        
        // Lê atiradores
        scanf("%d", &a);
        for (int i = 0; i < a; i++) {
            int pos;
            scanf("%d", &pos);
            snipers[pos]++;
        }
        
        // Lê origem e destino
        scanf("%d %d", &start, &dest);
        
        // Desconta atiradores da origem do número de balas disponíveis
        int bullets_at_start = k - snipers[start];
        if (bullets_at_start < 0) {
            printf("0.000\n");
            continue;
        }
        
        // Calcula probabilidade inicial (matar atiradores na origem)
        double prob_start = pow(p, snipers[start]);
        
        // Zera atiradores na origem para não contar novamente
        int temp = snipers[start];
        snipers[start] = 0;
        k = bullets_at_start;
        
        // Encontra melhor caminho
        double result = max_prob(start, dest) * prob_start;
        
        // Restaura
        snipers[start] = temp;
        
        printf("%.3lf\n", result);
    }
    
    return 0;
}
