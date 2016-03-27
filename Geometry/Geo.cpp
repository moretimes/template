#include <cstdio>
#include <deque>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const double eps = 1e-10;
int dcmp(double x) {
	return x < -eps ? -1 : x > eps;
}
const double pi = acos(-1.0);
inline double sqr(double x) {
	return x * x;
}
struct point {
	double x, y;
	point() : x(0), y (0) {}
	point(double a, double b) : x(a), y(b) {}
	void input() {
		scanf("%lf%lf", &x, &y);
	}
	void print() {
	    printf("%lf %lf\n", x, y);
    }
	friend point operator +(const point &a, const point &b) {
		return point(a.x + b.x, a.y + b.y);
	}
	friend point operator -(const point &a, const point &b) {
		return point(a.x - b.x, a.y - b.y);
	}
	friend bool operator ==(const point &a, const point &b) {
		return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
	}
	friend point operator *(const double &a, const point &b) {
		return point(a * b.x, a * b.y);
	}
	friend point operator *(const point &b, const double &a) {
		return point(a * b.x, a * b.y);
	}
	friend point operator /(const point &a, const double &b) {
		return point(a.x / b, a.y / b);
	}
	double norm() const {
		return sqrt(sqr(x) + sqr(y));
	}
};
double det(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}
double dis(const point &a, const point &b) {
	return (a - b).norm();
}
point rotate(const point &p, double A) {
	double tx = p.x, ty = p.y;
	return point(tx * cos(A) - ty * sin(A), tx * sin(A) + ty * cos(A));
}

struct line {
	point a, b;
	double ang;
	line() {}
	line(point x, point y) : a(x), b(y) {
		ang = atan2(b.y - a.y, b.x - a.x);
	}
	void input() {
		a.input();
		b.input();
	}
};

//line and seg are different

double dis(const point p, const point s, const point t) {  
	if (dcmp(dot(p - s, t - s)) == -1) return (p - s).norm();
	if (dcmp(dot(p - t, s - t)) == -1) return (p - t).norm();
	return fabs(det(s - p, t - p) / dis(s, t));
}
void proj(const point p, const point s, const point t, point &cp) {
	double r = dot((t - s), (p - s)) / dot(t - s, t - s);
	cp = s + r * (t - s);
}
bool onseg(point p, point s, point t) {
	return dcmp(det(p - s, t - s)) == 0 && dcmp(dot(p - s, p - t)) <= 0;
}
bool parallel(line a, line b) {
	return dcmp(det(a.a - a.b, b.a - b.b)) == 0;
}
bool inter(line a, line b) {
	double c1 = det(b.a - a.a, a.b - a.a), c2 = det(b.b - a.a, a.b - a.a);
	double c3 = det(a.a - b.a, b.b - b.a), c4 = det(a.b - b.a, b.b - b.a);
	return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
point interpoint(line a, line b) {
	//if (inter(a, b) == false) return false;
	point u = a.a - b.a;
	point v = a.b - a.a;
	point w = b.b - b.a;
	double t = det(w, u) / det(v, w);
	return a.a + v * t;
}
line move_d(line a, const double &len) {
	point d = a.b - a.a;
	d = d / d.norm();
	d = rotate(d, pi / 2);
	return line(a.a + d * len, a.b + d * len);
}
bool cmpxy(const point &a, const point &b) {
	if (dcmp(a.x - b.x) == 0)
		return a.y < b.y;
	return a.x < b.x;
}
#define points vector<point>
#define lines vector<line>
#define next(x) ((x) + 1) % n
double area(points &p) {
	double z = 0;
	for (int i = 0; i < (int)p.size() - 1; i ++)
		z += det(p[i] - p[0], p[i + 1] - p[0]);
	return fabs(z) / 2;
}
void convex_hull(points &a, points &res) {
	res.resize(2 * a.size() + 10);
	sort(a.begin(), a.end(), cmpxy);
	a.erase(unique(a.begin(), a.end()), a.end());
	int m = 0;
	for (int i = 0; i < (int)a.size(); i ++) {
		while(m > 1 && dcmp(det(res[m - 1] - res[m - 2], a[i] - res[m - 2])) <= 0) --m;
		res[m++] = a[i];
	}
	int k = m;
	for (int i = (int)a.size() - 2;  i >= 0; i --) {
		while(m > k && dcmp(det(res[m - 1] - res[m - 2], a[i] - res[m - 2])) <= 0) --m;
		res[m++] = a[i];
	}
	res.resize(m);
	//if (a.size() > 1) res.resize(m - 1);
}
void cut(points &p, point b, point a, points &res) {
	res.clear();
	int n = p.size();
	for (int i = 0; i < n; i ++) {
		point c = p[i];
		point d = p[next(i)];
		if (dcmp(det(b - a, c - a)) >= 0) res.push_back(c);
		if (dcmp(det(b - a, c - d)) != 0) {
			point cp = interpoint(line(a, b), line(c, d));
			if (onseg(cp, c, d)) res.push_back(cp);
		}
	}
}

bool onleft(point a, line p) {
	return dcmp(det(a - p.a, p.b - p.a)) < 0;
}
bool cmpang(const line &a, const line &b) {
	if (dcmp(a.ang - b.ang) == 0)
		return onleft(a.a, b);
	return a.ang < b.ang;
}
int halfplane(lines &v, points &res) {
	sort(v.begin(), v.end(), cmpang);
	deque<line> q;
	deque<point> ans;
	q.push_back(v[0]);
	for (int i = 1; i < int(v.size()); i ++) {
		if (dcmp(v[i].ang - v[i - 1].ang) == 0) continue;
		while(ans.size() && !onleft(ans.back(), v[i])) {
			ans.pop_back();
			q.pop_back();
		}
		while(ans.size() && !onleft(ans.front(), v[i])) {
			ans.pop_front();
			q.pop_front();
		}
		ans.push_back(interpoint(q.back(), v[i]));
		q.push_back(v[i]);
	}
	while(ans.size() && !onleft(ans.back(), q.front())) {
		ans.pop_back();
		q.pop_back();
	}
	while(ans.size() && !onleft(ans.front(), q.back())) {
		ans.pop_front();
		q.pop_front();
	}
	ans.push_back(interpoint(q.back(), q.front()));
	res = points(ans.begin(), ans.end());
	return ans.size(); //you must use the size to assure an empty set, area dont has the accuracy we need
}
const int N = 50010;
point p[N];
int n;
double r;
void init() {
}
double mysqrt(double x) {
    return sqrt(max(0.0, x));
}
void circle_inter_line(point a, point b, point o, double r, point ret[], int &num) {
    point p = b - a;
    point q = a - o;
    double A = dot(p, p);
    double B = 2 * dot(p, q);
    double C = dot(q, q) - sqr(r);
    double delta = B * B - 4 * A * C;
    num = 0;
    if (dcmp(delta) >= 0) {
        double t1 = (-B - mysqrt(delta)) / (2 * A);
        double t2 = (-B + mysqrt(delta)) / (2 * A);
        if (t1 <= 1 && t1 >= 0) {
            ret[num++] = a + t1 * p;
        }
        if (t2 <= 1 && t2 >= 0) {
            ret[num++] = a + t2 * p;
        }
    }
}
    
double sector_area(const point &a, const point &b) {
    double theta = atan2(a.y, a.x) - atan2(b.y, b.x);
    while(theta <= 0) theta += 2 * pi;
    while(theta > 2 * pi) theta -= 2 * pi;
    theta = min(theta, 2 * pi - theta);
    return r * r * theta / 2;
}
double calc(const point &a, const point &b) {
    point p[2];
    int num = 0;
    int ina = dcmp(a.norm()- r) < 0;
    int inb = dcmp(b.norm() - r) < 0;
    if (ina) {
        if (inb) {
            return fabs(det(a, b)) / 2;
        } else {
            circle_inter_line(a, b, point(0, 0), r, p, num);
            return sector_area(b, p[0]) + fabs(det(a, p[0])) / 2;
        }
    } else {
        if (inb) {
            circle_inter_line(a, b, point(0, 0), r, p, num);
            return sector_area(p[0], a) + fabs(det(p[0], b)) / 2;
        } else {
            circle_inter_line(a, b, point(0, 0), r, p, num);
            if (num == 2) {
                return sector_area(a, p[0]) + sector_area(p[1], b) + fabs(det(p[0], p[1])) / 2;
            } else {
                return sector_area(a, b);
            }
        }
    }
}
double area() {
    double ret = 0;
    for (int i = 0; i < n; i ++) {
        int sgn = dcmp(det(p[i], p[i + 1]));
        if (sgn) {
            ret += sgn * calc(p[i], p[i + 1]);
        }
    }
    return ret;
}
void solve() {
    scanf("%d", &n);
   	for (int i = 0; i < n; i ++)
   		p[i].input();
   	p[n] = p[0];
   	printf("%.2lf\n", fabs(area()) + eps);
   	
}
int main() {
	while(scanf("%lf", &r) != EOF) {
	    init();
		solve();
	}
	return 0;
}
