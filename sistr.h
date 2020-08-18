#ifndef _SI_STR_H_
#define _SI_STR_H_

// 定义简单字符串数据结构
typedef struct _si_str {
	int len;  // 字符串长度
	int size; // 字符串容量
	char str[1]; // 字符串BUF
} sistr;


sistr *sistr_new(uint32_t len, uint32_t size);
sistr *sistr_init(const char *c_str);
sistr *sistr_cat(sistr *head, sistr *tail);
sistr *sistr_dup(sistr *sistr);

#endif
