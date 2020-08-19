#include "command.h"
#include <string.h>


/**
 * 初始化，注册命令表
 *
 *
 *
 * be daemon
 */

int lookupCommandAndExe(struct si_protobuf *sipb, char *response_buf) {

	memcpy(response_buf, "ok\n", 3);
	return 3;
}