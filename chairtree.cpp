#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
#define mid (((l) + (r)) >> 1)
const int N = 301000;
struct S {
    struct Q {
        Q *l, *r;
        int s, c;
    }key[N << 4];
    Q *root[N];
    Q *p;
    inline void init (int n) {
        p = key;
        root[0] = build(1, n);
    }
    inline Q* getnew (int _c) {
        return p->s = 1, p->c = _c, p ++;
    }
    inline Q* getnew (Q* a, Q* b) {
        return p->l = a, p->r = b, p->s = a->s + b->s, p->c = a->c + b->c, p ++;
    }
    inline Q* build (int l, int r) {
        if (l == r) return getnew (0);
        return getnew (build (l, (l + r) >> 1), build (((l + r) >> 1) + 1, r));
    }
    inline Q* inc (Q* t, int i) {
        if (t->s == 1) return getnew (t->c + 1);
        if (i <= t->l->s) return getnew (inc (t->l, i), t->r);
        else return getnew (t->l, inc (t->r, i - t->l->s));
    }
    inline int query (Q* a, Q* b, int k) {
        if (a->s == 1) return 1;
        int t = b->l->c - a->l->c;
        if (k <= t) return query (a->l, b->l, k);
        else return a->l->s + query (a->r, b->r, k - t);
    }
}seg;
int n, m, a[N], b[N], c[N], b_c;
int main() {
    freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++)
        scanf("%d", &a[i]), b[++ b_c] = a[i];
    sort(b + 1, b + 1 + b_c);
    b_c = unique(b + 1, b + 1 + b_c) - (b + 1);
    for (int i = 1; i <= n; i ++)
        c[i] = lower_bound(b + 1, b + 1 + b_c, a[i]) - b;
    seg.init(b_c);
    for (int i = 1; i <= n; i ++)
        seg.root[i] = seg.inc(seg.root[i - 1], c[i]);
    for (int i = 1, x, y, k; i <= m; i ++) {
        scanf("%d%d%d", &x, &y, &k);
        printf("%d\n", b[seg.query(seg.root[x - 1], seg.root[y], k)]);
    }
    return 0;
}
