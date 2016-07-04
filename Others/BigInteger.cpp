#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int LEN = 110, base = 10000;
struct Num {
	int s[LEN], len;
	Num() { len = 0; memset(s, 0, sizeof s); }
	Num(int x) {
		len = 1;
		memset (s, 0, sizeof s);
		s[1] = x;
	}
	int& operator[](int x) {
		return s[x];
	}
	int operator[](int x) const {
		return s[x];
	}
	void get() {
		LL x;
		cin >> x;
		while(x) {
			s[++len] = x % base;
			x /= base;
		}
	}
	void print() {
		printf("%d", s[len]);
		for (int i = len - 1; i >= 1; i --)
			printf("%04d", s[i]);
		printf("\n");
	}
};
Num operator+ (const Num& a, const Num& b) {
	Num c;
	c.len = max(a.len, b.len);
	for (int i = 1; i <= c.len; i ++) {
		c[i] += a[i] + b[i];
		c[i + 1] += c[i] / base;
		c[i] %= base;
	}
	if (c[c.len + 1]) c.len++;
	return c;
}
Num operator- (const Num &a, const Num &b) {
	Num c;
	c.len = max(a.len, b.len);
	for(int i = 1; i <= c.len; i++) {
		c[i] += a[i] - b[i];
		if(c[i] < 0) {
			c[i + 1]--;
			c[i] += base;
		}
	}
	while(c[c.len] == 0 && c.len > 1) c.len--;
	return c;
}
Num operator* (const Num& a, const Num& b) {
	Num c;
	c.len = a.len + b.len - 1;
	for (int i = 1; i <= a.len; i ++)
		for (int j = 1; j <= b.len; j ++) {
			c[i + j - 1] += a[i] * b[j];
			c[i + j] += c[i + j - 1] / base;
			c[i + j - 1] %= base;
		}
	if (c[c.len + 1]) c.len++;
	while(c[c.len] == 0 && c.len > 1) c.len--;
	return c;
}
bool operator< (const Num& a, const Num& b) {
	if (a.len == b.len)
		for (int i = a.len; i >= 0; i --)
			if (a[i] != b[i])
				return a[i] < b[i];
	return a.len < b.len;
}
bool operator== (const Num& a, const Num& b) {
	if (a.len != b.len)
		return false;
	for (int i = a.len; i >= 0; i --)
		if (a[i] != b[i])
			return false;
	return true;
}
struct Q {
	Num x, y;
}a, b, A, B;
Q operator* (const Q& a, const Q& b) {
	Q c;
	c.x = a.x * b.x - a.y * b.y;
	c.y = a.x * b.y + a.y * b.x;
	return c;
}
int n, m;
int main() {
	freopen("a.in", "r", stdin);
	A.x.get();A.y.get();
	cin >> n;
	B.x.get();B.y.get();
	cin >> m;
	//(a + bi)(c + di) = (ac - bd) + (ad + bc)
	for (int i = 1; i <= m; i ++)
		A = A * a;
	for (int i = 1; i <= n; i ++)
		B = B * b;
	if (A.x == B.x && A.y == B.y)
		printf("%d\n", __gcd(n, m));
	else
		printf("0\n");
	return 0;
}
