#include <stdio.h>

int main() {
    int coluna;
    char operacao;
    double matriz[12][12];
    double soma = 0.0;
    int count = 0;
    
    // Ler a coluna e a operação
    scanf("%d", &coluna);
    scanf(" %c", &operacao); // Note o espaço antes de %c para ler o caractere corretamente
    
    // Ler os elementos da matriz
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            scanf("%lf", &matriz[i][j]);
        }
    }
    
    // Processar a coluna especificada
    for (int i = 0; i < 12; i++) {
        soma += matriz[i][coluna];
        count++;
    }
    
    // Realizar a operação desejada
    if (operacao == 'S') {
        // Imprimir a soma
        printf("%.1f\n", soma);
    } else if (operacao == 'M') {
        // Imprimir a média
        printf("%.1f\n", soma / count);
    }
    
    return 0;
}
