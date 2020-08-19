#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_


typedef enum {
	CMD_TYPE_STRING = 0,
	CMD_TYPE_HASH,
	CMD_TYPE_LIST,
} cmdType;

// 解析文本协议
typedef struct si_protobuf {
	cmdType cmd_type;
	char* cmd;
	char* key;
	char* value;
} si_protobuf;


/*
	type|cmd|key|value
 */
int protocalParse(char *buf, struct si_protobuf *sipb);

#endif
