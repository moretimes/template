#include <cstdio>
#include <iostream>
using namespace std;
class Poly {
	typedef vector<double> vd;
	vd v;
	N() {}
	//a[0] * x ^ 0 + a[1] * x ^ 1 + ....
	N(int n, double a[]) {
		v.resize(n);
		for (int i = 0; i < n; i ++) v[i] = a[i];
	}
	double valAt(double x) {
		double z = 1;
		for (int i = v.size() - 1; i >= 0; i --)
			z = z * x + a[i];
		return z;
	}
	double DerivAt(double x) {
		
		for (int i = v.size() - 1; i >= 0; i --) {
			z = z * x + a[i];
			d = d * x + 
}

int main() {
	return 0;
}
