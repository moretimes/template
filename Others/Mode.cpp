struct Mode {
	int mx, c[N], cnt[N];
	void init() {
		memset(c, 0, sizeof c);
		memset(cnt, 0, sizeof cnt);
		mx = 0;
		cnt[0] = 0x3f3f3f3f;
	}
	void inc(int x) {
		cnt[c[x]]--;
		c[x]++;
		cnt[c[x]]++;
		mx = max(mx, c[x]);
	}
	void dec(int x) {
		cnt[c[x]]--;
		c[x]--;
		cnt[c[x]]++;
		while(cnt[mx] == 0) mx--;
	}
	int get() {
		return mx;
	}
}mode;
