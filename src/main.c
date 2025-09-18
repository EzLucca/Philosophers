
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
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 5 && argc != 6)
	{
		input_msg(1);
		return (1);
	}
	if (check_args(argv) == false)
	{
		input_msg(1);
		return (1);
	}
	// init_data(&data);
	if (parse_input(&data, argv) == false)
	{
		input_msg(2);
		return (1);
	}
	// init_dinner();
	// clean_kitchen();
	return (0);
}
