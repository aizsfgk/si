#include "handle.h"
#include "log.h"
#include "read_line.h"
#include "protocol.h"
#include "command.h"

#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

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

void replyReadZero(int afd) {
	char *str = "this is a null command.\n";
	write(afd, str, strlen(str) + 1);
}

void replyCommand(int afd, char *buf, int num_read) {


	struct si_protobuf sipb;

	if (protocalParse(buf, &sipb) < 0) {
		LOG_ERROR("protocalParse err: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}


	char response_buffer[BUF_SIZE];
	int response_buffer_len;
	if ((response_buffer_len = lookupCommandAndExe(&sipb, response_buffer)) < 0) {
		LOG_ERROR("lookupCommandAndExe err: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}

	LOG_DEBUG("response_buffer_len:%d, response_buffer: %s", response_buffer_len, response_buffer);

	if (write(afd, response_buffer, response_buffer_len) != response_buffer_len) {
		LOG_ERROR("handleBaseRequest write err: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int handleBaseRequest(int afd) {
	// 解析命令
	// 查找命令
	// 执行命令
	// 返回结果

	ssize_t num_read;
	char buf[BUF_SIZE];

	while ((num_read = readLine(afd, buf, BUF_SIZE)) >= 0) {

		trim(buf);
		LOG_DEBUG("readLine: pid: %d, len: %d, buf: %s", getpid(), num_read, buf);

		if (num_read == 0 || strlen(buf) == 0) {
			replyReadZero(afd);
			continue;
		}

		if (strcmp(buf, "quit") == 0) {
			close(afd);
			LOG_INFO("this client is quitted.");
			return 0;
		}


		replyCommand(afd, buf, num_read);
	}

	if (num_read == -1) {
		LOG_ERROR("handleBaseRequest read err: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
}