#include <cstdio>
#include <iostream>
#include <algorithm>
#define rep(i, s, t) for (int i = s; i <= t; i ++)
using namespace std;
const int N = 1001000;
int n, m, a[N], s[N], ans[N], last[N];
struct Q {
	int l, r, id;
	bool operator<(const Q& a) const {
		return r < a.r;
	}
}b[N];
void update(int x, int v) {
	for (; x <= n; x += x & -x) s[x] += v;
}
int query(int x) {
	int z = 0;
	for (; x; x -= x & -x) z += s[x];
	return z;
}	
int main() {
	scanf("%d", &n);
	rep(i, 1, n) scanf("%d", &a[i]);
	scanf("%d", &m);
	rep(i, 1, m) scanf("%d%d", &b[i].l, &b[i].r), b[i].id = i;
	sort(b + 1, b + 1 + m);
	int k = 1;
	rep(i, 1, n) {
		update(i, 1);
		if (last[a[i]]) update(last[a[i]], -1);
		last[a[i]] = i;
		while(b[k].r == i) {
			ans[b[k].id] = query(b[k].r) - query(b[k].l - 1);
			k++;
		}
	}
	rep(i, 1, m) printf("%d\n", ans[i]);
	return 0;
}
