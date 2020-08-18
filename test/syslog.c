#include <syslog.h>

int main(int argc, char const *argv[])
{
	openlog("zsf", LOG_CONS|LOG_PID, 0);

	syslog(LOG_INFO, "this is a syslog test msg by zsf %s\n", argv[0]);

	closelog();

	return 0;
}