#include "handle.h"
#include "log.h"

#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

#define BUF_SIZE 4096

void baseGrimReaper(int sig) {
	int savedErrno, pid;

	savedErrno = errno;
	while((pid = waitpid(-1, NULL, WNOHANG)) > 0) {
		LOG_INFO("waitpid return; pid: %d", pid);
		continue;
	}
	errno = savedErrno;
}

int handleBaseRequest(int afd) {
	// 解析命令
	// 查找命令
	// 执行命令
	// 返回结果

	ssize_t num_read;
	char buf[BUF_SIZE];

	while ((num_read = read(afd, buf, BUF_SIZE)) > 0) {
		if (write(afd, buf, num_read) != num_read) {
			LOG_ERROR("handleBaseRequest write err: %s", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}

	if (num_read == -1) {
		LOG_ERROR("handleBaseRequest read err: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
}