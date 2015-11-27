#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define mid (l + r >> 1)
using namespace std;
const int N = 101000;
int n, m, a[N], b[N], b_c, sav[N];
struct S {
    struct Q {
        Q *l, *r;
        int s, c;
    }key[N << 5];
    Q* root[N];Q* p;
    Q *a[N], *b[N];
    int t1, t2;
    int sav[N];
    void init () {
        p = key;
        memset (sav, 0, sizeof sav);
    }
    Q* getnew (int _c) {
        return p->s = 1, p->c = _c, p ++;
    }
    Q* getnew (Q* a, Q* b) {
        return p->l = a, p->r = b, p->s = a->s + b->s, p->c = a->c + b->c, p ++;
    }
    Q* build (int l, int r) {
        if (l == r) return getnew (0);
        return getnew (build (l, mid), build (mid + 1, r));
    }
    Q* inc (Q* t, int i) {
        if (t->s == 1) return getnew (t->c + 1);
        if (i <= t->l->s) return getnew (inc (t->l, i), t->r);
        else return getnew (t->l, inc (t->r, i - t->l->s));
    }
    Q* dec (Q* t, int i) {
        if (t->s == 1) return getnew (t->c - 1);
        if (i <= t->l->s) return getnew (dec (t->l, i), t->r);
        else return getnew (t->l, dec (t->r, i - t->l->s));
    }
    int query (int k) {
        if (b[1]->s == 1) return 1;
        int t (0);
        for (int i = 1; i <= t1; i ++)
            t -= a[i]->l->c;
        for (int i = 1; i <= t2; i ++)
            t += b[i]->l->c;
        if (k <= t)
        {
            for (int i = 1; i <= t1; i ++)
                a[i] = a[i]->l;
            for (int i = 1; i <= t2; i ++)
                b[i] = b[i]->l;
            return query (k);
        }
        else
        {
            int tmp = b[1]->l->s;
            for (int i = 1; i <= t1; i ++)
                a[i] = a[i]->r;
            for (int i = 1; i <= t2; i ++)
                b[i] = b[i]->r;
            return tmp + query (k - t);
        }
    }
    void INC (int x, int v)
    {
        for (int i = x; i <= n; i += i & -i)
            root[i] = inc (root[i], v);
    }
    void DEC (int x, int v)
    {
        for (int i = x; i <= n; i += i & -i)
            root[i] = dec (root[i], v);
    }
}seg;
int l[N], r[N], k[N], x[N], v[N];
int main ()
{
    seg.init ();
    scanf ("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++)
        scanf ("%d", &a[i]), b[i] = a[i];
    b_c = n;
    char s[10];
    for (int i = 1; i <= m; i ++)
    {
        scanf ("%s", s);
        if (s[0] == 'Q')
            scanf ("%d%d%d", &l[i], &r[i], &k[i]);
        if (s[0] == 'C')
            scanf ("%d%d", &x[i], &v[i]), b[++ b_c] = v[i];
    }
    sort (b + 1, b + 1 + b_c);
    b_c = unique (b + 1, b + 1 + b_c) - (b + 1);
    for (int i = 1; i <= n; i ++)
        a[i] = lower_bound (b + 1, b + 1 + b_c, a[i]) - b;
    for (int i = 1; i <= m; i ++)
        if (x[i] != 0)
            v[i] = lower_bound (b + 1, b + 1 + b_c, v[i]) - b;

    seg.root[0] = seg.build (1, b_c);
    for (int i = 1; i <= n; i ++)
        seg.root[i] = seg.root[0];
    for (int i = 1; i <= n; i ++)
        seg.INC (i, a[i]);
    for (int j = 1; j <= m; j ++)
    {
        seg.t1 = seg.t2 = 0;
        if (l[j] != 0)
        {
            for (int i = l[j] - 1; i; i -= i & -i)
                seg.a[++ seg.t1] = seg.root[i];
            for (int i = r[j]; i; i -= i & -i)
                seg.b[++ seg.t2] = seg.root[i];
            printf ("%d\n", b[seg.query (k[j])]);
        }
        if (x[j] != 0)
        {
            seg.DEC (x[j], a[x[j]]);
            a[x[j]] = v[j];
            seg.INC (x[j], a[x[j]]);
        }
    }
    return 0;
}
