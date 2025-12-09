#include <stdio.h>
#include <string.h>

#define MAXN 21
#define INF 1000000000
#define TIME_LIMIT 420

int n;
int visit_time[MAXN];
int travel_time[MAXN][MAXN];
int dp[1 << MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int popcount(int mask) {
    int count = 0;
    while (mask) {
        count += mask & 1;
        mask >>= 1;
    }
    return count;
}

int main() {
    while (scanf("%d", &n) && n != 0) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &visit_time[i]);
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &travel_time[i][j]);
            }
        }
        
        int max_mask = (1 << n);
        
        for (int mask = 0; mask < max_mask; mask++) {
            for (int i = 0; i < n; i++) {
                dp[mask][i] = INF;
            }
        }
        
        for (int i = 0; i < n; i++) {
            dp[1 << i][i] = visit_time[i];
        }
        
        for (int mask = 0; mask < max_mask; mask++) {
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) continue;
                if (dp[mask][i] == INF) continue;
                
                for (int j = 0; j < n; j++) {
                    if (mask & (1 << j)) continue;
                    
                    int new_mask = mask | (1 << j);
                    int new_time = dp[mask][i] + travel_time[i][j] + visit_time[j];
                    
                    dp[new_mask][j] = min(dp[new_mask][j], new_time);
                }
            }
        }
        
        int max_museums = 0;
        for (int mask = 0; mask < max_mask; mask++) {
            for (int i = 0; i < n; i++) {
                if (dp[mask][i] <= TIME_LIMIT) {
                    int museums = popcount(mask);
                    if (museums > max_museums) {
                        max_museums = museums;
                    }
                }
            }
    }
    
    return 0;
}
