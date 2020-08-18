#ifndef _SI_LOG_H_
#define _SI_LOG_H_

#define LOG_BUFFER_SIZE 512

enum log_level_t {
	DEBUG = 0,
	INFO,
	WARN,
	ERROR
};


// 初始化日志
int initLog(int level, const char *file, int use_console);

void logging(int level,const char *file, const int line, const char *fmt, ...);

#define LOG_DEBUG(fmt, ...)  logging(DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_INFO(fmt, ...) logging(INFO, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_WARN(fmt, ...)  logging(WARN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) logging(ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif
