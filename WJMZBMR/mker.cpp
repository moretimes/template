#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

int main ()
{
	srand(time(0));
	int N = 20;
	printf("%d\n", N);
	for (int i = 1; i <= N; i ++) {
		t = rand() % 100 + 1;
		while(!vis[t]) t = rand() % 100 + 1;
		vis[t] = true;
		printf("%c %d\n", "+-"[rand() % 2], rand() % 100 + 1);
	}
	return 0;
}

