/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uurbizu- <uurbizu-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:18:26 by uurbizu-          #+#    #+#             */
/*   Updated: 2024/04/22 19:31:04 by uurbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * table->num_ph);
	if (!forks)
		return (free(table), \
				printf("Error: Could not allocate memory.\n"), NULL);
	i = 0;
	while (i < table->num_ph)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (free(table), \
				printf("Error: Could not create mutex.\n"), NULL);
		i++;
	}
	return (forks);
}

/* even philos are left handed */
void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->num_ph;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->num_ph;
		philo->fork[1] = philo->id;
	}
}

t_philo	**init_philosophers(t_table *table)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo) * table->num_ph);
	if (!philos)
		return (free(table), \
				printf("Error: Could not allocate memory.\n"), NULL);
	i = 0;
	while (i < table->num_ph)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (free(table), \
				printf("Error: Could not allocate memory.\n"), NULL);
		if (pthread_mutex_init(&philos[i]->meal_time_lock, 0) != 0)
			return (free(table), \
				printf("Error: Could not create mutex.\n"), NULL);
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

bool	init_global_mutexes(t_table *table)
{
	table->fork_locks = init_forks(table);
	if (!table->fork_locks)
		return (false);
	if (pthread_mutex_init(&table->sim_stop_lock, 0) != 0)
		return (free(table), \
				printf("Error: Could not create mutex.\n"), FALSE);
	if (pthread_mutex_init(&table->write_lock, 0) != 0)
		return (free(table), \
				printf("Error: Could not create mutex.\n"), FALSE);
	return (true);
}

t_table	*init_table(int ac, char **av, int i)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (free(table), \
				printf("Error: Could not allocate memory.\n"), NULL);
	table->num_ph = ft_atoi(av[i++]);
	table->time_to_die = ft_atoi(av[i++]);
	table->time_to_eat = ft_atoi(av[i++]);
	table->time_to_sleep = ft_atoi(av[i++]);
	table->must_eat_count = -1;
	if (ac - 1 == 5)
		table->must_eat_count = ft_atoi(av[i]);
	table->philos = init_philosophers(table);
	if (!table->philos)
		return (NULL);
	if (!init_global_mutexes(table))
		return (NULL);
	table->sim_stop = false;
	return (table);
}
