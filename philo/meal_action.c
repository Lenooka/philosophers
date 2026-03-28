/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:40:59 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/11 20:05:38 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	food_count(t_table *inst)
{
	int	count;

	pthread_mutex_lock(&inst->meals_mx);
	count = inst->all_eaten;
	pthread_mutex_unlock(&inst->meals_mx);
	return (count);
}

u_int64_t	last_meal_time(t_table *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->eat);
	time = philo->last_eat;
	pthread_mutex_unlock(&philo->eat);
	return (time);
}

void	meal_counter(t_table *inst)
{
	pthread_mutex_lock(&inst->meals_mx);
	inst->all_eaten++;
	pthread_mutex_unlock(&inst->meals_mx);
}

int	eat_action(t_table *inst)
{
	if (not_dead(inst->philo) == 1)
		return (-1);
	forks_action(inst, 0);
	if (not_dead(inst->philo) == 1)
		return (-1);
	pthread_mutex_lock(&inst->eat);
	if (not_dead(inst->philo) == 1)
		return (-1);
	inst->last_eat = get_current_time(0);
	pthread_mutex_unlock(&inst->eat);
	if (not_dead(inst->philo) == 1)
	{
		forks_action(inst, 0);
		return (-1);
	}
	mess_out(inst, "is eating", 2);
	pass_time(inst->philo->time_to_eat);
	forks_action(inst, 1);
	return (0);
}

void	limited_meals(t_table *inst)
{
	while (food_count(inst) < inst->philo->num_of_meals
		&& not_dead(inst->philo) == 0)
	{
		if (eat_action(inst) == -1)
			break ;
		meal_counter(inst);
		if (food_count(inst) >= inst->philo->num_of_meals)
		{
			pthread_mutex_lock(&inst->done);
			inst->done_eating = 1;
			pthread_mutex_unlock(&inst->done);
			return ;
		}
		if (not_dead(inst->philo) == 1)
			break ;
		mess_out(inst, "is sleeping", 3);
		pass_time(inst->philo->time_to_sleep);
		if (not_dead(inst->philo) == 1)
			break ;
		ft_think(inst);
	}
}
