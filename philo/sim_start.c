/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:31:41 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/12 14:35:21 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	join_threads(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	pthread_join(philo->mon_death, NULL);
	pthread_join(philo->mon_meals, NULL);
	while (i < philo->num_of_philo)
	{
		if (pthread_join(philo->ph[i], NULL) != 0)
		{
			exit_free(philo, table, "Error in pthread_join");
			return (1);
		}
		i++;
	}
	return (0);
}

void	time_and_wait_init(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	philo->start_t = get_current_time(0);
	philo->start = 0;
	while (i < philo->num_of_philo)
	{
		table[i].start_time = philo->start_t;
		table[i].last_eat = philo->start_t;
		i++;
	}
	pthread_mutex_lock(&philo->sim);
}

void	handle_threads_fail(t_philo *philo, t_table *table, int i)
{
	philo->start = 2;
	pthread_mutex_unlock(&philo->sim);
	while (i < philo->num_of_philo)
	{
		pthread_join(philo->ph[i], NULL);
		i++;
	}
	full_exit(philo, table, "Error in pthread_create");
}

int	start_feast(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	time_and_wait_init(philo, table);
	while (i < philo->num_of_philo)
	{
		if (pthread_create(&philo->ph[i], NULL, &ft_feast, &table[i]) != 0)
		{
			handle_threads_fail(philo, table, i);
			return (1);
		}
		i++;
	}
	philo->start = 1;
	pthread_mutex_unlock(&philo->sim);
	if (pthread_create(&philo->mon_death, NULL, &md, (void *)philo) != 0
		|| pthread_create(&philo->mon_meals, NULL, &mm, (void *)philo) != 0)
	{
		full_exit(philo, table, "Error in pthread_create for monitor_death");
		return (1);
	}
	if (join_threads(philo, table) == 1)
		return (1);
	return (0);
}
