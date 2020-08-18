#include "net.h"
#include "err.h"
#include "server.h"

#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
struct addrinfo {
   int              ai_flags;
   int              ai_family;
   int              ai_socktype;
   int              ai_protocol;
   size_t           ai_addrlen;
   struct sockaddr *ai_addr;
   char            *ai_canonname;
   struct addrinfo *ai_next;
};



*/
#define BUF_SIZE 500
#define BACKLOG 128

// 基础网络初始化
int baseListen(const char *ip, int port) {

	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, s, optval;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICHOST|AI_NUMERICSERV;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	char port_str[15];
    sprintf(port_str, "%d", port);

	s = getaddrinfo(ip, port_str, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
	}

	optval = 1;
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;

		// 重复使用端口
		if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
            close(sfd);
            freeaddrinfo(result);
            return -1;
        }

		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) {
			break; // success
		}

		close(sfd); // 失败则关闭
	}

	if (rp == NULL) {
		fprintf(stderr, "%s\n", "Cloud not bind");
		exit(EXIT_FAILURE);
	}

	if (listen(sfd, BACKLOG) == -1) {
		close(sfd);
        freeaddrinfo(result);
        return -1;
	}


	freeaddrinfo(result);
	return (rp == NULL) ? -1 : sfd;
}
