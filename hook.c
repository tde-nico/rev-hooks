#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/socket.h>

#define NAME "my_program"

typedef int (*encrypt_t)(int, int);

encrypt_t encrypt;

void *base = NULL;
void set_base() {
	if (base)
		return;
	int fd = open("/proc/self/maps", O_RDONLY);
	char addr_buf[0x1000];
	assert(read(fd, addr_buf, 0x1000) > 0);
	close(fd);
	char* ptr = strtok(addr_buf, "\n");
	while (ptr != NULL) {
		if (strstr(ptr, NAME)) {
			char* addr = strtok(ptr, "-");
			base = (void*)strtoul(addr, NULL, 16);
			return;
		}
		ptr = strtok(NULL, "\n");
	}
}

void set_symbols() {
	encrypt = (encrypt_t)(base + 0x11C9);
}

// gcc -o hook.so hook.c -shared -fPIC -ggdb && patchelf --add-needed ./hook.so my_program

int calls = 0;
int puts(const char *str) {
	set_base();
	set_symbols();
	calls++;

	int len = strlen(str);
	write(STDOUT_FILENO, str, len);
	if (calls == 2) {
		printf("%d\n", encrypt(1, 2));
	}
	return len;
}
