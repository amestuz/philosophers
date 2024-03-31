/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uurbizu- <uurbizu-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:08:54 by uurbizu-          #+#    #+#             */
/*   Updated: 2024/03/31 21:06:44 by uurbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	if (ac -1 < 4 || ac - 1 > 5)
		return (printf("Error"), FALSE);
	if (!ft_check_valid_input(ac, av))
		return (printf("Error"), FALSE);
	return (printf("OK"), TRUE);
}
