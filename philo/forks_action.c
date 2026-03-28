/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:26:50 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/11 18:56:19 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	untake_forks(t_table *inst)
{
	if (inst->indx % 2)
	{
		pthread_mutex_unlock(inst->leftf);
		pthread_mutex_unlock(inst->rightf);
	}
	else
	{
		pthread_mutex_unlock(inst->rightf);
		pthread_mutex_unlock(inst->leftf);
	}
}

void	uneven_handle(t_table *inst)
{
	pthread_mutex_lock(inst->rightf);
	if (not_dead(inst->philo) == 1)
	{
		pthread_mutex_unlock(inst->rightf);
		return ;
	}
	mess_out(inst, "has taken a fork", 1);
	pthread_mutex_lock(inst->leftf);
	if (not_dead(inst->philo) == 1)
	{
		untake_forks(inst);
		return ;
	}
	mess_out(inst, "has taken a fork", 1);
}

void	take_forks(t_table *inst)
{
	if (inst->indx % 2)
	{
		pthread_mutex_lock(inst->leftf);
		if (not_dead(inst->philo) == 1)
		{
			pthread_mutex_unlock(inst->leftf);
			return ;
		}
		mess_out(inst, "has taken a fork", 1);
		pthread_mutex_lock(inst->rightf);
		if (not_dead(inst->philo) == 1)
		{
			untake_forks(inst);
			return ;
		}
		mess_out(inst, "has taken a fork", 1);
	}
	else
	{
		uneven_handle(inst);
	}
}

void	forks_action(t_table *inst, int take)
{
	if (take == 0)
		take_forks(inst);
	else
		untake_forks(inst);
}
