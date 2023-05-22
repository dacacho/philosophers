/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danierod <danierod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:26:20 by danierod          #+#    #+#             */
/*   Updated: 2023/05/10 11:13:56 by danierod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	turn_off(t_args *args, t_philo *philo)
{
	int i;
	
	i = -1;
	while (++i < args->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&(args->forks[i]));
	}
	pthread_mutex_destroy(&(args->text));
}

void	bon_apetit(t_philo *philo)
{
	t_args * args;
	
	args = philo->args;
	pthread_mutex_lock(&(args->forks[philo->l_fork]));
	print_me(args, philo->id, "has taken a fork", MT);
	pthread_mutex_lock(&(args->forks[philo->r_fork]));
	print_me(args, philo->id, "has taken a fork", MT);
	pthread_mutex_lock(&(args->meals));
	print_me(args, philo->id, "is eating", GR);
	philo->last_meal = time_me();
	pthread_mutex_unlock(&(args->meals));
	snooze(args->t_eat, args);
	(philo->x_ate)++;
	pthread_mutex_unlock(&(args->forks[philo->r_fork]));
	pthread_mutex_unlock(&(args->forks[philo->l_fork]));
}

void	*routine(void *v_philo)
{
	int	i;
	t_philo *philo;
	t_args	*args;

	i = 0;
	philo = (t_philo *)v_philo;
	args = philo->args;
	if (philo->id % 2)
		usleep(15000);
	while (!(args->dead))
	{
		bon_apetit(philo);
		if (args->all_ate)
			break ;
		print_me(args, philo->id, "is sleeping", BL);
		snooze(args->t_sleep, args);
		print_me(args, philo->id, "is thinking", YL);
		i++;
	}
	return (NULL);
}


void	schrodinger(t_args *args, t_philo *philo, int i)
{
	while (!(args->all_ate))
	{
		i = -1;
		while (++i < args->nb_philo && !(args->dead))
		{
			pthread_mutex_lock(&(args->meals));
			if ((time_me() - philo[i].last_meal) > args->t_death)
			{
				print_me(args, philo->id, "died", RD);
				args->dead = 1;
			}
			pthread_mutex_unlock(&(args->meals));
			usleep(100);
		}
		if (args->dead)
			break ;
		i = 0;
		while (args->nb_eat != -1 && i < args->nb_philo && philo[i].x_ate >= args->nb_eat)
			i++;
		if (i == args->nb_philo)
			args->all_ate = 1;
	}
}

int	main(int ac, char **av)
{
	t_args args;
	
	if (ac != 5 && ac != 6)
		return (write(2, "Wrong number of arguments.\n", 27));
	if (ignition(&args, av))
		return (write(2, "Failed to start program.\n", 26));
	if (launcher(&args))
		return (write(2, "Failed to create threads.\n", 25));
	return (0);
}