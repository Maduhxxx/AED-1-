#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;
const ll INFLL = (ll)1e15;

typedef struct { int to; int next; } Edge;

// heap item
typedef struct { int node; ll dist; } Item;

Edge *edges;
int *head;
int edge_cnt;

// adiciona aresta (lista encadeada)
void add_edge(int u, int v) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

/* heap mínimo simples */
Item *heap;
int hsize;

void heap_push(int node, ll dist) {
    int i = hsize++;
    heap[i].node = node;
    heap[i].dist = dist;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].dist <= heap[i].dist) break;
        Item tmp = heap[p]; heap[p] = heap[i]; heap[i] = tmp;
        i = p;
    }
}
Item heap_pop() {
    Item ret = heap[0];
    heap[0] = heap[--hsize];
    int i = 0;
    while (1) {
        int l = 2*i + 1, r = 2*i + 2, mn = i;
        if (l < hsize && heap[l].dist < heap[mn].dist) mn = l;
        if (r < hsize && heap[r].dist < heap[mn].dist) mn = r;
        if (mn == i) break;
        Item tmp = heap[i]; heap[i] = heap[mn]; heap[mn] = tmp;
        i = mn;
    }
    return ret;
}

int main() {
    ios: ;
    int M, N, G, K;
    while (scanf("%d %d %d %d", &M, &N, &G, &K) == 4) {
        if (M==0 && N==0 && G==0 && K==0) break;

        // lê magias
        int *cost = malloc(M * sizeof(int));
        int *dmg  = malloc(M * sizeof(int));
        for (int i = 0; i < M; ++i) scanf("%d %d", &cost[i], &dmg[i]);

        // monta grafo com G arestas (bidirecionais)
        // aloca 2*G edges
        edges = malloc((2LL * G + 5) * sizeof(Edge));
        head  = malloc((N + 1) * sizeof(int));
        for (int i = 1; i <= N; ++i) head[i] = -1;
        edge_cnt = 0;
        for (int i = 0; i < G; ++i) {
            int a,b; scanf("%d %d", &a, &b);
            add_edge(a,b);
            add_edge(b,a);
        }

        // DP unbounded knapsack: custo mínimo para dano exato d (0..1000)
        const int MAXV = 1000;
        ll *kill = malloc((MAXV+1) * sizeof(ll));
        for (int i = 0; i <= MAXV; ++i) kill[i] = INFLL;
        kill[0] = 0;
        // unbounded knapsack (forward per magia funciona)
        for (int i = 0; i < M; ++i) {
            int w = dmg[i];
            int c = cost[i];
            for (int v = w; v <= MAXV; ++v) {
                if (kill[v - w] + c < kill[v]) kill[v] = kill[v - w] + c;
            }
        }
        // Agora queremos custo mínimo para causar >= v de dano:
        // suffix minimum: para v from MAXV-1 downto 0: kill[v] = min(kill[v], kill[v+1])
        for (int v = MAXV-1; v >= 0; --v) {
            if (kill[v+1] < kill[v]) kill[v] = kill[v+1];
        }

        // room cost (soma dos monstros no mesmo salão)
        ll *room_cost = malloc((N+1) * sizeof(ll));
        for (int i = 1; i <= N; ++i) room_cost[i] = 0;

        for (int i = 0; i < K; ++i) {
            int sala, vida; scanf("%d %d", &sala, &vida);
            if (vida < 0) vida = 0;
            if (vida > MAXV) vida = MAXV; // vidas >1000 não existem segundo enunciado, mas só por segurança
            room_cost[sala] += kill[vida];
            // note: se kill[vida] == INFLL, soma ficará grande (INFLL)
        }

        // Dijkstra sobre nós 1..N, custo ao entrar em nó v = room_cost[v]
        ll *dist = malloc((N+1)*sizeof(ll));
        char *vis = malloc((N+1)*sizeof(char));
        for (int i = 1; i <= N; ++i) { dist[i] = INFLL; vis[i]=0; }

        heap = malloc((N+5) * sizeof(Item));
        hsize = 0;

        // Partida no salão 1: antes de sair, precisa limpar sala 1,
        // portanto custo inicial = room_cost[1]
        dist[1] = room_cost[1];
        heap_push(1, dist[1]);

        ll answer = -1;
        while (hsize > 0) {
            Item it = heap_pop();
            int u = it.node;
            if (vis[u]) continue;
            vis[u] = 1;
            if (u == N) { answer = dist[u]; break; }
            // relaxa arestas
            for (int e = head[u]; e != -1; e = edges[e].next) {
                int v = edges[e].to;
                if (vis[v]) continue;
                // para ir a v, precisamos pagar room_cost[v] ao entrar (ou antes de sair de v)
                if (dist[u] + room_cost[v] < dist[v]) {
                    dist[v] = dist[u] + room_cost[v];
                    heap_push(v, dist[v]);
                }
            }
        }

        if (answer >= INFLL/2) printf("-1\n");
        else printf("%lld\n", answer);

        // libera memória
        free(cost); free(dmg);
        free(edges); free(head);
        free(kill);
        free(room_cost);
        free(dist); free(vis);
        free(heap);
    }

    return 0;
}
