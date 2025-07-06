#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int encrypt(int a, int b) {
	return a ^ b;
}

int main() {
	puts("Begin\n");
	srand(time(0));
	puts("Hello, World!\n");
	printf("%d\n", encrypt((rand() % 100), (rand() % 100)));
}
