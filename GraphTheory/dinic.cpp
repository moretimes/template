int S, T;
const int N = 500, M = 501000, INF = 0x3f3f3f3f;
struct Flow {
    int key[M], next[M], head[N], f[M], cnt, q[N], d[N];
    void init() {
        cnt = 0;
        memset (head, -1, sizeof head);
    }
    inline void add (int x, int y, int F)
    {
        key[cnt] = y;
        next[cnt] = head[x];
        f[cnt] = F;
        head[x] = cnt ++;

        key[cnt] = x;
        next[cnt] = head[y];
        f[cnt] = 0;
        head[y] = cnt ++;
    }
    bool SPFA ()
    {
        memset (d, -1, sizeof d);
        int h = 1, t = 2;
        q[1] = S;
        d[S] = 0;
        while (h < t)
        {
            int u = q[h ++];
            for (int i = head[u]; ~ i; i = next[i])
                if (f[i] && d[key[i]] == -1)
                    d[key[i]] = d[u] + 1, q[t ++] = key[i];
        }
        return d[T] != -1;
    }
    int DFS (int a, int b)
    {
        if (a == T)
            return b;
        int t (0), r (0);
        for (int i = head[a]; ~ i && r < b; i = next[i])
            if (f[i] && d[key[i]] == d[a] + 1)
            {
                t = DFS (key[i], min (b - r, f[i]));
                f[i] -= t, r += t, f[i ^ 1] += t;
            }
        if (!r) d[a] = -1;
        return r;
    }
    int work() {
        int z(0);
        while(SPFA())
            z += DFS(S, INF);
        return z;
    }
}flow;

