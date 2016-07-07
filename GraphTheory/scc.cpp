int dfn[N], low[N], tmct, stk[N], top, scc_c, scc[N];
bool instk[N];
void init() {
	tmct = top = scc_c;
	clr(scc);
	clr(dfn);
	clr(instk);
	clr(low);
}
void DFS(int u) {
	dfn[u] = low[u] = ++ tmct;
	stk[++ top] = u;
	instk[u] = true;
	for (int i = head[u]; ~ i; i = next[i]) {
		int v = key[i];
		if (!dfn[v]) {
			DFS(v);
			low[u] = min(low[u], low[v]);
		} else if (instk[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u]) {
		++ scc_c;
		int now;
		do {
			now = stk[top --];
			scc[now] = scc_c;
			instk[now] = false;
		} while(now != u);
	}
}