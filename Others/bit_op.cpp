bool test(int s, int i) {
	return (s >> i) & 1;
}
void set(int& s, int i) {
	s |= (1 << i);
}

void flip(int &s, int i) {
	s ^= (1 << i);
}
void clear(int& s, int i) {
	if (test(s, i))
		flip(s, i);
}
int count(int s) {
	int z = 0;
	for (int i = 0; i < 8 * sizeof(s); i ++)
		if (test(s, i))
			z ++;
	return z;
}
