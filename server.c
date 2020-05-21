#include "server.h"
#include "err.h"
#include "log.h"
#include "conf.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>

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


	Info("server is staring, ip:%s, port:%d", server.ip, server.port);


	// create net server ... TODO

	
	return 0;
}

