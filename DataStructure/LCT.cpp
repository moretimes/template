#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <climits>
#include <numeric>
#include <vector>
using namespace std;
#define rep(i, s, t) for (int i = s; i <= t; i ++)
typedef int int64;
const int LEN = 3001000;
namespace LCT {
	struct Node {
		Node*p, *ch[2];
		int64 add, val;
		int size;
		bool isRoot;
		Node*fa;
		Node() {
			add = val = 0;
			isRoot = 0;
			size = 0;
		}
		void sc(Node*c, int d) {
			ch[d] = c;
			c->p = this;
		}
		bool d() {
			return this == p->ch[1];
		}
		void pushup() {
			size = 1 + ch[0]->size + ch[1]->size;
		}
		void apply(int x) {
			add += x;
			val += x;
		}
		void pushdown();
		void setRoot(Node*f);
	} Tnull, *null = &Tnull;
	void Node::setRoot(Node*f) {
		fa = f;
		isRoot = true;
		p = null;
	}
	void Node::pushdown() {
		if (add) {
			rep(i, 0, 1)
				if (ch[i] != null)
					ch[i]->apply(add);
			add = 0;
		}
	}
	Node*make(int v) {
		Node* C = new Node();
		C->val = v;
		C->add = 0;
		C->ch[0] = C->ch[1] = null;
		C->isRoot = true;
		C->p = null;
		C->fa = null;
		return C++;
	}
	void rot(Node*t) {
		Node*p = t->p;
		p->pushdown();
		t->pushdown();
		bool d = t->d();
		p->p->sc(t, p->d());
		p->sc(t->ch[!d], d);
		t->sc(p, !d);
		p->pushup();
		if (p->isRoot) {
			p->isRoot = false;
			t->isRoot = true;
			t->fa = p->fa;
		}
	}
	void pushTo(Node*t) {
		static Node*stk[LEN];
		int top = 0;
		while (t != null) {
			stk[top++] = t;
			t = t->p;
		}
		for (int i = top - 1; i >= 0; --i)
			stk[i]->pushdown();
	}
	void splay(Node*u, Node*f = null) {
		pushTo(u);
		while (u->p != f) {
			if (u->p->p == f)
				rot(u);
			else
				u->d() == u->p->d() ? (rot(u->p), rot(u)) : (rot(u), rot(u));
		}
		u->pushup();
	}
	Node* expose(Node*u) {
		Node*v;
		for (v = null; u != null; v = u, u = u->fa) {
			splay(u);
			u->ch[1]->setRoot(u);
			u->sc(v, 1);
			v->fa = u;
		}
		return v;
	}
	void makeRoot(Node*u) {
		expose(u);
		splay(u);
	}
	void addEdge(Node*u, Node*v) {
		makeRoot(v);
		v->fa = u;
	}
	void delEdge(Node*u, Node*v) {
		makeRoot(u);
		expose(v);
		splay(u);
		u->sc(null, 1);
		u->pushup();
		v->fa = null;
		v->isRoot = true;
		v->p = null;
	}
	void markPath(Node*u, Node*v, int x) {
		makeRoot(u);
		expose(v);
		splay(v);
		v->apply(x);
	}
}

struct Q {
	Q *suf, *go[26], *nxt;
	int val;
	LCT::Node* tree;
	Q() :
			suf(0), val(0) {
		memset(go, 0, sizeof go);
		tree = LCT::make(0);
	}
}*root, *last;

void init() {
	root = last = new Q();
}

void extend(int w) {
	Q *p = last, *np = new Q();
	np->val = p->val + 1;
	while (p && !p->go[w])
		p->go[w] = np, p = p->suf;
	if (!p) {
		np->suf = root;
		LCT::addEdge(root->tree, np->tree);
	}
	else {
		Q *q = p->go[w];
		if (p->val + 1 == q->val) {
			np->suf = q;
			LCT::addEdge(q->tree, np->tree);
		} else {
			Q *nq = new Q();
			memcpy(nq->go, q->go, sizeof q->go);
			nq->val = p->val + 1;
			LCT::delEdge(q->suf->tree, q->tree);
			nq->suf = q->suf; LCT::addEdge(q->suf->tree, nq->tree);
			q->suf = nq;  LCT::addEdge(nq->tree, q->tree);
			np->suf = nq; LCT::addEdge(nq->tree, np->tree);
			LCT::pushTo(q->tree);
			nq->tree->val = q->tree->val;
			while (p && p->go[w] == q)
				p->go[w] = nq, p = p->suf;
		}
	}
	last = np;
	markPath(root->tree, np->tree, 1);
	//for (; np; np = np->suf)
	//	np->size++;
}
int query(char *s) {
	Q* now = root;
	for (; *s; s ++) {
		now = now->go[*s - 'A'];
		if (now == 0) return 0;
	}
	LCT::pushTo(now->tree);
	return now->tree->val;
}
void Decode(char s[], int mask) {
	int ls = strlen(s);
	rep(i, 0, ls - 1) {
		mask = (mask * 131 + i) % ls;
		swap(s[i], s[mask]);
	}
}
int mask;
char a[LEN], s[LEN], op[10];
int n;
int main() {
	//freopen("b.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s", a);
	init();
	int la = strlen(a);
	rep(i, 0, la - 1) {
		extend(a[i] - 'A');
	}
	rep(i, 1, n) {
		scanf("%s%s", op, s);
		int ls = strlen(s);
		Decode(s, mask);
		if (op[0] == 'Q') {
			int tmp = query(s);
			mask ^= tmp;
			printf("%d\n", tmp);
		}
		if (op[0] == 'A') {
			rep(i, 0, ls - 1)
				extend(s[i] - 'A');
		}
	}
	return 0;
}
