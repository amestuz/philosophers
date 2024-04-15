/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uurbizu- <uurbizu-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:37:15 by uurbizu-          #+#    #+#             */
/*   Updated: 2024/04/15 21:09:41 by uurbizu-         ###   ########.fr       */
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

// For error printing;

//# define PROG_NAME 			"Philo :"
//# define MAX_PHILO_STRING 	"250"
//# define USAGE				"%s usage: ./philo <num_of_philos> <time_to_die> \
							<time_to_eat> <time_to_sleep> [num_max_of_meals]\n"
//# define ERR_INPUT_DIGIT	"%s invalid input: %s is not a valid unsigned \
							int.\n"
//# define ERR_INPUT_PH_NUM	"%s invalid input: there must be between 1 and %s \
							Philos.\n"
//# define ERR_THREAD			"%s error: could not create thread.\n"
//# define ERR_MALLOC			"%s error: could not allocate memory.\n"
//# define ERR_MUTEX			"%s error: could not create mutex.\n"

/******************************************************************************
*                                 Structures                                  *
******************************************************************************/

typedef struct s_table
{
	time_t			start_time;
	unsigned int	num_ph;
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

//		main.c
int		main(int ac, char **av);

//		parser.c
int		ft_check_valid_input(int ac, char **av);
bool	ft_check_is_int(char *str);
int		ft_atoi(const char *s1);
int		ft_isdigit(int c);

#endif