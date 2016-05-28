#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#define lc idx << 1
#define rc idx << 1 | 1
#define lson l, mid, lc
#define rson mid + 1, r, rc
using namespace std;
const int N = 401000;
typedef long long LL;
LL sum[N << 2];
int cov[N << 2], mn[N << 2];
void pushup(int idx) {
	sum[idx] = sum[lc] + sum[rc];
	mn[idx] = mn[lc];
}
void pushdown(int l, int r, int mid, int idx) {
	if (cov[idx] != 0) {
		cov[lc] = cov[rc] = cov[idx];
		mn[lc] = cov[idx];
		mn[rc] = cov[idx];
		sum[lc] = (LL)cov[idx] * (mid - l + 1);
		sum[rc] = (LL)cov[idx] * (r - mid);
		cov[idx] = 0;
	}
}
void build(int l, int r, int idx) {
	if (l == r) {
		sum[idx] = l;
		mn[idx] = l;
		return ;
	}
	int mid = (l + r) >> 1;
	build(lson);
	build(rson);
	pushup(idx);
}
void update(int L, int R, int val, int l, int r, int idx) {
	if (L > R) return ;
	if (L <= l && r <= R) {
		cov[idx] = val;
		mn[idx] = val;
		sum[idx] = (LL)val * (r - l + 1);
		return ;
	}
	int mid = (l + r) >> 1;
	pushdown(l, r, mid, idx);
	if (L <= mid) update(L, R, val, lson);
	if (R > mid) update(L, R, val, rson);
	pushup(idx);
}
int left(int L, int R, int val, int l, int r, int idx) {
	if (l == r) {
		if (mn[idx] < val) return l;
		else return 0;
	}
	int mid = (l + r) >> 1;
	pushdown(l, r, mid, idx);
	if (R <= mid) {
		return left(L, R, val, lson);
	}
	else if (L > mid) {
		return left(L, R, val, rson);
	}
	else {
		if (mn[rc] < val) return left(L, R, val, rson);
		else return left(L, R, val, lson);
	}
}
