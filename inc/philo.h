/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uurbizu- <uurbizu-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:37:15 by uurbizu-          #+#    #+#             */
/*   Updated: 2024/03/31 21:03:42 by uurbizu-         ###   ########.fr       */
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

enum e_bool
{
	FALSE = 0,
	TRUE = 1,
	CONT = 2
} ;

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