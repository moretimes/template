#include <bits/stdc++.h>
using namespace std;
#define next nxt
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define dwn(i, s, t) for (int i = s; i >= t; i--)
#define edg(i, x) for (int i = head[x]; ~ i; i = next[i])
#define ctn(i, x) for (i = x.begin(); i != x.end(); i++)
#define clr(x) memset ((x), 0, sizeof (x))
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
const double eps = 1e-8;
const int INF = 0x3f3f3f3f;
double nowx;
int n, C, m;
const int N = 3001000;
int ans[N];
double cmp(double x) {
	return x < -eps ? -1 : x > eps;
}
struct Q {
	double x1, x2, y1, y2;
	bool vert, high;
	Q() {}
	Q(double x1, double y1, double x2, double y2) :
		x1(x1), y1(y1), x2(x2), y2(y2) {
		if (cmp(y1 - y2) == 0) vert = true;
		else vert = false;
		if (y2 > y1) high = true;
		else high = false;
	}
	double getY() {
		//if (cmp(x1 - x2) == 0) return y1;
		return y1 + (y2 - y1) / (x2 - x1) * (nowx - x1);
		//return y1;
	}
}a[N];

struct E {
	double x, y;
	int id;
	bool pos;
	E() {}
	E(double x, double y, int id, bool pos) :
		x(x), y(y), id(id), pos(pos) {}
	bool operator<(const E& a) const {
		if (cmp(x - a.x) == 0)
			if (pos == a.pos)
				return y < a.y;
			else return pos < a.pos;
		else return x < a.x;
	}
}event[N];

struct P {
	int id;
	P() {}
	P(int id) : id(id) {}
	bool operator<(const P& p) const{
		double y1 = a[id].getY();
		double y2 = a[p.id].getY();
		
		return y1 < y2;
	}
	bool operator==(const P& p) const {
		return id == p.id;
	}
};
int fa[N], top[N];
int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
set<P> st;
set<P>::iterator it, cit, sit[N];

double rec[N];
void init() {
	clr(top);
	clr(ans);
	clr(rec);
}
void solve() {
	
	int cnt = 0;
	rep(i, 1, n) {
		double x1, x2, y1, y2;
		scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
		if (x1 > x2) swap(x1, x2), swap(y1, y2);
		a[i] = Q(x1, y1, x2, y2);
		//printf("%d %d\n", a[i].vert, a[i].high);
		event[++cnt] = E(x1, y1, i, 0);
		event[++cnt] = E(x2, y2, i, 1);
		fa[i] = i;
	}
	sort(event + 1, event + 1 + cnt);
	rep(i, 1, cnt) {
		nowx = event[i].x;
		int id = event[i].id;
		if (a[id].vert) {
			if (event[i].pos == 0) sit[id] = st.insert(P(id)).first;
			else st.erase(sit[id]);
			continue;
		}
		if (event[i].pos == 0) {
			it = st.insert(P(id)).first;
			sit[id] = it;
			if (a[id].high == 0) {
				if (++it == st.end()) {
					top[id] = INF;
				} else {
					cit = it;
					if (a[cit->id].vert == false)
						fa[id] = find(cit->id);
					else
						top[id] = cit->id;
				}
			}
		} else {
			it = sit[id];
			if (it == st.end()) printf("%d\n", id);
			if (a[id].high == 1) {
				if (++it == st.end()) {
					top[id] = INF;
				} else {
					cit = it;
					if (a[cit->id].vert == false)
						fa[id] = find(cit->id);
					else
						top[id] = cit->id;
					
				}
			}
			st.erase(sit[id]);
		}
	}
	rep(i, 1, n) {
		fa[i] = find(fa[i]);
		//printf("%d\n", fa[i]);
	}
	rep(i, 1, m) {
		scanf("%lf", &rec[i]);
		a[n + i] = Q(rec[i], 0, rec[i], 0);
		event[++cnt] = E(rec[i], 0, i + n, 1);
	}
	sort(event + 1, event + 1 + cnt);
	st.clear();
	rep(i, 1, cnt) {
		nowx = event[i].x;
		int id = event[i].id;
		if (id > n) {
			if (st.size()) {
				it = st.lower_bound(P(id));
				ans[id - n] = it->id;
			} else {
				ans[id - n] = -1;
			}
			continue;
		}
		if (a[id].vert) {
			if (event[i].pos == 0) sit[id] = st.insert(P(id)).first;
			else st.erase(sit[id]);
			continue;
		}
		if (event[i].pos == 0) {
			sit[id] = st.insert(P(id)).first;
		} else {
			st.erase(sit[id]);
		}
	}
	
	rep(i, 1, m) {
		if (ans[i] == -1) {
			printf("%.0lf\n", rec[i]);
		} else {
			ans[i] = fa[ans[i]];
			if (top[ans[i]] == INF) {
				double tmp;
				if (a[ans[i]].high == 0)
					printf("%.0lf\n", a[ans[i]].x1);
				else
					printf("%.0lf\n", a[ans[i]].x2);
			} else {
				if (a[ans[i]].vert == true) {
					printf("%.0lf %.0lf\n", rec[i], a[ans[i]].y1);
					continue;
				}
				if (a[ans[i]].high == 0)
					printf("%.0lf %.0lf\n", a[ans[i]].x1, a[top[ans[i]]].y1);
				else
					printf("%.0lf %.0lf\n", a[ans[i]].x2, a[top[ans[i]]].y2);
			}
		}
	}
	
	
}
int main() {
	while(scanf("%d%d", &n, &m) != EOF) {
		init();
		solve();
	}
	return 0;
}