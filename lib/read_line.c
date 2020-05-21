#include "read_line.h"
#include <unistd.h> // read
#include <errno.h>  // errno

int readLine(int fd, void *buffer, int n) {
	int read_num, tot_read;

	char *buf;
	char ch;

	if (n < 0 || buffer == NULL) {
		errno = EINVAL; // 设置错误号
		return -1;
	}

	buf = buffer;
	tot_read = 0;
	for(;;) {
		read_num = read(fd, &ch, 1);
		// TODO
		if (read_num == -1) {
			if (errno == EINTR) // ctrl + c 中断；继续读取
				continue;
			else
				return -1;
		} else if( read_num == 0) {
			if (tot_read == 0)
				return 0;
			break;
		} else {
			if (tot_read < (n-1)) {
				tot_read++;
				*buf++ = ch;
			}
			if (ch == '\n')
                break;
		}
	}

	*buf = '\0';
	return tot_read;

}