#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static char buf[32];

int openFile(const char *file_name) {
	FILE *fp = fopen(file_name, "r");

	if (fp == NULL || fread(buf, sizeof(buf), 1, fp) != 1) {
		printf("fread file err\n");
		
		return -1;
	} else {
		printf("fread->buf, %s\n", buf);
	}

	if (fp) {
		fclose(fp);
	}

	//
	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("%ld => %ld\n", tv.tv_sec, tv.tv_usec);


	pid_t pid = getpid();
	printf("pid: %d\n", pid);
	return 0;
}

int main(void) {
	openFile("/dev/urandom");
	return 0;
}