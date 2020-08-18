#ifndef _SI_SERVER_H_
#define _SI_SERVER_H_

// 内存|mem
#define si_malloc  malloc
#define si_calloc  calloc
#define si_realloc realloc
#define si_free    free

// 定义一下公用的常量
#define CONF_BUF_SIZE 128

typedef struct _siServer {
	char *config_file;
	char *log_file;
	int log_level;
	int use_console;
	char *ip;
	int port;
	char *net;
} siServer;


void printServerConfig();

#endif
