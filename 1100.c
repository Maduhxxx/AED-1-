#include <stdio.h>
#include <stdlib.h>

#define V 64   // 64 casas no tabuleiro 8×8

int adj[V][8];     // até 8 movimentos por casa
int grau[V];       // grau de cada vértice
int dist[V];       // distância calculada na BFS

int dx[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
int dy[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };

int pos_to_id(char c, char d) {
    int x = c - 'a';
    int y = d - '1';
    return x * 8 + y;
}

void monta_grafo() {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            int id = x * 8 + y;
            grau[id] = 0;

            for (int k = 0; k < 8; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];

                if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
                    int nid = nx * 8 + ny;
                    adj[id][grau[id]++] = nid;
                }
            }
        }
    }
}

int bfs(int s, int t) {
    int queue[64], front = 0, back = 0;

    for (int i = 0; i < V; i++)
        dist[i] = -1;

    dist[s] = 0;
    queue[back++] = s;

    while (front < back) {
        int u = queue[front++];

        if (u == t)
            return dist[u];

        for (int i = 0; i < grau[u]; i++) {
            int v = adj[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                queue[back++] = v;
            }
        }
    }

    return -1;
}

int main() {
    monta_grafo();

    char a[3], b[3];

    while (scanf("%s %s", a, b) == 2) {
        int s = pos_to_id(a[0], a[1]);
        int t = pos_to_id(b[0], b[1]);

        int resposta = bfs(s, t);

    }

    return 0;
}
