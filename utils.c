/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danierod <danierod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:26:20 by danierod          #+#    #+#             */
/*   Updated: 2023/05/10 11:13:44 by danierod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *s)
{
	int nb;
		
	nb = 0;
	if (*s == '-')
		return (-1);
	else if (*s == '+')
		s++;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			nb = nb * 10 + (*s++ - 48);
		else
			return (-1);
	}
	return (nb);
}

long long	time_me(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	print_me(t_args *args, int id, char *s, char *color)
{
	pthread_mutex_lock(&(args->text));
	if (!(args->dead))
	{
		printf("__________________________________________________\n\n");
		printf("[%lli ms] ", time_me() - args->time);
		printf("[philosopher nº %i]: ", id + 1);
		printf("%s%s.%s\n", color, s, NC);
	}
	pthread_mutex_unlock(&(args->text));
}

void	snooze(long long time, t_args *args)
{
	long long i;
	
	i = time_me();
	while (!(args->dead))
	{
		if ((time_me() - i) >= time)
			break ;
		usleep(50);
	}
}