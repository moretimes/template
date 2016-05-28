C++

#include <cstdio>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;
#define rep(i,s,t) for(int i=s;i<=t;i++)
#define dwn(i,s,t) for(int i=s;i>=t;i--)
typedef long long LL;
struct Node {
	Node*ch[2], *p;
	int size, val;
	LL sum;
	Node() {
		size = 0;
		val = sum = 0;
	}
	bool d() {
		return this == p->ch[1];
	}
	void setc(Node*c, int d) {
		ch[d] = c;
		c->p = this;
	}
	void relax();
	void upd() {
		size = ch[0]->size + ch[1]->size + 1;
		sum = ch[0]->sum + ch[1]->sum + val;
	}
} Tnull, *null = &Tnull;
Node mem[1001000], *C = mem;
void Node::relax() {
}
Node*make(int v) {
	C->ch[0] = C->ch[1] = null;
	C->size = 1;
	C->val = v;
	C->sum = v;
	return C++;
}
Node*root;
Node*rot(Node*t) {
	Node*p = t->p;
	bool d = t->d();
	p->p->setc(t, p->d());
	p->setc(t->ch[!d], d);
	t->setc(p, !d);
	p->upd();
	if (p == root)
		root = t;
}
void splay(Node*t, Node*f = null) {
	while (t->p != f) {
		if (t->p->p == f)
			rot(t);
		else
			t->d() == t->p->d() ? (rot(t->p), rot(t)) : (rot(t), rot(t));
	}
	t->upd();
}
void random_spaly() {
	if (C - mem < 10) return ;
	int t = rand() % (C - mem - 1) + 1;
	splay(mem + t);
}
Node* insert(Node* t, int val) {
	for (; ; ) {
		bool d = val > t->val;
		if (t->ch[d] == null) {
			Node* p = make(val);
			t->setc(p, d);
			return p;
		}
		t = t->ch[d];
	}
}
int select(LL k) {
	int z = 0;
	for (Node*t = root;;) {
		t->relax();
		if (t == null)
			return z;
		if (k >= t->sum)
			return z + t->size;
		LL c = t->ch[0]->sum + t->val;
		if (k == c)
			return z + t->ch[0]->size + 1;
		if (k > c)
			k -= c, z += t->ch[0]->size + 1, t = t->ch[1];
		else
			t = t->ch[0];
	}
}
void ins(int val) {
	if (root == null)
		root = make(val), root->p = null;
	else
		splay(insert(root, val));
}
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N = 1001000;
int n, T, K, a[N], b[N], c[N], ans;
priority_queue<int> pq;
int main() {
	srand(time(0));
//	freopen("c.in", "r", stdin);
	root = null;
	scanf("%d%d%d", &n, &T, &K);
	rep(i, 1, n) a[i] = read();
	rep(i, 1, n) b[i] = read();
	rep(i, 1, n) c[i] = read();
	LL sum = 0;
	bool flag = false;
	rep(i, 1, n) {
		if (c[i] == 1) {
			pq.push(b[i]);
			sum += b[i];
			if (pq.size() > K) {
				int x = pq.top();
				pq.pop();
				sum -= x;
				ins(x);
			}
		} else
			ins(b[i]);
		if (pq.size() == K) {
			if ((LL)T >= a[i] + sum) 
				flag = true, ans = max(ans, K + select(T - a[i] - sum));
		}
		random_spaly();
	}
	printf("%d\n", flag ? ans : -1);
	return 0;
}

