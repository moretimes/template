#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;
typedef long long LL;
const int N = 1001000;
LL pw(LL a, LL k) {
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
LL pw(LL x, LL k, LL p) {
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
	int N = 1000000;
	for (int i = 1; i <= N; i ++)
		vis[i] = false;
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
	LL n;
	int a_c;
	int a[N];
	void divide(LL n) {
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
	int get(LL _n) {
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

const int HN = 30000, M = 1000000, HEAD = 29997;
struct HASH {
	int cnt, head[HN], next[M], len[M];
	LL key[M];
	HASH() {
		clear();
	}
	inline void clear() {
		memset (head, -1, sizeof head);
		cnt = 0;
	}
	inline void ADD(int x, LL y, int w) {
		key[cnt] = y;
		next[cnt] = head[x];
		len[cnt] = w;
		head[x] = cnt ++;
	}
	inline int GETHEAD(LL idx) {
		return idx % HEAD;
	}
	inline void add(LL idx, int val) {
		int h = GETHEAD(idx);
		ADD(h, idx, val);
	}
	bool find(LL idx) {
		int h = GETHEAD(idx);
		for (int i = head[h]; ~ i; i = next[i])
			if (key[i] == idx)
				return true;
		return false;
	}
	int get(LL idx) {
		int h = GETHEAD(idx);
		for (int i = head[h]; ~ i; i = next[i])
			if (key[i] == idx)
				return len[i];
	}
}_hash;
int BSGS(LL a, LL b, LL p) {
	a %= p, b %= p;
	if (b == 1) return 0;
	int cnt = 0;
	LL t = 1;
	for (LL g = gcd(a, p); g != 1; g = gcd(a, p)) {
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
void exgcd(LL a, LL b, LL& d, LL& x, LL& y) {
    if (!b) { d = a; x = 1; y = 0; }
    else { exgcd(b, a % b, d, y, x); y -= x * (a / b); }
}
LL A, B, p;
LL a[N];
int a_c;
int main() {
	freopen("a.in", "r", stdin);
	getpr();
	int Case = 0;
	while(scanf("%lld%lld%lld", &A, &p, &B) != EOF) {
		a_c = 0;
		int g = root.get(B);
		LL I = BSGS(g, B, p);
		LL x, y, d;
		exgcd(A, p - 1, d, x, y);
		++Case;printf("case%d:\n", Case);
		if (I % d) {
			printf("-1\n");
			continue;
		} else {
			x = (I / d) * x % (p - 1);
			for (int i = 0; i < d; i ++) {
				LL tx = (x + i * (p - 1) / d) % (p - 1); 
				a[++a_c] = pw(g, tx, p);
			}
		}
		sort(a + 1, a + 1 + a_c);
		for (int i = 1; i <= a_c; i ++)
			printf("%lld\n", a[i]);
	}
	return 0;
}

