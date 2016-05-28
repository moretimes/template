#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAX_N = 1001000 + 10;
const int INF = ~0U >> 1;
struct Node {
	Node*ch[2], *p;
	int size, val, gcd;
	Node() {
		size = 0;
		val = gcd = 0;
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
		gcd = __gcd(ch[0]->gcd, __gcd(ch[1]->gcd, val));
	}
} Tnull, *null = &Tnull;
Node mem[MAX_N], *C = mem;
void Node::relax() {
}
Node*make(int v) {
	C->ch[0] = C->ch[1] = null;
	C->size = 1;
	C->val = v;
	C->gcd = v;
	return C++;
}
Node*root;
Node*rot(Node*t) {
	Node*p = t->p;
	int d = t->d();
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
Node* select(int k) {
	for (Node*t = root;;) {
		t->relax();
		int c = t->ch[0]->size;
		if (k == c)
			return t;
		if (k > c)
			k -= c + 1, t = t->ch[1];
		else
			t = t->ch[0];
	}
}
Node* find(Node* t, int val) {
	bool d = val > t->val;
	if (val == t->val) return t;
	return find(t->ch[d], val);
}
Node* mx(Node* t) {
	for (; ; t = t->ch[1])
		if (t->ch[1] == null) return t;
}
Node* mn(Node* t) {
	for (; ; t = t->ch[0])
		if (t->ch[0] == null) return t;
}
Node* remove(Node* t) {
	splay(t);
	if (root->ch[0] != null) {
		splay(mx(root->ch[0]), root);
		root->ch[0]->setc(root->ch[1], 1);
		root = root->ch[0];
		root->p = null;
		root->upd();
	} else {
		root = root->ch[1];
		root->p = null;
	}
}
Node*&get(int l, int r) { //[l,r)
	Node*L = select(l - 1);
	Node*R = select(r);
	splay(L);
	splay(R, L);
	return R->ch[0];
}
void travel(Node* t) {
	if (t == null) return ;
	travel(t->ch[0]);
	printf("%d ", t->val);
	travel(t->ch[1]);
}
void ins(int val) {
	if (root == null)
		root = make(val), root->p = null;
	else
		splay(insert(root, val));
}
void rm(int val) {
	remove(find(root, val));
}


int n, m;
char s[10];
int x;
int main() {
	scanf("%d", &n);
	root = null;
	for (int i = 1; i <= n; ++i) {
		scanf("%s%d", s, &x);
		if (s[0] == '+') {
			ins(x);
		} else {
			rm(x);
		}
		if (root != null) printf("%d\n", root->gcd);
		else printf("1\n");
	}
}
