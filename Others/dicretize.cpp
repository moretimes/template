b[++b_c] = a[i];
sort (b + 1, b + 1 + b_c);
b_c = unique (b + 1, b + 1 + b_c) - (b + 1);
for (int i = 1; i <= n; i ++)
    a[i] = lower_bound (b + 1, b + 1 + b_c, a[i]) - b;
