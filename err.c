#include "err.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int errExit(char *err_str, int err_code) {
	printf("[errno: %d] => %s, err: %s\n", errno, strerror(errno), err_str);
	exit(err_code);
}

void errEcho(char *err_str) {
	printf("[errno: %d] => %s, err: %s\n", errno, strerror(errno), err_str);
}
