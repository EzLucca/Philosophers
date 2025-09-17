
#include "philo.h"

static void	input_msg()
{
		printf("Invalid argument.\n");
		printf("Correct usage: ./philo [1] [2] [3] [4] [5]\n");
		printf("./philo: the executable.\n");
		printf("[1]: Number of philosophers(>2).\n");
		printf("[2]: Time in ms to die.\n");
		printf("[3]: Time in ms to eat.\n");
		printf("[4]: Time in ms to sleep.\n");
		printf("Optional argument:\n");
		printf("[5]: Times that each philosopher eat on the simulation.\n");
}

static void	init_data(t_data *data)
{
	data->n_philos = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->cycle = 0;
	data->start_time = 0;
	data->philo = NULL;
}

int	main(int argc, char **argv)
{
	t_data		*data;

	if (argc != 5 && argc != 6)
	{
		input_msg();
		return (1);
	}
	if (check_args(argv) == false)
	{
		input_msg();
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (2);
	init_data(data);
	parse_input(data, argv);
	// init_dinner();
	// clean_kitchen();
}
