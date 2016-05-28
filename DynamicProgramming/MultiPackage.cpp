#include <cstdio>
#include <cstring>
const int N = 1001000, M = 1001000;
int n, m, v[N], c[N], f[M];
void init() {
	memset (f, 0, sizeof f);
}
void solve() {
	
	for (int i = 1; i <= n; i ++)
		scanf("%d", &v[i]);
	for (int i = 1; i <= n; i ++)
		scanf("%d", &c[i]);
	//w[i]
	f[0] = 1;
	for (int i = 1; i <= n; i ++)
		for (int d = 0; d < v[i]; d ++) {
			que.init();
			for (int k = 0; k <= (m - d) / v[i]; k ++) {
				que.insert(T(k, f[d + k * v[i]]));
				que.pop(k - c[i]);
				f[d + k * v[i]] = que.get();
			}
		}
	int ans = 0;
	for (int i = 1; i <= m; i ++)
		ans += f[i];
	printf("%d\n", ans);
}
int main() {
	while(scanf("%d%d", &n, &m), n + m) {
		init();
		solve();
	}
	return 0;
}
