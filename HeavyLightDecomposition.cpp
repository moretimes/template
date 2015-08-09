const int N = 500000;
int p[N], s[N], d[N], tid[N], top[N], son[N], key[N], next[N], len[N], head[N], cnt, tid_c, w[N];
int a[N], b[N], c[N];
int n;
inline void add (int x, int y, int w) {
    key[cnt] = y;
    next[cnt] = head[x];
    len[cnt] = w;
    head[x] = cnt ++;
}
void D1 (int x, int fa) {
    p[x] = fa;
    d[x] = d[fa] + 1;
    s[x] = 1;
    int t1 (0), t2 (0);
    for (int i = head[x]; ~ i; i = next[i])
    {
        if (key[i] == fa) continue;
        D1 (key[i], x);
        s[x] += s[key[i]];
        if (s[key[i]] > t1)
            t1 = s[key[i]], t2 = key[i];
    }
    son[x] = t2;
}
void D2 (int x, int TOP) {
    tid[x] = ++ tid_c;
    top[x] = TOP;
    if (son[x]) D2 (son[x], TOP);
    for (int i = head[x]; ~ i; i = next[i])
    {
        if (key[i] == p[x] || key[i] == son[x]) continue;
        D2 (key[i], key[i]);
    }
}
void D3 (int x, int fa) {
    for (int i = head[x]; ~ i; i = next[i])
    {
        if (key[i] == fa) continue;
        D3 (key[i], x);
        w[tid[key[i]]] = len[i];
    }
}
int ask (int x, int y) {
    int z (0);
    while (top[x] != top[y])
    {
        if (d[top[x]] < d[top[y]])
            swap (x, y);
        z = max (z, seg.query (tid[top[x]], tid[x], 1, n, 1));
        x = p[top[x]];
    }
    if (d[x] > d[y])
        swap (x, y);
    return max (z, seg.query (tid[son[x]], tid[y], 1, n, 1));
}
void Cover(int x, int y, int v) {
    while(top[x] != top[y]) {
        if (d[top[x]] < d[top[y]])
            swap(x, y);
        seg.Cover(tid[top[x]], tid[x], v, 1, n, 1);
        x = p[top[x]];
    }
    if (d[x] > d[y])
        swap(x, y);
    seg.Cover(tid[son[x]], tid[y], v, 1, n, 1);
}
void Add(int x, int y, int v) {
    while(top[x] != top[y]) {
        if (d[top[x]] < d[top[y]])
            swap(x, y);
        seg.Add(tid[top[x]], tid[x], v, 1, n, 1);
        x = p[top[x]];
    }
    if (d[x] > d[y])
        swap(x, y);
    seg.Add(tid[son[x]], tid[y], v, 1, n, 1);
}
int main () {
    freopen("in", "r", stdin);
    tid_c = 0;cnt = 0;
    memset (head, -1, sizeof head);
    scanf ("%d", &n);
    for (int i = 1; i <= n - 1; i ++)
        scanf ("%d%d%d", &a[i], &b[i], &c[i]), add (a[i], b[i], c[i]), add (b[i], a[i], c[i]);
    w[1] = 0;d[1] = 0;
    D1 (1, 1);D2 (1, 1);D3 (1, 1);
    seg.build(1, n, 1, w);
    char op[15];
    while(scanf("%s", op), op[0] != 'S') {
        int x, y, v;
        if (op[0] == 'M') {
            scanf("%d%d", &x, &y);
            printf("%d\n", ask(x, y));
        }
        if (op[0] == 'C' && op[1] == 'o') {
            scanf("%d%d%d", &x, &y, &v);
            Cover(x, y, v);
        }
        if (op[0] == 'A') {
            scanf("%d%d%d", &x, &y, &v);
            Add(x, y, v);
        }
    }
    return 0;
}
