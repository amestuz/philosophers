/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uurbizu- <uurbizu-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:52:20 by uurbizu-          #+#    #+#             */
/*   Updated: 2024/04/06 19:58:45 by uurbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int msg(char *msg, char *detail, int exit)
{
	if(! detail)
		printf(msg, PROG_NAME);
	else
		printf(msg, PROG_NAME, detail);
	return(exit);
}

