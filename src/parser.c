/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uurbizu- <uurbizu-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:16:23 by uurbizu-          #+#    #+#             */
/*   Updated: 2024/03/31 21:05:03 by uurbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *s1)
{
	long	num;
	short	sgn;

	num = 0;
	sgn = 1;
	while (*s1 == ' ' || *s1 == '\n' || *s1 == '\f' || *s1 == '\t'
		|| *s1 == '\v' || *s1 == '\r')
		s1++;
	if (*s1 == '-' || *s1 == '+')
	{
		if (*s1 == '-')
			sgn = -1;
		s1++;
	}
	while (ft_isdigit((int) *s1))
		num = (num * 10) + (*s1++ - '0');
	return (num * sgn);
}

bool	ft_check_is_int(char *str)
{
	int		i;

	if (!str)
		return (FALSE);
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (FALSE);
		i++;
	}
	if (ft_atoi(str) < 0 || ft_atoi(str) > INT_MAX)
		return (FALSE);
	else
		return (TRUE);
}

int	ft_check_valid_input(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_check_is_int(av[i]))
			return (FALSE);
		if (i == 1 && ft_atoi(av[i]) > MAX_PHILOS)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
