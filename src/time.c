/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uurbizu- <uurbizu-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:12:22 by uurbizu-          #+#    #+#             */
/*   Updated: 2024/04/22 19:31:39 by uurbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* checks to see if the simulation has ended during the sleep*/
void	philo_sleep(t_table *table, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_ms() + sleep_time;
	while (get_time_ms() < wake_up)
	{
		if (has_sim_stopped(table))
			break ;
		usleep(100);
	}
}

/* waits for a delay at the beginning of each threads execution so that 
all threads start at the same time with the same start time reference. 
This ensures the burrial thread is synchronized with the philosopher threads.*/
void	sim_start_delay(time_t start_time)
{
	while (get_time_ms() < start_time)
		continue ;
}
