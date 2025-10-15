#include <stdio.h>
#include <string.h>

#define MAX_N 100005

int main() {
    int N, D;

    while (scanf("%d %d", &N, &D) && (N != 0 || D != 0)) {
        char numero[MAX_N];
        scanf("%s", numero);

        char pilha[MAX_N];
        int topo = 0, digitos_restantes = N - D;

        for (int i = 0; i < N; i++) {
            // Enquanto o topo da pilha não estiver vazio, houver dígitos
            // suficientes para remover e o dígito no topo for menor que o atual
            while (topo > 0 && pilha[topo - 1] < numero[i] && D > 0) {
                topo--;  // Removemos o dígito do topo da pilha
                D--;
            }
            // Adicionamos o dígito atual à pilha, se ainda pudermos adicionar
            if (topo < digitos_restantes) {
                pilha[topo++] = numero[i];
            } else {
                D--;  // Se não puder adicionar, contamos como um dígito removido
            }
        }

        // Adiciona o caractere nulo ao final da pilha para formar a string
        pilha[topo] = '\0';

        // Imprime o maior número possível
        printf("%s\n", pilha);
    }

    return 0;
}
