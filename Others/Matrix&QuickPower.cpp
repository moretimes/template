int mod(int x) { return x % P; }
LL mod(LL x) { return x % P; }
struct Q {
	int s[N][N];
	Q () {
		memset (s, 0, sizeof s);
	}
	Q operator * (const Q& a) {
		Q c;
		for (int i = 0; i < N; i ++)
			for (int j = 0; j < N; j ++)
				for (int k = 0; k < N; k ++)
					c.s[i][j] = mod(c.s[i][j] + mod(s[i][k] * a.s[k][j]));
		return c;
	}
};
Q qk(Q& A, LL k) {
	Q z;z.s[0][0] = z.s[1][1] = 1;
	for (; k; k >>= 1) {
		if (k & 1)
			z = z * A;
		A = A * A;
	}
	return z;
}