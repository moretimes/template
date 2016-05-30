struct T {
	int pos, val;
	T(){}
	T(int pos, int val):pos(pos),val(val){}
	bool operator > (const T& a) const {
		return val > a.val;
	}
}q[6001000];
struct Q {	
	int h, t;
	void init() {
		h = 1, t = 1;
	}
	void insert(const T& x) {
		while(t > h && x > q[t - 1]) t--;
		q[t++] = x;
	}
	void pop(int pos) {
		while(t > h && q[h].pos < pos) h++;
	}
	int get() {
		return q[h].val;
	}
}que;
