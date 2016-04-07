#include <stdio.h>

const int MAXN = 10010;
int n, q;
int a[MAXN];
struct tree
{
	struct S
	{
		int len, lc, rc, count;
		S(): len(0), lc(0), rc(0), count(0) {}
		S(bool x): len(1), lc(x), rc(x), count(x) {}
		S(const S &L, const S &R):
			len(L.len + R.len), lc(L.lc), rc(R.rc),
			count(L.count + R.count + L.rc * R.lc)
		{
			if (lc == L.len) lc += R.lc;
			if (rc == R.len) rc += L.rc;
		}
	}T[MAXN * 2];

	void build(int x)
	{
		for (int i = 0; i < n; ++i) T[i + n] = S(a[i] % x == 0);
		for (int i = n - 1; i; --i) T[i] = S(T[i<<1], T[i<<1|1]);
	}

	void update(int i, bool x)
	{
		T[i += n] = x;
		while (i >>= 1) T[i] = S(T[i<<1], T[i<<1|1]);
	}

	int query(int l, int r)
	{
		S L, R;
		for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
			if ( l&1) L = S(L, T[l++]);
			if (~r&1) R = S(T[r--], R);
		}
		return S(L, R).count;
	}
}T[101];

int tot;
int prime[101];
int mu[101];
bool vis[101];

int mm[101];

void init()
{
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= 100; ++i) T[i].build(i);
}

void solve()
{
	while (q--) {
		char op[5];
		scanf("%s", op);
		if (op[0] == 'M') {
			int p, v;
			scanf("%d%d", &p, &v);
			for (int i = 1; i <= 100; ++i) {
				T[i].update(p, v % i == 0);
			}
			a[p] = v;
		} else {
			int l, r;
			scanf("%d%d", &l, &r);
			for (int i = 1; i <= 100; ++i) {
				mm[i] = T[i].query(l, r - 1);
			}
			int ans = 0;
			for(int i = 100; i >= 1; i --){
				for (int j = i + i; j <= 100; j += i)
					mm[i] = mm[i] - mm[j];
				if (mm[i]) ans++;
			}
			printf("%d\n", ans);
		}
	}
}

int main()
{
	//freopen("a.in", "r", stdin);
	while (scanf("%d%d", &n, &q) != EOF) {
		init();
		solve();
	}
}
