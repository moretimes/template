#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
const int N = 501000, M = 30;
/*
1.len[i]��ʾ���Ϊi�Ľڵ��ʾ�Ļ��Ĵ��ĳ��ȣ�һ���ڵ��ʾһ�����Ĵ���
2.next[i][c]��ʾ���Ϊi�Ľڵ��ʾ�Ļ��Ĵ�����������ַ�c�Ժ��ɵĻ��Ĵ��ı�ţ����ֵ������ƣ���
3.fail[i]��ʾ�ڵ�iʧ���Ժ���ת����������Ľڵ�i��ʾ�Ļ��Ĵ������׺���Ĵ�����AC�Զ������ƣ���
4.cnt[i]��ʾ�ڵ�i��ʾ�ı��ʲ�ͬ�Ĵ��ĸ���������ʱ����Ĳ�����ȫ�ģ����count()������һ���Ժ������ȷ�ģ�
5.num[i]��ʾ�Խڵ�i��ʾ������Ĵ������Ҷ˵�Ϊ���Ĵ���β�Ļ��Ĵ�������
6.lastָ�������һ����ĸ�����γɵ�����Ĵ���ʾ�Ľڵ㡣
7.S[i]��ʾ��i����ӵ��ַ���һ��ʼ��S[0] = -1������������һ���ڴ�S�в�����ֵ��ַ�������
8.p��ʾ��ӵĽڵ������
9.n��ʾ��ӵ��ַ�������
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
