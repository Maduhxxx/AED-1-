#include <stdio.h>
#include <math.h>

int main() {
    int A, B, C;

    while (1) {
        // Leitura dos valores de A, B e C
        scanf("%d %d %d", &A, &B, &C);
        
        // Condição de parada
        if (A == 0 || B == 0 || C == 0) {
            break;
        }

        // Calcula a área da casa
        int areaCasa = A * B;

        // Calcula a área mínima do terreno necessária
        double areaTerrenoNecessaria = (double)areaCasa * 100 / C;

        // Calcula o lado do terreno e trunca para o menor inteiro
        int ladoTerreno = (int)sqrt(areaTerrenoNecessaria);

        // Imprime o resultado
        printf("%d\n", ladoTerreno);
    }

    return 0;
}
