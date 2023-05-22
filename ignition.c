/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danierod <danierod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:26:20 by danierod          #+#    #+#             */
/*   Updated: 2023/05/10 12:01:32 by danierod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	launcher(t_args *args)
{
	int	i;
	t_philo *philo;

	i = 0;
	philo = args->philo;
	args->time = time_me();
	while (i < args->nb_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL, routine, &(philo[i])))
			return (1);
		philo[i].last_meal = time_me();
		i++;
	}
	schrodinger(args, args->philo, -1);
	turn_off(args, philo);
	return (0);
}

int	mutex_init(t_args *args)
{
	int i;

	i = args->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(args->forks[i]), NULL))
			return (write(2, "Failed to init mutex.\n", 22));
	}
	if (pthread_mutex_init(&(args->text), NULL))
		return (write(2, "Failed to init mutex.\n", 22));
	if (pthread_mutex_init(&(args->meals), NULL))
		return (write(2, "Failed to init mutex.\n", 22));
	return (0);
}

int	philo_gen(t_args *args)
{
	int i;
	
	i = args->nb_philo;
	while (--i >= 0)
	{
		args->philo[i].id = i;
		args->philo[i].l_fork = i;
		args->philo[i].r_fork = (i + 1) % args->nb_philo;
		args->philo[i].args = args;
		args->philo[i].last_meal = 0;
		args->philo[i].args = args;
	}
	return (0);
}

int	ignition(t_args *args, char **av)
{
	args->nb_philo = ft_atoi(av[1]);
	args->t_death = ft_atoi(av[2]);
	args->t_eat = ft_atoi(av[3]);
	args->t_sleep = ft_atoi(av[4]);
	args->all_ate = 0;
	args->dead = 0;
	if (args->nb_philo < 1 || args->nb_philo > 250 || args->t_death < 0 || args->t_eat < 0
		|| args->t_sleep < 0)
		return (write(2, "At least one wrong argument.\n", 30));
	if (av[5])
	{
		args->nb_eat = ft_atoi(av[5]);
		if (args->nb_eat <= 0)
			return (write(2, "Wrong 5th argument.\n", 20));
	}
	else
		(args->nb_eat) = -1;
	if (mutex_init(args))
		return (write(2, "Failed to init mutex.\n", 22));
	philo_gen(args);
	return (0);
}