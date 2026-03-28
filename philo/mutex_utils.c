/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:29:59 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/12 14:24:46 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	set_mutex_cut(t_philo *philo)
{
	philo->table = malloc(sizeof(t_table) * philo->num_of_philo);
	if (!philo->table)
		return (exit_just_mess("Malloc table fail, set_up_table"));
	philo->ph = malloc(sizeof(pthread_t) * philo->num_of_philo);
	if (!philo->ph)
		return (exit_one(philo, philo->table, "Malloc ph_thread fail"));
	if (set_mutex(philo, philo->table) == 1)
		return (1);
	return (0);
}

int	done_eat_check(t_table *inst)
{
	int	a;

	pthread_mutex_lock(&inst->done);
	a = inst->done_eating;
	pthread_mutex_unlock(&inst->done);
	return (a);
}

int	init_mutex_forks(t_philo *philo)
{
	int	i;

	i = 0;
	philo->end = 0;
	while (i < philo->num_of_philo)
	{
		if (pthread_mutex_init(&philo->fork[i], NULL) != 0)
		{
			pthread_mutex_destroy(&philo->write);
			pthread_mutex_destroy(&philo->death);
			pthread_mutex_destroy(&philo->sim);
			destroy_back(philo, i);
			return (exit_free(philo, philo->table, "Mutex fork init fail"));
		}
		i++;
	}
	return (0);
}

int	not_dead(t_philo *philo)
{
	int	r;

	pthread_mutex_lock(&philo->death);
	r = philo->end;
	pthread_mutex_unlock(&philo->death);
	return (r);
}

int	wait_for_creation(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim);
	while (1)
	{
		if (philo->start == 1)
			break ;
		if (philo->start == 2)
			return (2);
	}
	pthread_mutex_unlock(&philo->sim);
	return (0);
}
