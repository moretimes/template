for (int i = 1; i <= n; i ++)
	a[i] = (1LL * a[i - 1] * A + B) % p, s[a[i]]++;
for (int i = 1; i <= p; i ++)
	s[i] += s[i - 1];
for (int i = n; i >= 1; i --)
	id[s[a[i]]--] = i;
