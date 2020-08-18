#include "sistr.h"

#include <stdio.h>
#include <stdlib.h>

sistr *sistr_new(uint32_t size) {
	sistr *str = (sistr *)malloc(sizeof(sistr) + size);
	if (str == NULL) {
		return NULL;
	}
	str->len = 0;
	str->size = size;
	str->str = str+(sizeof(sistr)-1);

	return str;
}

sistr *sistr_init(const char *c_str, uint32_t size) {
	sistr *str = sistr_new(size);
	str->len = strlen(c_str);
	memcopy(str->str, c_str, str->len);
	return str;
}

sistr *sistr_cat(sistr *head, sistr *tail) {
	if ((head->size - head->len) >= tail->len) {
		memcopy(head->str+head->len, tail->str, tail->len);
	} else {
		si_realloc()
	}
}
sistr *sistr_dup(sistr *sistr);







#ifdef _SISTR_TEST


int main(int argc, char const *argv[])
{
	fpritnf(stdout, "start sistr to test\n");
	return _SISTR_TEST();
}


#endif
