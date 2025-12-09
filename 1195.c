#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 5000
#define MAX_LEN 205

int cmp(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main() {
    char buffer[MAX_LEN];
    char *words[MAX_WORDS];
    int count = 0;

    while (fgets(buffer, MAX_LEN, stdin)) {
        int i = 0;
        while (buffer[i]) {
            if (isalpha(buffer[i])) {
                char word[205];
                int j = 0;

                while (isalpha(buffer[i])) {
                    word[j++] = tolower(buffer[i]);
                    i++;
                }
                word[j] = '\0';

                // Verifica se já existe
                int exists = 0;
                for (int k = 0; k < count; k++) {
                    if (strcmp(words[k], word) == 0) {
                        exists = 1;
                        break;
                    }
                }

                // Adiciona se não existir
                if (!exists && count < MAX_WORDS) {
                    words[count] = malloc(strlen(word) + 1);
                    strcpy(words[count], word);
                    count++;
                }
            } else {
                i++;
            }
        }
    }

    // Ordenar
    qsort(words, count, sizeof(char *), cmp);

    // Aqui não imprime nada (sem printf)
    // As palavras ficam armazenadas em words[]

    // Libera a memória
    for (int i = 0; i < count; i++)
        free(words[i]);

    return 0;
}
