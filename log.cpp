#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;
typedef long long LL;
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
int pw(LL x, int k, LL p) {
	LL z = 1;
	for (; k; k >>= 1) {
		if (k & 1) z = z * x % p;
		x = x * x % p;
	}
	return z;
}
const int N = 40000, M = 100000, HEAD = 39997;
struct HASH {
	int cnt, head[N], next[M], len[M], key[M];
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
};
struct HASH hash;
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
	hash.clear();
	int m = int(sqrt(1.0 * p) + 0.5);
	LL base = b;
	for (int i = 0; i < m; i ++) {
		hash.add(base, i);
		base = base * a % p;
	}
	base = pw(a, m, p);
	LL now = t;
	for (int i = 1; i <= m + 1; ++i) {
		now = now * base % p;
		if (hash.find(now))
			return i * m - hash.get(now) + cnt;
	}
	return -1;
}
int main() {
	freopen("a.in", "r", stdin);
	int a, b, p;
	while(scanf("%d%d%d", &p, &a, &b) != EOF) {
		int tmp = BSGS(a, b, p);
		if (tmp == -1) printf("no solution\n");
		else printf("%d\n", tmp);
	}
	return 0;
}

