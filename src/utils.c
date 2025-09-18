
#include "philo.h"

void	error_exit(char *error)
{
	printf("%s\n", error);
}

long	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}
