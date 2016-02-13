#include <cstdio>
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
typedef long long LL;
LL D, P;
struct Q{
	LL a, b;
	Q(LL _a = 0, LL _b = 0) : a(_a), b(_b) {}
	Q operator* (const Q& p) {
		return Q((a * p.a % P + b * p.b % P * D % P) % P, (a * p.b % P + p.a * b % P) % P);
	}
};
LL qk(LL x, LL k) {
	LL z(1);
	for (; k; k >>= 1) {
		if (k & 1) z = z * x % P;
		x = x * x % P;
	}
	return z;
}
LL qk(Q x, LL k) {
	Q z(1, 0);
	for (; k; k >>= 1) {
		if (k & 1) z = z * x;
		x = x * x;
	}
	return z.a;
}
LL L(LL a) {
	return qk(a, (P - 1) / 2) == 1;
}
LL solve(LL n) {
	//P == 2 special judge
	if (P == 2) {
		if (n == 1) return 1;
		else return -1;
	}
	if (!L(n)) return -1;
	LL a;
	while(1) {
		a = rand() % P;
		D = ((a * a - n) % P + P) % P;
		if (!L(D)) break;
	}
	return qk(Q(a, 1), (P + 1) / 2);
}

int main() {
	srand(time(0));
	int T;
	scanf("%d", &T);
	while(T --) {
		int a, n, t;
		scanf("%d%d", &a, &n);
		a %= n;
		P = n;
		t = solve(a);
		if (t == -1)
			puts("No root");
		else {
			if (t == n - t)
				printf("%d\n", t);
			else
				printf("%d %d\n", min(t, n - t), max(t, n - t));
		}
	}
	return 0;
}

