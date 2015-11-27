#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int N = 1010, INF = 0x3f3f3f3f;
int w[N][N], lx[N], ly[N], match[N], slack[N];
bool vx[N], vy[N];
bool dfs(int i) {
	vx[i] = true;
	for (int j = 0; j < n; j ++) {
		if (lx[i] + ly[j] > w[i][j]) {
			slack[j] = min(slack[j], lx[i] + ly[j] - w[i][j]);
		} else if (!vy[j]) {
			vy[j] = true;
			if (match[j] < 0 || dfs(match[j])) {
				match[j] = i;
				return true;
			}
		}
	}
	return false;
}
int km() {
	memset(match, -1, sizeof match);
	memset(ly, 0, sizeof ly);
	for (int i = 0; i < n; i ++) lx[i] = *max_element(w[i], w[i] + n);
	for (int i = 0; i < n; i ++) {
		while(1) {
			memset(vx, 0, sizeof vx);
			memset(vy, 0, sizeof vy);
			memset(slack, 0x3f, sizeof slack);
			if (dfs(i)) break;
			int d = 0x3f3f3f3f;
			for (int i = 0; i < n; i ++) {
				if (!vy[i]) d = min(d, slack[i]);
			}
			for (int i = 0; i < n; i ++) {
				if (vx[i]) lx[i] -= d;
				if (vy[i]) ly[i] += d;
			}
		}
	}
	int z = 0;
	for (int i = 0; i < n; i ++) {
		if (w[match[i]][i] == -INF) return -1;
		z += w[match[i]][i];
	}
	return z;
}

