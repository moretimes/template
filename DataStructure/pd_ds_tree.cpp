#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace std;
using namespace __gnu_pbds; 
const int N = 101000;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> st[N], ed[N];
int t[N], x[N], T, a[N], b[N], b_c;
int main ()
{
    int n, m;
    scanf ("%d", &n);
    for (int i = 1; i <= n; i ++)
        scanf ("%d%d%d", &a[i], &t[i], &x[i]);
    
    b_c = n;
    for (int i = 1; i <= n; i ++)
        b[i] = x[i];
    sort (b + 1, b + 1 + b_c);
    b_c = unique (b + 1, b + 1 + b_c) - (b + 1);
    for (int i = 1; i <= n; i ++)
        x[i] = lower_bound (b + 1, b + 1 + b_c, x[i]) - b;
    
    for (int i = 1; i <= n; i ++) {
    	if (a[i] == 1) {
    		st[x[i]].insert(t[i]);
		}
    	if (a[i] == 2) {
    		ed[x[i]].insert(t[i]);
    	}
    	if (a[i] == 3) {
    		printf("%d\n",
    			st[x[i]].order_of_key(t[i])
    			 - ed[x[i]].order_of_key(t[i]));
    	}
    }
	return 0;
}

