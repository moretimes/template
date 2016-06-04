#include <bits/stdc++.h>
using namespace std;
#define rep(i, s, t) for (int i = s; i <= t; i ++)
#define dwn(i, s, t) for (int i = s; i >= t; i --)
#define edg(i, x) for (int i = head[x]; ~ i; i = next[i])
#define ctn(i, x) for (i = x.begin(); i != x.end(); i++)
#define clr(x) memset ((x), 0, sizeof (x))
typedef long long LL;
typedef pair<int, int> pi;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void print(LL x) {
	if (x / 10) print(x / 10);
	putchar(x % 10 + '0');
}
void from(const char *s) {
	freopen(s, "r", stdin);
}
const int N = 501000, INF = 0x3f3f3f3f;
int key[N], next[N], len[N], head[N], cnt, f[N], sz[N], flag[N], root[N], tot, K, n, t, ans;
vector<pi> son[N];
void add(int x, int y, int w) {
	key[cnt] = y;
	next[cnt] = head[x];
	len[cnt] = w;
	head[x] = cnt++;
}
void find(int u, int fa) {
	f[u] = 0, sz[u] = 1;
	edg(i, u) {
		int v = key[i];
		if (flag[v] || v == fa) continue;
		find(v, u);
		sz[u] += sz[v];
		f[u] = max(f[u], sz[v]);
	}
	f[u] = max(f[u], tot - sz[u]);
	if (f[u] < f[root[t]])
		root[t] = u;
}
bool cmp(pi x, pi y) {
	return sz[x.first] < sz[y.first];
}
void solve(int u) {
	flag[u] = t;
	if (tot == 1) return ;
	edg(i, u) {
		int v = key[i];
		if (flag[v]) continue;
		if (sz[v] > sz[u]) sz[v] = tot - sz[u];
		son[u].push_back(pi(v, len[i]));
	}
	sort(son[u].begin(), son[u].end(), cmp);
	edg(i, u) {
		int v = key[i];
		if (flag[v]) continue;
		++t;
		tot = sz[v];
		find(v, 0);
		solve(root[t]);
	}
}
map<int, int> res, path;
map<int, int>::iterator it;
int dep1, dep2, clk;
void update(map<int, int>& mp, int key, int val) {
	if (mp.find(key) != mp.end()) mp[key] = min(mp[key], val);
	else mp[key] = val;
}
void DFS(int u, int fa, int dep, int dis) {
	update(path, dis, dep);
	edg(i, u) {
		int v = key[i];
		if (flag[v] <= clk || v == fa) continue;
		DFS(v, u, dep + 1, dis + len[i]);
	}
}
bool conquer() {
	for (clk = 1; clk <= n; clk++) {
		int u = root[clk];
		res[0] = 0;
		rep(i, 0, (int)son[u].size() - 1) {
			int v = son[u][i].first;
			int len = son[u][i].second;
			DFS(v, u, 1, len);
			ctn(it, path)
				if (res.find(K - it->first) != res.end())
					ans = min(ans, it->second + res[K - it->first]);
			ctn(it, path)
				update(res, it->first, it->second);
			path.clear();
		}
		res.clear();
	}
	return 0;
}
int main() {
	memset (head, -1, sizeof head);
	n = read(), K = read();
	rep(i, 1, n - 1) {
		int a, b, c;
		a = read(), b = read(), c = read();
		++a,++b;
		add(a, b, c);
		add(b, a, c);
	}
	++t;
	tot = n;f[0] = INF;
	find(1, 0);
	solve(root[1]);
	ans = 0x3f3f3f3f;
	conquer();
	printf("%d\n", ans != 0x3f3f3f3f ? ans : -1);
	return 0;
}
