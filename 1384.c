#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

typedef struct {
    int x, y;
    int dist;
} Node;

typedef struct {
    Node *data;
    int size;
    int cap;
} Heap;

Heap* createHeap(int cap){
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->data = (Node*)malloc(sizeof(Node)*cap);
    h->size = 0;
    h->cap = cap;
    return h;
}

void swap(Node *a, Node *b){
    Node t = *a; *a = *b; *b = t;
}

void push(Heap *h, int x, int y, int dist){
    int i = h->size++;
    h->data[i].x = x;
    h->data[i].y = y;
    h->data[i].dist = dist;
    
    while(i > 0){
        int p = (i-1)/2;
        if(h->data[p].dist <= h->data[i].dist) break;
        swap(&h->data[p], &h->data[i]);
        i = p;
    }
}

Node pop(Heap *h){
    Node ret = h->data[0];
    h->data[0] = h->data[--h->size];

    int i = 0;
    while(1){
        int l = 2*i+1, r = 2*i+2, small = i;
        if(l < h->size && h->data[l].dist < h->data[small].dist) small = l;
        if(r < h->size && h->data[r].dist < h->data[small].dist) small = r;
        if(small == i) break;
        swap(&h->data[i], &h->data[small]);
        i = small;
    }
    return ret;
}

int dijkstra(int C, int R, int sx, int sy, int tx, int ty, 
             int mat[R+1][C+1], int blocked[R+1][C+1]) {

    static int dist[1002][1002];

    int dx[8] = {-3,-3,-2,-2, 2, 2, 3, 3};
    int dy[8] = {-2, 2,-3, 3,-3, 3,-2, 2};

    for(int i=1;i<=R;i++)
        for(int j=1;j<=C;j++)
            dist[i][j] = INF;

    Heap *h = createHeap(C*R + 10);

    dist[sy][sx] = 0;
    push(h, sx, sy, 0);

    while(h->size){
        Node u = pop(h);
        int x = u.x, y = u.y;

        if(u.dist > dist[y][x]) continue;
        if(x == tx && y == ty) return u.dist;

        for(int k=0;k<8;k++){
            int nx = x + dx[k];
            int ny = y + dy[k];

            if(nx < 1 || nx > C || ny < 1 || ny > R) continue;
            if(blocked[ny][nx]) continue;

            int cost = mat[ny][nx];
            int nd = u.dist + cost;

            if(nd < dist[ny][nx]){
                dist[ny][nx] = nd;
                push(h, nx, ny, nd);
            }
        }
    }
    return -1;
}

int main() {
    int C, R;
    while(1) {
        scanf("%d %d", &C, &R);
        if(C == 0 && R == 0) break;

        int sx, sy, tx, ty;
        scanf("%d %d %d %d", &sx, &sy, &tx, &ty);

        int mat[R+1][C+1];
        for(int i=1;i<=R;i++)
            for(int j=1;j<=C;j++)
                scanf("%d", &mat[i][j]);

        int blocked[R+1][C+1];
        for(int i=1;i<=R;i++)
            for(int j=1;j<=C;j++)
                blocked[i][j] = 0;

        int W;
        scanf("%d", &W);
        while(W--){
            int c1, r1, c2, r2;
            scanf("%d %d %d %d", &c1, &r1, &c2, &r2);
            for(int y = r1; y <= r2; y++)
                for(int x = c1; x <= c2; x++)
                    blocked[y][x] = 1;
        }

        int ans = dijkstra(C, R, sx, sy, tx, ty, mat, blocked);

        if(ans < 0)
            ;  
        else
            ;   
    }

    return 0;
}
