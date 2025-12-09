#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAXN 105
#define EPS 1e-9

int adj[MAXN][MAXN];
int grau[MAXN];
double prob[MAXN];
double new_prob[MAXN];
int n, a, b, c;

int main() {
    while (scanf("%d %d %d %d", &n, &a, &b, &c) != EOF) {
        // Inicializa grafo
        memset(grau, 0, sizeof(grau));
        
        // Lê as arestas
        for (int i = 0; i < n - 1; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            adj[x][grau[x]++] = y;
            adj[y][grau[y]++] = x;
        }
        
        // Inicializa probabilidades
        for (int i = 1; i <= n; i++) {
            prob[i] = 0.5; // Começa com 0.5 para todos
        }
        prob[b] = 1.0; // Hotel barato
        prob[c] = 0.0; // Hotel caro
        
        // Método iterativo para resolver o sistema de equações
        // Itera até convergir
        int max_iterations = 10000;
        for (int iter = 0; iter < max_iterations; iter++) {
            bool converged = true;
            
            // Atualiza probabilidade de cada vértice
            for (int v = 1; v <= n; v++) {
                if (v == b || v == c) {
                    new_prob[v] = prob[v]; // Mantém fixo
                    continue;
                }
                
                // Calcula nova probabilidade como média dos vizinhos
                double sum = 0.0;
                for (int i = 0; i < grau[v]; i++) {
                    int u = adj[v][i];
                    sum += prob[u];
                }
                new_prob[v] = sum / grau[v];
                
                // Verifica convergência
                if (fabs(new_prob[v] - prob[v]) > EPS) {
                    converged = false;
                }
            }
            
            // Copia novas probabilidades
            for (int v = 1; v <= n; v++) {
                prob[v] = new_prob[v];
            }
            
            if (converged) {
                break;
            }
        }
        
        printf("%.6f\n", prob[a]);
    }
    
    return 0;
}
