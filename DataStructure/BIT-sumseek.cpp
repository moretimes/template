#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <queue>
using namespace std;
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define dwn(i, s, t) for (int i = s; i >= t; i--)
#define edg(i, x) for (int i = head[x]; ~ i; i = next[i])
#define ctn(i, x) for (i = x.begin(); i != x.end(); i++)
#define clr(x) memset ((x), 0, sizeof (x))
#define size(x) (int)x.size()
typedef long long LL;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void print(LL x) {
    static int a[24];int n = 0;
    while(x > 0) {
        a[n++] = x % 10;
        x /= 10;
    }
    if (n == 0) a[n++] = 0;
    while(n--) putchar('0' + a[n]);
    putchar('\n');
}
void from(const char *s) {
	freopen(s, "r", stdin);
}
const int N = 301000;
int a[N], b[N], s[N], ans[N], x, n, fa[N], L;
void update(int x, int val) {
	for (; x <= L; x += x & -x)
		s[x] += val;
}
int query(int x) {
	int z = 0;
	for (; x; x -= x & -x)
		z += s[x];
	return z;
}
int sumseek(int val) {
	int z = 0, sum = 0;
	for (int i = 18; i >= 0; i --) {
		z += (1<<i);
		if (z > L || sum + s[z] >= val) z -= (1<<i);
		else sum += s[z];
	}
	return z + 1;
}
int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
int main() {
	from("a.in");
	n = read();
	L = read();L += n;
	rep(i, 1, L) fa[i] = i;
	rep(i, 1, n) {
		a[i] = read();
		int right = find(a[i]);
		update(right, 1);
		fa[right] = find(right + 1);
		//rep(i, 1, L) printf("%d", find(i));puts("");
		a[i] = query(a[i] - 1);
	}
	int res = 0;
	dwn(i, n, 1) {
		x = sumseek(a[i] + 1);
		update(x, -1);
		res = max(res, x);
		ans[x] = i;
	}
	printf("%d\n", res);
	rep(i, 1, res) printf("%d ", ans[i]);
	return 0;
}