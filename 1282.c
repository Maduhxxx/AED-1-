#include <stdio.h>
#include <string.h>

#define MAXN 1005
#define INF 1000000000000000000LL

long long pos[MAXN];
long long weight[MAXN];
long long dp[MAXN][MAXN];
int n, k;

long long cost(int l, int r) {
    long long total = 0;
    for (int i = l; i < r; i++) {
        total += weight[i] * (pos[r] - pos[i]);
    }
    return total;
}

int main() {
    while (scanf("%d %d", &n, &k) != EOF) {
        // Lê os montes
        for (int i = 1; i <= n; i++) {
            scanf("%lld %lld", &pos[i], &weight[i]);
        }
        
        // Inicializa DP com infinito
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = INF;
            }
        }
        
        // Caso base: 0 montes em 0 grupos tem custo 0
        dp[0][0] = 0;
        
        // DP: dp[i][j] = custo mínimo para agrupar os primeiros i montes em j grupos
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k && j <= i; j++) {
                // Tenta diferentes tamanhos para o j-ésimo grupo
                // O j-ésimo grupo vai do monte (t+1) até o monte i
                for (int t = j - 1; t < i; t++) {
                    if (dp[t][j-1] == INF) continue;
                    
                    // Custo de mover os montes de (t+1) até i para a posição i
                    long long group_cost = cost(t + 1, i);
                    
                    if (dp[t][j-1] + group_cost < dp[i][j]) {
                        dp[i][j] = dp[t][j-1] + group_cost;
                    }
                }
            }
        }
        
        printf("%lld\n", dp[n][k]);
    }
    
    return 0;
}
