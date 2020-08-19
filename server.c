#include "server.h"
#include "err.h"
#include "log.h"
#include "conf.h"
#include "ae.h"
#include "net.h"
#include "handle.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

// global var
char *g_conf_file = "conf/si.conf";
char g_conf_buf[CONF_BUF_SIZE];
siServer server;

void printServerConfig() {
	printf("========== serverConfig ========\n");
	printf("server.config_file => %s\n", server.config_file);
	printf("server.log_file    => %s\n", server.log_file);
	printf("server.log_level   => %d\n", server.log_level);
	printf("server.use_console => %d\n", server.use_console);
	printf("server.ip          => %s\n", server.ip);
	printf("server.port        => %d\n", server.port);
	printf("server.net         => %s\n", server.net);
	printf("================================\n");
}

// server main
int main(int argc, char const *argv[]) {
	// get real dir 
	char *real_path;
	if ((real_path = getcwd(g_conf_buf, sizeof(g_conf_buf))) == NULL) {
		errEcho("getcwd fail");
		return -1;
	}

	// concatenate strings
	char *real_conf_file;
	real_conf_file = strcat(g_conf_buf, "/");
	real_conf_file = strcat(g_conf_buf, g_conf_file);
	server.config_file = real_conf_file;

	// load config file to struct
	int is_config_ok;
	if ((is_config_ok = loadConfig(server.config_file)) < 0) {
		errEcho("load config file fail");
		return -1;
	}
	printServerConfig();

	// init log
	int is_log_ok;
	if ((is_log_ok = initLog(server.log_level, server.log_file, server.use_console)) < 0) {
		errEcho("init logger fail");
		return -1;
	}

	LOG_INFO("server should start, ip:%s, port:%d", server.ip, server.port);

	// init
	// 
	// 1. 初始化服务器需要的变量
	// 2. 生成进程pid文件
	// 3. 变为daemon后台进程
	// 4. 开始网络事件循环
	// serverInit();

	// // start eventloop
	// aeMain();

	// // delete eventloop
	// aeDeleteEventLoop();

	// 单进程-基本网络
	if (strcmp(server.net, "base") == 0 ) {

		// 安装信号处理程序
		struct sigaction sa;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		sa.sa_handler = baseGrimReaper;
		if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		    errEcho("sigaction err");
		    return -1;
		}

		int lfd = baseListen(server.ip, server.port);
		if (lfd == -1) {
			LOG_ERROR("baseListen err: %s", strerror(errno));
			errEcho("baseListen err");
			return -1;
		}

		int afd;
		for (;;) {
			afd = accept(lfd, NULL, NULL);
			if (afd == -1) {
				errEcho("accept err");
				return -1;
			}

			switch(fork()) {
				case -1:
					close(afd);
					LOG_INFO("server fork err");
					errEcho("fork err");
					return -1;
				case 0:
					close(lfd);
					handleBaseRequest(afd);
					_exit(EXIT_SUCCESS);
				default:
				 	close(afd);
					break;
			}
		}

	// IO多路复用
	} else if (strcmp(server.net, "multiio") == 0) {
		


	// 进程池
	} else if (strcmp(server.net, "pool") == 0) {

	}


	return 0;
}

