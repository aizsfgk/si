#include "conf.h"
#include "server.h"
#include "read_line.h"
#include "common.h"

#include <stdlib.h> // 这里定义了NULL  atoi
#include <unistd.h> // access
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>   // O_RDONLY
#include <stdio.h>
#include <string.h>

extern siServer server;

static char *zstrdup(const char *s) {
    int l = strlen(s)+1;
    char *p = malloc(l);
    memcpy(p,s,l);
    return p;
}

int loadConfig(const char *conf_file) {
	int is_exists;
	int is_stat;

	// 1. check file is exists?
	//    the file is a regular file?
	if (conf_file == NULL)
		return -1;

	if ((is_exists = access(conf_file, F_OK|R_OK)) < 0) {
		errEcho("file is not exists");
		return -1;
	}

	struct stat st;
	if ((is_stat = stat(conf_file, &st)) < 0) {
		errEcho("stat file fail");
		return -1;
	}
	if (!S_ISREG(st.st_mode)) {
        errEcho("conf file is not regular file");
        return -1;
    }

	
	// 2. open file to read line
	//    if first char is '#'; it's note
	int fd;
	if ((fd = open(conf_file, O_RDONLY)) < 0 ) { // O_RDONLY 只读方式打开
		errEcho("open file fail");
        return -1;
	}

	char line_buf[LINE_SIZE];
	char token[LINE_SIZE/2];
	int n;
	while ((n = readLine(fd, line_buf, LINE_SIZE)) > 0 ) {
		// skip note
		if (line_buf[0] == '#') {
			continue;
		}


		// del space
		trim(line_buf);
		if (strlen(line_buf) == 0) {
			continue;
		}

		char *key = strtok(line_buf, "=");
		char *value = strtok(NULL, "=");
		trim(key);
		trim(value);

		// 日志格式解析
		if (strcmp(key, "log_level") == 0) {
			server.log_level = atoi(value);
		} else if (strcmp(key, "log_file") == 0) {
			server.log_file = zstrdup(value);
		} else if (strcmp(key, "use_console") == 0) {
			server.use_console = atoi(value);
		} else if (strcmp(key, "ip") == 0) {
			server.ip = zstrdup(value);
		} else if (strcmp(key, "port") == 0) {
			server.port = atoi(value);
		} else if (strcmp(key, "net") == 0) {
			server.net = zstrdup(value);
		}
	}

	// 3. load config param to struct var
	return 0;
}
