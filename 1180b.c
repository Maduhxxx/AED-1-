#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int x[n];
    for (int i = 0; i < n; i++) scanf("%d", &x[i]);

    int *p = x;
    int *menor = x;
    int pos = 0;

    for (int i = 1; i < n; i++) {
        if (*(p + i) < *menor) {
            menor = p + i;
            pos = i;
        }
    }

    printf("Menor valor: %d\nPosicao: %d\n", *menor, pos);
    return 0;
}
