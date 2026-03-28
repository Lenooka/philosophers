/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:28:01 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/11 20:15:31 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	to_die_force(t_philo *philo)
{
	pthread_mutex_lock(&philo->death);
	philo->end = 1;
	pthread_mutex_unlock(&philo->death);
}

int	monmeals(t_philo *philo, t_table *table)
{
	int		i;
	int		all_done;

	all_done = 1;
	i = 0;
	while (i < philo->num_of_philo)
	{
		if (done_eat_check(&table[i]) == 0)
		{
			all_done = 0;
			break ;
		}
		i++;
	}
	if (all_done)
	{
		to_die_force(philo);
		return (1);
	}
	return (0);
}

void	*mm(void *ph)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)ph;
	table = philo->table;
	if (philo->num_of_meals == -1)
		return (NULL);
	while (not_dead(philo) == 0)
	{
		if (monmeals(philo, table) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	*mondeath(t_philo *philo, t_table *table, int i)
{
	pthread_mutex_lock(&philo->death);
	if (philo->end == 0)
	{
		philo->end = 1;
		pthread_mutex_unlock(&philo->death);
		mess_out(&table[i], "died", 5);
	}
	else
		pthread_mutex_unlock(&philo->death);
	return (NULL);
}

void	*md(void *ph)
{
	t_philo	*philo;
	t_table	*table;
	int		i;

	philo = (t_philo *)ph;
	table = philo->table;
	while (1)
	{
		if (not_dead(philo) == 1)
			return (NULL);
		i = 0;
		while (i < philo->num_of_philo)
		{
			if (philo->num_of_meals != -1 && done_eat_check(&table[i]) == 1)
			{
				i++;
				continue ;
			}
			if (get_current_time(last_meal_time(&table[i]))
				> (u_int64_t)philo->time_to_die)
				return (mondeath(philo, table, i));
			i++;
		}
		usleep(1000);
	}
}
