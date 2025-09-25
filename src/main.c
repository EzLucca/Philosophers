
#include "philo.h"

void	input_msg(int code)
{
	if (code == 1)
	{
		printf("Invalid argument.\n");
		printf("Correct usage: ./philo [1] [2] [3] [4] [5]\n");
		printf("./philo: the executable.\n");
		printf("[1]: Number of philosophers (>2).\n");
		printf("[2]: Time in ms to die (+).\n");
		printf("[3]: Time in ms to eat (+).\n");
		printf("[4]: Time in ms to sleep (+).\n");
		printf("Optional argument:\n");
		printf("[5]: Times that each philosopher eat on the simulation (+).\n");
	}
	if (code == 2)
		printf("Malloc fail.\n");
	if (code == 3)
		printf("Mutex fail.\n");
}

// Used for testing
void print_data(t_data *data)
{
	printf("%ld\n", data->number_philos);
	printf("%ld\n", data->time_to_die);
	printf("%ld\n", data->time_to_eat);
	printf("%ld\n", data->time_to_sleep);
	printf("%ld\n", data->cycle);
	printf("%ld\n", data->start_time);
	printf("%d\n", data->stop_simulation);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc == 5 || argc == 6)
	{
		if (check_args(argv) == false)
			return (2);
		parse_input(&data, argv);
		print_data(&data); // TESTING:
		if (prepare_meal(&data) == false)
			return (3);
		// start_dinner();
		destroy_free_mutex(&data, data.number_philos);
		return (0);
	}
	input_msg(1);
	return (1);
}
