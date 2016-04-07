#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
const int N = 501000, M = 30;
/*
1.len[i]表示编号为i的节点表示的回文串的长度（一个节点表示一个回文串）
2.next[i][c]表示编号为i的节点表示的回文串在两边添加字符c以后变成的回文串的编号（和字典树类似）。
3.fail[i]表示节点i失配以后跳转不等于自身的节点i表示的回文串的最长后缀回文串（和AC自动机类似）。
4.cnt[i]表示节点i表示的本质不同的串的个数（建树时求出的不是完全的，最后count()函数跑一遍以后才是正确的）
5.num[i]表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数。
6.last指向新添加一个字母后所形成的最长回文串表示的节点。
7.S[i]表示第i次添加的字符（一开始设S[0] = -1（可以是任意一个在串S中不会出现的字符））。
8.p表示添加的节点个数。
9.n表示添加的字符个数。
*/
struct PAM {
	int next[N][M], fail[N], cnt[N], len[N], S[N], num[N];
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
	}
	int get_fail(int x) {
		while(S[n - len[x] - 1] != S[n]) x = fail[x];
		return x;
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
		cnt[last]++;
	}
	void count() {
		for (int i = p - 1; i >= 0; i --)
			cnt[fail[i]] += cnt[i];
	}

}pa, pb;
int main() {
	int T;
	scanf("%d", &T);
		scanf("%s", sa);
		int lb = strlen(sb);
		pa.init();
		for (int i = 0; i < la; i ++)
			pa.add(sa[i]);
		pa.count();
	}
	return 0;
}
