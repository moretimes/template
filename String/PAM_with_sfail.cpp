#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
const int N = 501000, M = 30;
int ans[N][2];
const int MAX = 0x3f3f3f3f;
struct PAM {
	int next[N][M], fail[N], cnt[N], len[N], S[N], num[N], diff[N], sfail[N], dp[N][2];
	int last, n, p;
	int newnode(int l) {
		for (int i = 0; i < M; i ++) next[p][i] = 0;
		cnt[p] = 0;
		num[p] = 0;
		len[p] = l;
		return p++;
	}
	void init() {
		p = 0;
		newnode(0);
		newnode(-1);
		last = 0;
		n = 0;
		S[n] = -1;
		fail[0] = 1;
		ans[0][0] = 0;
		ans[0][1] = MAX;
	}
	int get_fail(int x) {
		while(S[n - len[x] - 1] != S[n]) x = fail[x];
		return x;
	}
	int getmin(int x, int i) {
		dp[x][i] = ans[n - len[sfail[x]] - diff[x]][i];
		if (diff[x] == diff[fail[x]]) {
			dp[x][i] = min(dp[x][i], dp[fail[x]][i]);
		}
		return dp[x][i] + 1;
	}
	void add(int c) {
		c -= 'a';
		S[++n] = c;
		int cur = get_fail(last);
		if (!next[cur][c]) {
			int now = newnode(len[cur] + 2);
			fail[now] = next[get_fail(fail[cur])][c];
			next[cur][c] = now;
			num[now] = num[fail[now]] + 1;
		}
		last = next[cur][c];
		diff[last] = len[last] - len[fail[last]];
		sfail[last] = diff[last] != diff[fail[last]] ? fail[last] : sfail[fail[last]];
		cnt[last]++;
		//=============================================
		ans[n][1] = ans[n][0] = MAX;
		for (int x = last; x; x = sfail[x]) {
			
			ans[n][0] = min(ans[n][0], getmin(x, 1)); 
			ans[n][1] = min(ans[n][1], getmin(x, 0));
		}
	}
	void count() {
		for (int i = p - 1; i >= 0; i --)
			cnt[fail[i]] += cnt[i];
		for (int i = 1; i <= n; i ++)
			printf("%d %d\n", 
				ans[i][1] == MAX ? -1 : ans[i][1], 
				ans[i][0] == MAX ? -2 : ans[i][0]);
	}
}pa, pb;
char s[N];
int main() {
	freopen("a.in", "r", stdin);
	int T;
	
	scanf("%s", s);
	int len = strlen(s);
	pa.init();
	for (int i = 0; i < len; i ++)
		pa.add(s[i]);
	pa.count();
	
	return 0;
}
