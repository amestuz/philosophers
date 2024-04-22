/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uurbizu- <uurbizu-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:37:15 by uurbizu-          #+#    #+#             */
/*   Updated: 2024/04/22 18:30:56 by uurbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

/******************************************************************************
*                                     Macros                                  *
******************************************************************************/

# define MAX_PHILOS	250

/******************************************************************************
*                                 Structures                                  *
******************************************************************************/

typedef struct s_philo	t_philo;

typedef struct s_table
{
	time_t			start_time;
	int				num_ph;
	pthread_t		burrial;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			**philos;
}	t_table;

typedef struct s_philo
{
	pthread_t			philo_thread;
	unsigned int		id;
	unsigned int		times_ate;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_table				*table;
}	t_philo;

enum e_bool
{
	FALSE = 0,
	TRUE = 1,
	CONT = 2
};

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

/******************************************************************************
*                           Function Prototypes                               *
******************************************************************************/

//	main.c
int				main(int ac, char **av);
int				start_simulation(t_table *table);
void			stop_simulation(t_table *table);

//	parser.c
int				ft_check_valid_input(int ac, char **av);
bool			ft_check_is_int(char *str);
int				ft_atoi(const char *s1);
int				ft_isdigit(int c);

//	init.c
t_table			*init_table(int ac, char **av, int i);
bool			init_global_mutexes(t_table *table);
t_philo			**init_philosophers(t_table *table);
void			assign_forks(t_philo *philo);
pthread_mutex_t	*init_forks(t_table *table);

//	philo.c
void			*philosopher(void *data);
void			*lone_philo(t_philo *philo);
void			think_routine(t_philo *philo, bool silent);
void			eat_sleep_routine(t_philo *philo);

//	burrial.c
void			*burrial(void *data);
bool			end_condition_reached(t_table *table);
bool			kill_philo(t_philo *philo);
bool			has_sim_stopped(t_table *table);
void			set_sim_stop_flag(t_table *table, bool state);

//	time.c
time_t			get_time_ms(void);
void			sim_start_delay(time_t start_time);
void			philo_sleep(t_table *table, time_t sleep_time);

//	output.c
void			*free_table(t_table *table);
void			destroy_mutexes(t_table *table);
void			print_status(t_philo *philo, char *str);
void			write_status(t_philo *philo, bool reaper_report, \
													t_status status);
//void			write_outcome(t_table *table);
#endif