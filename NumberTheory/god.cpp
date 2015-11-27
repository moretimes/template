#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;
typedef long long LL;
const int N = 101000;
LL pw(LL a, int k) {
	LL z(1);
	for (; k; k >>= 1) {
		if (k & 1) z = z * a;
		a = a * a;
	}
	return z;
}
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
LL pw(LL x, int k, LL p) {
	LL z = 1;
	for (; k; k >>= 1) {
		if (k & 1) z = z * x % p;
		x = x * x % p;
	}
	return z;
}
bool vis[N];
int pr[N];
void getpr() {
	int N = 100000;
	memset (vis, 0, sizeof vis);
	int cnt = 0;
	for (int i = 2; i <= N; i ++) {
		if (!vis[i])
			pr[++ cnt] = i;
		for (int j = 1; j <= cnt; j ++) {
			if (i * pr[j] > N) break;
			vis[i * pr[j]] = true;
			if (i % pr[j] == 0) break;
		}
	}
}
struct ROOT {
	int n, a_c;
	int a[N];
	void divide(int n) {
		for (int i = 1; pr[i] * pr[i] <= n; i ++) {
			if (n % pr[i] != 0) continue;
			a[++ a_c] = pr[i];
			while(n % pr[i] == 0) n /= pr[i];
		}
		if (n != 1) a[++ a_c] = n;
	}
	bool ck(int x) {
		for (int i = 1; i <= a_c; i ++)
			if (pw(x, n / a[i], n) == 1)
				return false;
		return true;
	}
	int get(int _n) {
		a_c = 0;
		n = _n;
		divide(n - 1);
		int i;
		for (i = 2; ; i ++) {
			if (ck(i))
				return i;
		}
	}
}root;

const int HN = 40000, M = 100000, HEAD = 39997;
struct HASH {
	int cnt, head[HN], next[M], len[M], key[M];
	HASH() {
		clear();
	}
	inline void clear() {
		memset (head, -1, sizeof head);
		cnt = 0;
	}
	inline void ADD(int x, int y, int w) {
		key[cnt] = y;
		next[cnt] = head[x];
		len[cnt] = w;
		head[x] = cnt ++;
	}
	inline int GETHEAD(int idx) {
		return idx % HEAD;
	}
	inline void add(int idx, int val) {
		int h = GETHEAD(idx);
		ADD(h, idx, val);
	}
	bool find(int idx) {
		int h = GETHEAD(idx);
		for (int i = head[h]; ~ i; i = next[i])
			if (key[i] == idx)
				return true;
		return false;
	}
	int get(int idx) {
		int h = GETHEAD(idx);
		for (int i = head[h]; ~ i; i = next[i])
			if (key[i] == idx)
				return len[i];
	}
}_hash;
int BSGS(int a, int b, int p) {
	a %= p, b %= p;
	if (b == 1) return 0;
	int cnt = 0;
	LL t = 1;
	for (int g = gcd(a, p); g != 1; g = gcd(a, p)) {
		if (b % g) return -1;
		p /= g, b /= g, t = t * a / g % p;
		++cnt;
		if (b == t) return cnt;
	}
	_hash.clear();
	int m = int(sqrt(1.0 * p) + 0.5);
	LL base = b;
	for (int i = 0; i < m; i ++) {
		_hash.add(base, i);
		base = base * a % p;
	}
	base = pw(a, m, p);
	LL now = t;
	for (int i = 1; i <= m + 1; ++i) {
		now = now * base % p;
		if (_hash.find(now))
			return i * m - _hash.get(now) + cnt;
	}
	return -1;
}
int a[N], c[N], a_c;
void Divide(int n) {
	a_c = 0;
	memset (c, 0, sizeof c);
	for (int i = 1; pr[i] * pr[i] <= n; i ++) {
		if (n % pr[i] != 0) continue;
		a[++ a_c] = pr[i];
		while(n % pr[i] == 0) n /= pr[i], c[a_c]++;
	}
	if (n != 1) {
		a[++ a_c] = n;
		c[a_c] = 1;
	}
}
int A, B, p;
int main() {
	freopen("a.in", "r", stdin);
	getpr();
	int T;
	scanf("%d", &T);
	while(T --) {
		scanf("%d%d%d", &A, &B, &p);
		a_c = 0;
		p = 2 * p + 1;
		Divide(p);
		bool flag = false;
		LL ans = 1;
		for (int i = 1; i <= a_c; i ++) {
			int t = pw(a[i], c[i]);
			int b = B % t;
			if (!b) {
				ans = ans * pw(a[i], c[i] - (c[i] - 1) / A - 1);
			}
			else {
				int g = gcd(b, t);
				b /= g, t /= g;
				int cnt = 0;
				while(g % a[i] == 0) g /= a[i], cnt ++;
				if (cnt % A) {
					ans = 0;
					break;
				}
				int rt = root.get(a[i]);
				int I = BSGS(rt, b, t);
				int phit = t - pw(a[i], c[i] - 1);
				int D = gcd(A, phit);
				if (I % D) {
					ans = 0;
					break;
				}
				if (cnt)
					ans = ans * D * pw(a[i], cnt - cnt / A);
				else
					ans = ans * D;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

