int S, T;
struct Flow {
	typedef LL int;
	const int INF = 0x3f3f3f3f;
	int key[M], next[M], head[N], cnt, f[M];
	int pe[N], pv[N], S, T;
	int  q[N];
	LL dis[N], cost[M];
	bool vis[N];
	void init() {
		cnt = 0;
		memset (head, -1, sizeof head);
	}
	void add(int x, int y, LL w, int flow) {
		key[cnt] = y;
		next[cnt] = head[x];
		cost[cnt] = w;
		f[cnt] = flow;
		head[x] = cnt ++;
		
		key[cnt] = x;
		next[cnt] = head[y];
		cost[cnt] = -w;
		f[cnt] = 0;
		head[y] = cnt ++;
	}
	bool spfa() {
		rep(i, S, T) dis[i] = INF;
		memset (vis, 0, sizeof vis);
		int h = 1, t = 2;
		q[1] = S;
		vis[S] = true;
		dis[S] = 0;
		while(h < t) {
			int u = q[h ++];
			vis[u] = false;
			for (int i = head[u]; ~ i; i = next[i]) {
				int v = key[i];
				if (dis[v] > dis[u] + cost[i] && f[i]) {
					dis[v] = dis[u] + cost[i];
					pv[v] = u;
					pe[v] = i;
					if (!vis[v]) {
						vis[v] = true;
						q[t ++] = v;
					}
				}
			}
		}
		return dis[T] != INF;
	}
	LL z() {
		int tmp = INF;
		for (int i = T; i != S; i = pv[i])
			tmp = min(tmp, f[pe[i]]);
		for (int i = T; i != S; i = pv[i])
			f[pe[i]] -= tmp, f[pe[i] ^ 1] += tmp;
		return dis[T] * tmp;
	}
	LL work() {
		LL ans = 0;
		while(spfa())
			ans += z();
		return ans;
	}
}flow;