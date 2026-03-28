/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:32:18 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/12 14:00:09 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	*one_philo_handler(t_table *table)
{
	pthread_mutex_lock(table->leftf);
	mess_out(table, "has taken a fork", 1);
	pthread_mutex_unlock(table->leftf);
	pthread_mutex_lock(&table->philo->death);
	table->philo->end = 1;
	pthread_mutex_unlock(&table->philo->death);
	mess_out(table, "died", 5);
	return (NULL);
}

void	ft_sleep(t_table *inst)
{
	mess_out(inst, "is sleeping", 3);
	pass_time(inst->philo->time_to_sleep);
	if (not_dead(inst->philo) == 1)
		return ;
}

void	*ft_feast(void *ph)
{
	t_table	*inst;

	inst = (t_table *)ph;
	if (wait_for_creation(inst->philo) == 2)
		return (NULL);
	if (inst->num_ph == 1)
		return (one_philo_handler(inst));
	if (inst->indx % 2 == 0)
		usleep(50);
	if (inst->philo->num_of_meals == -1)
	{
		while (not_dead(inst->philo) == 0)
		{
			if (eat_action(inst) == -1)
				break ;
			if (not_dead(inst->philo) == 1)
				break ;
			ft_sleep(inst);
			ft_think(inst);
		}
	}
	else
		limited_meals(inst);
	return (NULL);
}
