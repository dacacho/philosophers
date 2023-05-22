/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danierod <danierod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:26:20 by danierod          #+#    #+#             */
/*   Updated: 2023/05/10 11:53:58 by danierod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <string.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>


# define NC "\e[0m"
# define RD "\e[31m"
# define GR "\e[32m"
# define BL "\e[34m"
# define YL "\e[33m"
# define MT "\e[35m"

struct s_args;

typedef struct  s_philo
{
    int				id;
    int             x_ate;
    int             r_fork;
	int             l_fork;
    long long       last_meal;
    pthread_t		thread;
	struct s_args	*args;
}	t_philo;

typedef struct  s_args
{
    int 					nb_philo;
    int 					t_death;
    int		 				t_eat;
    int 					t_sleep;
    int 					nb_eat;
    int                     all_ate;
    int                     dead;
    long long               time;
	pthread_mutex_t			text;
	pthread_mutex_t			meals;
	pthread_mutex_t			forks[250];
	t_philo					philo[250];
}   t_args;


int	ignition(t_args *args, char **av);
int	launcher(t_args *args);

long long	time_me(void);
int	ft_atoi(char *s);
void	print_me(t_args *args, int id, char *s, char *color);
void	snooze(long long time, t_args *args);

void	schrodinger(t_args *args, t_philo *philo, int i);
void	*routine(void *v_philo);
void	turn_off(t_args *args, t_philo *philo);

#endif