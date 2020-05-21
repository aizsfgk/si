#include "log.h"
#include "err.h"

#include <stdio.h>  // snprintf; fopen
// #include <stdlib.h> // 
#include <stdarg.h> // va_list
#include <time.h>   // time_t
// #include <string.h>

static const char *LEVEL_NAMES[] = {"DEBUG", "INFO", "WARN", "ERROR"};

static int enable_console = 1;
static FILE *log_stream = NULL;
static int log_level = INFO;

int initLog(int level, const char *file, int use_console) {
	FILE *stream = NULL;
	int res = 0;

	if (level > ERROR)
		level = ERROR;
	if (level < DEBUG)
		level = DEBUG;
	log_level = level;
	enable_console = use_console;

	if (file != NULL) {
		// use standard
		stream = fopen(file, "a");
		if (stream == NULL) {
			errEcho("fopen log file ret NULL");
			res = -1;
		} else {
			log_stream = stream;
		}
	}

	return res;
}

void logging(int level, const char *file, const int line, const char *fmt, ...) {
	if (level < log_level)
		return;

	char buffer[LOG_BUFFER_SIZE], *ptr = buffer;
	int size, cap = LOG_BUFFER_SIZE;

	time_t ts;
	struct tm *tmp;

	ts = time(NULL); // return timestamp
	tmp = localtime(&ts);
	size = strftime(ptr, cap, "[%Y-%m-%d %H:%M:%S]", tmp);
	ptr += size;
	cap -= size;

	size = snprintf(ptr, cap, "[%-5s][%s:%d] ", LEVEL_NAMES[level], file, line);
	ptr += size;
	cap -= size;

	va_list ap;
	va_start(ap, fmt);
	size = vsnprintf(ptr, cap, fmt, ap);
	va_end(ap);

	ptr += size;
	*ptr = '\n';
	*(ptr+1) = '\0';

	if (enable_console) {
		if (level >= WARN) {
			fputs(buffer, stderr);
		} else {
			fputs(buffer, stdout);
		}
	}

	if (log_stream != NULL) {
		fputs(buffer, log_stream);
	}
}

void endLog() {
	if (log_stream != NULL)
		fclose(log_stream);
}

