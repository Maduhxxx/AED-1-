#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 605
#define MAXM 405

int n, m;
int cost[MAXN];
int benefit[MAXM];
int category_size[MAXM];
int category[MAXM][MAXN];
bool vodka_bought[MAXN];
bool category_selected[MAXM];
int max_profit;

int calculate_profit() {
    int total_benefit = 0;
    int total_cost = 0;
    
    // Calcula custo das vodkas compradas
    for (int j = 1; j <= n; j++) {
        if (vodka_bought[j]) {
            total_cost += cost[j];
        }
    }
    
    // Calcula benefício das categorias completas
    for (int i = 1; i <= m; i++) {
        if (category_selected[i]) {
            bool complete = true;
            for (int k = 0; k < category_size[i]; k++) {
                if (!vodka_bought[category[i][k]]) {
                    complete = false;
                    break;
                }
            }
            if (complete) {
                total_benefit += benefit[i];
            }
        }
    }
    
    return total_benefit - total_cost;
}

void backtrack_categories(int idx, int current_profit, int potential_benefit) {
    if (idx > m) {
        if (current_profit > max_profit) {
            max_profit = current_profit;
        }
        return;
    }
    
    // Poda: se mesmo pegando todos os benefícios restantes não melhorar, retorna
    if (current_profit + potential_benefit <= max_profit) {
        return;
    }
    
    // Não seleciona a categoria idx
    backtrack_categories(idx + 1, current_profit, potential_benefit - benefit[idx]);
    
    // Seleciona a categoria idx
    category_selected[idx] = true;
    
    // Marca as vodkas necessárias e calcula custo adicional
    bool vodkas_added[MAXN] = {false};
    int added_cost = 0;
    
    for (int k = 0; k < category_size[idx]; k++) {
        int v = category[idx][k];
        if (!vodka_bought[v]) {
            vodka_bought[v] = true;
            vodkas_added[v] = true;
            added_cost += cost[v];
        }
    }
    
    backtrack_categories(idx + 1, current_profit + benefit[idx] - added_cost, 
                        potential_benefit - benefit[idx]);
    
    // Desfaz as mudanças
    category_selected[idx] = false;
    for (int k = 0; k < category_size[idx]; k++) {
        int v = category[idx][k];
        if (vodkas_added[v]) {
            vodka_bought[v] = false;
        }
    }
}

int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        // Lê custos das vodkas
        for (int j = 1; j <= n; j++) {
            scanf("%d", &cost[j]);
        }
        
        // Lê tamanhos das categorias
        for (int i = 1; i <= m; i++) {
            scanf("%d", &category_size[i]);
        }
        
        // Lê categorias
        int total_benefit = 0;
        for (int i = 1; i <= m; i++) {
            scanf("%d", &benefit[i]);
            total_benefit += benefit[i];
            for (int k = 0; k < category_size[i]; k++) {
                scanf("%d", &category[i][k]);
            }
        }
        
        // Inicializa
        memset(vodka_bought, false, sizeof(vodka_bought));
        memset(category_selected, false, sizeof(category_selected));
        max_profit = 0; // Não comprar nada também é uma opção
        
        // Backtracking
        backtrack_categories(1, 0, total_benefit);
        
 
    }
    
    return 0;
}
