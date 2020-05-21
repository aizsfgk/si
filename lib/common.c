#include "common.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void ltrim(char *ori_str) {
	char *p;
	p = ori_str;
	while (isspace(*p)) {
		*p++;
	}
	strcpy(ori_str, p);
}

void rtrim(char *ori_str) {
	int i;
	i = strlen(ori_str) - 1;
	while (isspace(ori_str[i]) && i>=0) {
		i--;
	}
	ori_str[i+1] = '\0';
}

void trim(char *ori_str) {
	ltrim(ori_str);
	rtrim(ori_str);
}
