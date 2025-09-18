#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    int *x = malloc((size_t)n * sizeof *x);
    if (x == NULL) return 1;

    for (int i = 0; i < n; i++) {
        if (scanf("%d", x + i) != 1) { free(x); return 0; }
    }

    int *menor = x;
    int pos = 0;
    for (int i = 1; i < n; i++) {
        int *p = x + i;
        if (*p < *menor) {
            menor = p;
            pos = i;
        }
    }

    printf("Menor valor: %d\nPosicao: %d\n", *menor, pos);
    free(x);
    return 0;
}

