#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "protocol.h"


int lookupCommandAndExe(struct si_protobuf *sipb, char *response_buf);

#endif
