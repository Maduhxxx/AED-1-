#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int n, m, b;
int min_lamps;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void calculate_lighting() {
    memset(lit, false, sizeof(lit));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (lamp[i][j]) {
                lit[i][j] = true;
                
                // Ilumina nas 4 direções
                for (int d = 0; d < 4; d++) {
                    int ni = i + dx[d];
                    int nj = j + dy[d];
                    
                    while (ni >= 1 && ni <= n && nj >= 1 && nj <= m && board[ni][nj] == -2) {
                        lit[ni][nj] = true;
                        ni += dx[d];
                        nj += dy[d];
                    }
                }
            }
        }
    }
}

bool is_valid() {
    // Verifica se todas as células vazias estão iluminadas
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (board[i][j] == -2 && !lit[i][j]) {
                return false;
            }
        }
    }
    
    // Verifica se nenhuma lâmpada ilumina outra
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (lamp[i][j]) {
                for (int d = 0; d < 4; d++) {
                    int ni = i + dx[d];
                    int nj = j + dy[d];
                    
                    while (ni >= 1 && ni <= n && nj >= 1 && nj <= m && board[ni][nj] == -2) {
                        if (lamp[ni][nj]) return false;
                        ni += dx[d];
                        nj += dy[d];
                    }
                }
            }
        }
    }
    
    // Verifica restrições de barreiras numeradas
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (board[i][j] >= 0) {
                int count = 0;
                for (int d = 0; d < 4; d++) {
                    int ni = i + dx[d];
                    int nj = j + dy[d];
                    if (ni >= 1 && ni <= n && nj >= 1 && nj <= m && lamp[ni][nj]) {
                        count++;
                    }
                }
                if (count != board[i][j]) return false;
            }
        }
    }
    
    return true;
}

void backtrack(int pos, int lamp_count) {
    if (lamp_count >= min_lamps) return; // Poda
    
    if (pos > n * m) {
        calculate_lighting();
        if (is_valid()) {
            if (lamp_count < min_lamps) {
                min_lamps = lamp_count;
            }
        }
        return;
    }
    
    int i = (pos - 1) / m + 1;
    int j = (pos - 1) % m + 1;
    
    if (board[i][j] != -2) {
        backtrack(pos + 1, lamp_count);
    } else {
        // Não coloca lâmpada
        lamp[i][j] = false;
        backtrack(pos + 1, lamp_count);
        
        // Coloca lâmpada
        lamp[i][j] = true;
        backtrack(pos + 1, lamp_count + 1);
        lamp[i][j] = false;
    }
}

int main() {
    while (scanf("%d %d", &n, &m) && (n || m)) {
        // Inicializa tabuleiro como vazio
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                board[i][j] = -2; // vazio
            }
        }
        
        scanf("%d", &b);
        for (int i = 0; i < b; i++) {
            int r, c, k;
            scanf("%d %d %d", &r, &c, &k);
            board[r][c] = k;
        }
        
        memset(lamp, false, sizeof(lamp));
        min_lamps = INF;
        
        backtrack(1, 0);
        
        if (min_lamps == INF) {
            printf("No solution\n");
        } else {
            printf("%d\n", min_lamps);
        }
    }
    
    return 0;
}
