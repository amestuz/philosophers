/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uurbizu- <uurbizu-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:01:00 by uurbizu-          #+#    #+#             */
/*   Updated: 2024/04/18 18:17:05 by uurbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, false, GOT_FORK_1);
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	write_status(philo, false, GOT_FORK_2);
	write_status(philo, false, EATING);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_sleep(philo->table, philo->table->time_to_eat);
	if (has_sim_stopped(philo->table) == false)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	write_status(philo, false, SLEEPING);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	philo_sleep(philo->table, philo->table->time_to_sleep);
}

void	think_routine(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->table->time_to_die - (get_time_ms() \
			- philo->last_meal) - philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		write_status(philo, false, THINKING);
	philo_sleep(philo->table, time_to_think);
}

void	*lone_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, false, GOT_FORK_1);
	philo_sleep(philo->table, philo->table->time_to_die);
	write_status(philo, false, DIED);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	sim_start_delay(philo->table->start_time);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->num_ph == 1)
		return (lone_philo(philo));
	else if (philo->id % 2)
		think_routine(philo, TRUE);
	while (has_sim_stopped(philo->table) == FALSE)
	{
		eat_sleep_routine(philo);
		think_routine(philo, FALSE);
	}
	return (NULL);
}