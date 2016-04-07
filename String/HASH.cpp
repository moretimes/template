const int N = 400000, M = 5000000, HEAD = 399997;
const int P = 1e9 + 7;
struct HASH {
	int cnt, head[N], next[M], len[M];
	LL key[M];
	HASH() {
		clear();
	}
	inline void clear() {
		memset (head, -1, sizeof head);
		cnt = 0;
	}
	inline void ADD(int x, LL y, int w) {
		key[cnt] = y;
		next[cnt] = head[x];
		len[cnt] = w;
		head[x] = cnt ++;
	}
	inline int GETHEAD(LL idx) {
		return idx % HEAD;
	}
	inline void add(LL idx, int w) {
		int h = GETHEAD(idx);
		ADD(h, idx, w);
	}
	bool find(LL idx, int w) {
		int h = GETHEAD(idx);
		for (int i = head[h]; ~ i; i = next[i])
			if (key[i] == idx && len[i] == w)
				return true;
		return false;
	}
}mp;
