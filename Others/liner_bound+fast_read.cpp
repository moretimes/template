#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 2001000;
int a[N], l[N], r[N], c[N];
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main() {
	freopen("a.in", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		a[i] = read();
	rotate(a + 1, max_element(a + 1, a + 1+n), a + 1 + n);
	for(int i = n; i >= 1; --i) {
	    r[i] = i + 1;
	    while (r[i] <= n && a[i] > a[r[i]]) r[i] = r[r[i]];
	    if (r[i] <= n && a[i] == a[r[i]]) {
			c[i] = c[r[i]] + 1;
			r[i] = r[r[i]];
		}
	}
	for(int i = 1; i <= n; i ++) {
	    l[i] = i - 1;
	    while (l[i] >= 1 && a[i] > a[l[i]]) l[i] = l[l[i]];
	    if (l[i] >= 1 && a[i] == a[l[i]]) {
			l[i] = l[l[i]];
		}
	}
	LL ans = 0;
	for (int i = 1; i <= n; i ++) {
		ans += c[i];
		if (a[i] == a[1]) continue;
		ans += 2;
		if (l[i] == 1 && r[i] == n + 1) ans--;
	}
	printf("%I64d\n", ans);
	return 0;
}
