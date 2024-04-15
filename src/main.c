/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uurbizu- <uurbizu-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:08:54 by uurbizu-          #+#    #+#             */
/*   Updated: 2024/04/15 20:56:55 by uurbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time_ms() + (table->num_ph * 2 * 10);
	i = 0;
	while (i < table->num_ph)
	{
		if (pthread_create(&table->philos[i]->philo_thread, NULL, \
				&philosopher, table->philos[i]) != 0)
			return (free_table(table), FALSE);
		i++;
	}
	if (table->num_ph > 1)
	{
		if (pthread_create(&table->burrial, NULL, &burrial, table) != 0)
			return (free_table(table), FALSE);
	}
	return (TRUE);
}

void	stop_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_ph)
	{
		phtread_join(table->philos[i]->philo_thread, NULL);
		i++;
	}
	if (table->num_ph > 1)
		phtread_join(table->burrial, NULL);
	// comprobar lo de DEBUG FORMATTING en ppio no hace falta
	destroy_mutexes(table);
	free_table(table);
}

int	main(int ac, char **av)
{
	t_table	*table;
	
	if (ac -1 < 4 || ac - 1 > 5)
//		return (msg(USAGE, NULL, EXIT_FAILURE));
		return (printf("usage: ./philo <num_of_philos> <time_to_die> \
		<time_to_eat> <time_to_sleep> [num_max_of_meals]\n"), EXIT_FAILURE);
	if (!ft_check_valid_input(ac, av))
		return (EXIT_FAILURE);
	table = init_table(ac, av, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	stop_simulatiom(table);
	return (/* printf("OK"), */ EXIT_SUCCESS);
}
