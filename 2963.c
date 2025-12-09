
#include <stdio.h>

int main() {
    int n, votos_carlos, votos;
    int carlos_venceu = 1;
    
    scanf("%d", &n);
    scanf("%d", &votos_carlos);
    
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &votos);
        if (votos > votos_carlos) {
            carlos_venceu = 0;
        }
    }
    
    if (carlos_venceu) {
        printf("S\n");
    } else {
        printf("N\n");
    }
    
    return 0;
}
