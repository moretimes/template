#include <cstdio>
#include <cstring>
typedef long long LL;
const int N = 4001000;
int P, n, a_c;
int a[N];
LL pw(LL a, int k) {
	LL z(1);
	for (; k; k >>= 1) {
		if (k & 1) z = z * a % P;
		a = a * a % P;
	}
	return z;
}
bool vis[N];
int pr[N];
void getpr() {
	const int N = 4000000;
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
		if (pw(x, n / a[i]) == 1)
			return false;
	return true;
}
int main() {
	scanf("%d", &n);
	getpr();
	divide(n - 1);
	P = n;
	int i;
	for (i = 2; ; i ++) {
		if (ck(i))
			break;
	}
	printf("%d\n", i);
	return 0;
}

