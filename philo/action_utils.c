/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:31:10 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/12 13:55:25 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	ft_think(t_table *inst)
{
	u_int64_t	buffer;
	u_int64_t	think_time;

	buffer = 5;
	if (not_dead(inst->philo) == 1)
		return (0);
	think_time = inst->philo->time_to_die
		- (get_current_time(0) - last_meal_time(inst))
		- inst->philo->time_to_eat
		- buffer;
	if ((int)think_time > 0)
		pass_time(think_time);
	if (not_dead(inst->philo) == 1)
		return (0);
	mess_out(inst, "is thinking", 4);
	return (0);
}

void	pass_time(u_int64_t time)
{
	u_int64_t	start_time;

	start_time = get_current_time(0);
	while (get_current_time(start_time) < time)
		usleep(1000);
}

char	*choose_color(int i)
{
	if (i == 1)
		return (KRED);
	if (i == 2)
		return (KYEL);
	if (i == 3)
		return (KGRN);
	if (i == 4)
		return (KCYN);
	if (i == 5)
		return (KMAG);
	return (KCYN);
}

void	mess_out(t_table *inst, char *mess, int c)
{
	u_int64_t	time;

	time = get_current_time(inst->philo->start_t);
	pthread_mutex_lock(&inst->philo->write);
	if (c == 1)
		printf("%s%lu %d %s\n", KRED, time, inst->indx, mess);
	else if (c == 2)
		printf("%s%lu %d %s\n", KYEL, time, inst->indx, mess);
	else if (c == 3)
		printf("%s%lu %d %s\n", KGRN, time, inst->indx, mess);
	else if (c == 4)
		printf("%s%lu %d %s\n", KCYN, time, inst->indx, mess);
	else if (c == 5)
		printf("%s%lu %d %s\n", KMAG, time, inst->indx, mess);
	else
		printf("%s%lu %d %s\n", KRED, time, inst->indx, mess);
	printf("%s", KNRM);
	pthread_mutex_unlock(&inst->philo->write);
}
