/**
 * Copyright ? 2016 Authors. All rights reserved.
 * 
 * FileName: L.cpp
 * Author: SYSU_Team3 <msy5>
 * Date: 2016-04-13
 */
#include <bits/stdc++.h>

using namespace std;

#define rep(i,n) for (int i = 0; i < (n); ++i)
#define For(i,s,t) for (int i = (s); i <= (t); ++i)
#define foreach(i,c) for (__typeof(c.begin()) i = c.begin(); i != c.end(); ++i)

typedef long long LL;

const int inf = 0x3f3f3f3f;
const LL infLL = 0x3f3f3f3f3f3f3f3fLL;
const int N = 201000;
double Time;
struct Q {
        int x, y, r;
        double getX(bool flag) {
                if (flag) return x + r;
                else return x - r;
        }
        double getY(bool flag) {
                double ret = sqrt(1.0 * r * r - (Time - x) * (Time - x));
                if (flag) return   y + ret;
                else return y - ret;
        }
        void scan() {
                scanf("%d%d%d", &x, &y, &r);
        }
}p[N];
struct E {
        int x, y, id;
        bool flag;
        E() {}
        E(int x, int y, int id, bool flag) : x(x), y(y), id(id), flag(flag) {}
        bool operator < (const E& a) const {
                return x == a.x ? y < a.y : x < a.x;
        }
}event[N];
struct P {
        int id;
        bool flag;
        P () {}
        P (int id, bool flag) : id(id), flag(flag) {}
        bool operator < (const P& a) const {
                double y1 = p[id].getY(flag);
                double y2 = p[a.id].getY(a.flag);
                return y1 < y2 || y1 == y2 && flag < a.flag;
        }
        bool operator == (const P& a) const {
                return id == a.id;
        }
};
set<P> ss;
set<P>::iterator up, dn;
int n, fa[N], key[N], nxt[N], head[N], cnt;
void add(int x, int y) {
        key[cnt] = y;
        nxt[cnt] = head[x];
        head[x] = cnt++;
        fa[y] = x;
}
void init() {
        ss.clear();
        cnt = 0;
        memset (head, -1, sizeof head);
}
int sg(int u) {
        if (head[u] == -1) return 0;
        int t = 0;
        for (int i = head[u]; ~ i; i = nxt[i]) {
                int v = key[i];
                t = t ^ (sg(v) + 1);
        }
        return t;
}
void solve() {
        scanf("%d", &n);
        for (int i = 1; i <= n; i ++) {
                p[i].scan();
                event[i] = E(p[i].getX(0), p[i].y, i, 0);
                event[n + i] = E(p[i].getX(1), p[i].y, i, 1);
        }
        sort(event + 1, event + 1 + n + n);
        for (int i = 1; i <= n; i ++)
                fa[i] = i;
        for (int i = 1; i <= n + n; i ++) {
                Time = event[i].x;
                if (event[i].flag == 0) {
                        if (ss.empty()) {
                                ss.insert(P(event[i].id, 0));
                                ss.insert(P(event[i].id, 1));
                                add(0, event[i].id);
                                continue;
                        }
                        up = ss.upper_bound(P(event[i].id, 1));
                        dn = ss.lower_bound(P(event[i].id, 0));
                        if (dn == ss.begin() || up == ss.end())
                                add(0, event[i].id);
                        else {
                                dn--;
                                int t1 = up->id;
                                int t2 = dn->id;
                                if (t1 == t2)
                                        add(t1, event[i].id);
                                else if (fa[t1] == fa[t2])
                                        add(fa[t1], event[i].id);
                                else if (fa[t1] == t2)
                                        add(t2, event[i].id);
                                else if (fa[t2] == t1)
                                        add(t1, event[i].id);
                                else
                                        add(0, event[i].id);
                        }
                        ss.insert(P(event[i].id, 0));
                        ss.insert(P(event[i].id, 1));
                } else {
                        ss.erase(ss.find(P(event[i].id, 0)));
                        ss.erase(ss.find(P(event[i].id, 1)));
                }
        }
        for (int i = 1; i <= n; i ++) {
                printf("%d: ", i);
                for (int j = head[i]; ~ j; j = nxt[j])
                        printf("%d ", key[j]);
                printf("\n");
        }
        printf("%s\n", sg(0) ? "Alice" : "Bob");
}
int main()
{
        freopen("L.in", "r", stdin);
        int T;
        scanf("%d", &T);
        while(T --) {
                init();
                solve();
        }
        return 0;
}
