struct Seg{
#define lson idx << 1
#define rson idx << 1 | 1
#define N 101000 * 4
    int mx[N], add[N], cover[N];
    void pushup(int idx) {
        mx[idx] = max(mx[lson], mx[rson]);
    }
    void pushdown(int mid, int idx) {
        if (cover[idx] != -1) {
            cover[lson] = cover[rson] = cover[idx];
            add[lson] = add[rson] = 0;
            mx[lson] = mx[rson] = cover[idx];
            cover[idx] = -1;
        }
        if (add[idx]) {
            mx[lson] += add[idx];
            mx[rson] += add[idx];
            if (cover[lson] == -1) add[lson] += add[idx];
            else cover[lson] += add[idx];
            if (cover[rson] == -1) add[rson] += add[idx];
            else cover[rson] += add[idx];
            add[idx] = 0;
        }
    }
    void build(int l, int r, int idx, int* w) {
        cover[idx] = -1;
        if (l == r) {
            mx[idx] = w[l];
            return ;
        }
        int mid = (l + r) >> 1;
        build(l, mid, lson, w);
        build(mid + 1, r, rson, w);
        pushup(idx);
    }
    int query(int L, int R, int l, int r, int idx) {
        if (L <= l && r <= R) {
            return mx[idx];
        }
        int mid = (l + r) >> 1;
        int z = 0;
        pushdown(mid, idx);
        if (L <= mid)
            z = max(z, query(L, R, l, mid, lson));
        if (R > mid)
            z = max(z, query(L, R, mid + 1, r, rson));
        pushup(idx);
        return z;
    }
    void Add(int L, int R, int v, int l, int r, int idx) {
        if (L <= l && r <= R) {
            add[idx] += v;
            mx[idx] += v;
            return ;
        }
        int mid = (l + r) >> 1;
        pushdown(mid, idx);
        if (L <= mid)
            Add(L, R, v, l, mid, lson);
        if (R > mid)
            Add(L, R, v, mid + 1, r, rson);
        pushup(idx);
    }
    void Cover(int L, int R, int v, int l, int r, int idx) {
        if (L <= l && r <= R) {
            cover[idx] = v;
            add[idx] = 0;
            mx[idx] = v;
            return ;
        }
        int mid = (l + r) >> 1;
        pushdown(mid, idx);
        if (L <= mid)
            Cover(L, R, v, l, mid, lson);
        if (R > mid)
            Cover(L, R, v, mid + 1, r, rson);
        pushup(idx);
    }

}seg;

