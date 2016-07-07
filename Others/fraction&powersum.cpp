#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 35;
typedef long long LL;
struct Q {
	LL a, b;
	Q () { a = 0; b = 1; }
	Q (LL x) { a = x; b = 1; }
	Q (LL x, LL y) {
		a = x, b = y;
		uni();
	}
	void uni() {
		LL t = __gcd(a, b);
		a /= t;
		b /= t;
		if (b < 0) {
			a = -a;
			b = -b;
		}
	}
	Q operator + (const Q& x) const {
		Q c;
		c.a = a * x.b + x.a * b;
		c.b = b * x.b;
		c.uni();
		return c;
	}
	Q operator - (const Q& x) const {
		Q c;
		c.a = a * x.b - x.a * b;
		c.b = b * x.b;
		c.uni();
		return c;
	}
	Q operator * (const Q& x) const {
		Q c;
		c.a = a * x.a;
		c.b = b * x.b;
		c.uni();
		return c;
	}
	Q operator / (const Q& x) const {
		Q c;
		c.a = a * x.b;
		c.b = b * x.a;
		c.uni();
		return c;
	}
	bool operator==(int x) {
		uni();
		return a == 0;
	}
	bool operator!=(int x) {
		uni();
		return a != 0;
	}
	void print() {
		printf("X = %lld/%lld\n", a, b);
	}
}C[N][N], B[N];
int main() {
	for (int i = 1; i <= 31; i ++) {
		C[i][0] = C[i][i] = Q(1, 1);
		for (int j = 1; j < i; j ++)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];//, C[i][j].print();
	}
	B[0] = Q(1, 1);
	for (int i = 1; i <= 30; i ++) {
		B[i] = Q(0, 1);
		for (int j = 0; j < i; j ++)
			B[i] = B[i] + C[i + 1][j] * B[j];
		B[i] = B[i] * Q(-1, i + 1);
		//printf("%d ", i);B[i].print();
		
	}
	int m;
	scanf("%d", &m);
	for (int k = 0; k <= m; k ++) {
		Q t(1, m + 1);
		t = t * C[m + 1][k];
		t = t * B[k];
		if (k == 1) t = t + Q(1, 1);
		t.print();
		//C[m + 1][k] * B[k].print();
	}
	Q t(0, 1);
	t.print();
	return 0;
}
