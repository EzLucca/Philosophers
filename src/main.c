#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data		*data;

	data = NULL;
	if (argc != 5 && argc != 6)
	{
		error_exit("Wrong input: ./philo 1 200 200 [5]");
		return (1);
	}
	if (parse_input(data, argv) == false)
	{
		printf("Invalid argument\n");
		return (1);
	}
		
	// init_data();
	// init_dinner();
	// clean_kitchen();
}
