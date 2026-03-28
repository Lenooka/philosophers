/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:55:21 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/12 14:20:48 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	destroy_back(t_philo *philo, int i)
{
	int	a;

	a = 0;
	while (a != i)
	{
		pthread_mutex_destroy(&philo->fork[a]);
		a++;
	}
}

int	set_mutex(t_philo *philo, t_table *table)
{
	philo->fork = NULL;
	if (pthread_mutex_init(&philo->write, NULL) != 0)
		return (exit_free(philo, table, "Mutex write init fail"));
	if (pthread_mutex_init(&philo->sim, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->write);
		return (exit_free(philo, table, "Mutex write init fail"));
	}
	if (pthread_mutex_init(&philo->death, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->write);
		pthread_mutex_destroy(&philo->death);
		return (exit_free(philo, table, "Mutex death init fail"));
	}
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
	if (!philo->fork)
	{
		pthread_mutex_destroy(&philo->write);
		pthread_mutex_destroy(&philo->death);
		pthread_mutex_destroy(&philo->sim);
		return (exit_free(philo, table, "Mutex death init fail"));
	}
	if (init_mutex_forks(philo) == 1)
		return (1);
	return (0);
}

int	exit_one(t_philo *philo, t_table *table, char *s)
{
	free(table);
	(void)philo;
	exit_just_mess(s);
	return (1);
}

int	exit_loop(t_philo *philo, t_table *table, char *s, int i)
{
	pthread_mutex_destroy(&philo->write);
	pthread_mutex_destroy(&philo->death);
	pthread_mutex_destroy(&philo->sim);
	while (i >= 0)
	{
		pthread_mutex_destroy(&table[i].eat);
		pthread_mutex_destroy(&table[i].meals_mx);
		i--;
	}
	return (exit_free(philo, table, s));
}

int	set_up_table(t_philo *philo, int i)
{
	if (set_mutex_cut(philo) == 1)
		return (1);
	while (i < philo->num_of_philo)
	{
		philo->table[i].indx = i + 1;
		philo->table[i].philo = philo;
		philo->table[i].done_eating = 0;
		philo->table[i].all_eaten = 0;
		philo->table[i].num_ph = philo->num_of_philo;
		philo->table[i].leftf = &philo->fork[i];
		philo->table[i].rightf = &philo->fork[(i + 1) % philo->num_of_philo];
		if (pthread_mutex_init(&philo->table[i].eat, NULL) != 0)
			return (exit_loop(philo, philo->table, "Mutex eat init fail", i));
		if (pthread_mutex_init(&philo->table[i].meals_mx, NULL) != 0)
			return (exit_loop(philo, philo->table, "Mutex meals init fail", i));
		if (pthread_mutex_init(&philo->table[i].done, NULL) != 0)
			return (exit_loop(philo, philo->table, "Mutex done init fail", i));
		i++;
	}
	return (0);
}
