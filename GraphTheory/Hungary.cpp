#include <cstdio>
#include <cstring>
//优化：随机一个匹配增广；改邻接表
const int N = 1010;
bool vis[N], map[N][N];
int n, m, t, x, lnk[N], left[N];
bool DFS (int u)
{
	for (int v = 1; v <= m; v ++)
		if (map[u][v] && !vis[v])
		{
			vis[v] = true;
			if (lnk[v] == -1 || DFS (lnk[v]))
			{
				lnk[v] = u;
				return true;
			}
		}
	return false;
}
 
int hungary ()
{
	int ans (0);
	memset (lnk, -1, sizeof lnk);
	for (int i = 1; i <= n; i ++)
	{
		memset (vis, 0, sizeof vis);
		if (DFS (i))
			ans ++;
	}
	return ans;
}
int k;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1, a, b; i <= k; i ++)
		scanf("%d%d", &a, &b), map[a][b] = true;
	int ans = hungary();
	printf("%d\n", n + m - hungary());
	return 0;
}

