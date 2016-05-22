const int N = 501000, M = 601000;
int key[M], nxt[M], head[N], cnt;
void add(int x, int y) {
	key[cnt] = y;
	nxt[cnt] = head[x];
	head[x] = cnt++;
}
struct LCA {
	int f[N][25], d[N], q[N];
	void BFS(int S) {
		int h = 1, t = 2, u;
		q[1] = S;
		while(h < t) {
			u = q[h++];
			for (int i = head[u]; ~ i; i = nxt[i]) {
				int v = key[i];
				if (d[v] != 0) continue;
				f[v][0] = u, d[v] = d[u] + 1;
				q[t++] = v;
			}
		}
	}
	void init(int n) {
		d[1] = 1;
		BFS(1);
		for (int j = 1; j <= 20; j ++)
			for (int i = 1; i <= n; i ++) {
				f[i][j] = f[f[i][j - 1]][j - 1];
			}
	}
	int get(int x, int y) {
		if (d[x] < d[y])
			swap(x, y);
		for (int j = 20; j >= 0; j --)
			if (d[f[x][j]] >= d[y])
				x = f[x][j];
		if (x == y)
			return x;                  //return
		for (int j = 20; j >= 0; j --)
			if (f[x][j] != f[y][j])
				x = f[x][j], y = f[y][j];
		return f[x][0];               //return
	}
	int dis(int x, int y) {
		int t = get(x, y);
		return d[x] - d[t];
	}
}lca;
