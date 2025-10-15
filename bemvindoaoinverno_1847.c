#include <stdio.h>

int main() {
    int A, B, C;
    
    // Leitura das temperaturas dos três dias
    scanf("%d %d %d", &A, &B, &C);

    if (A > B && B <= C) {
        printf(":)\n"); // Primeira figura
    } else if (A < B && B >= C) {
        printf(":(\n"); // Segunda figura
    } else if (A < B && B < C && (C - B) < (B - A)) {
        printf(":(\n"); // Terceira figura
    } else if (A < B && B < C && (C - B) >= (B - A)) {
        printf(":)\n"); // Quarta figura
    } else if (A > B && B > C && (C - B) > (B - A)) {
        printf(":)\n"); // Quinta figura
    } else if (A > B && B > C && (C - B) <= (B - A)) {
        printf(":(\n"); // Sexta figura
    } else if (A == B && B < C) {
        printf(":)\n"); // Sétima figura
    } else if (A == B && B >= C) {
        printf(":(\n"); // Oitava figura
    }
    
    return 0;
}
