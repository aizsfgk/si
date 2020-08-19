#include "protocol.h"

/*
	type|cmd|key|value
	0|set|name|zsf
	0|get|name


	// 维护一个Hash
 */
int protocalParse(char *buf, struct si_protobuf *sipb) {

	sipb->cmd_type = CMD_TYPE_STRING;
	sipb->cmd = "set";
	sipb->key = "zsf-key";
	sipb->value = "zsf-value";


	return 0;
}