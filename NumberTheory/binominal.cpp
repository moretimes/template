const int N = 1001000, P = 1e9 + 7;
LL inv[N], fac[N], faci[N];
LL C(int n, int m) {
	if (n < 0 || m < 0 || m > n) return 0;
	return fac[n] * faci[n - m] % P * faci[m] % P;
}
void pre() {
	const int P = 1e9 + 7, N = 1000000;
	inv[1] = 1;
	rep(i, 2, N) inv[i] = (P - P / i) * inv[P % i] % P;
	fac[0] = 1;
	rep(i, 1, N) fac[i] = fac[i - 1] * i % P;
	faci[0] = 1;
	rep(i, 1, N) faci[i] = faci[i - 1] * inv[i] % P;
}
