
#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_data *data;
	bool	no_death;

	no_death = true;
	data = (t_data *)arg;
	while (no_death)
	{
		if (check_death(data) == true)
			return (NULL);
		usleep(1000);
	}
	return (0);
}
