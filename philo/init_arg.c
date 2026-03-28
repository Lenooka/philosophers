/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:34:58 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/12 14:18:45 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

u_int64_t	get_current_time(u_int64_t relative)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * (u_int64_t)1000) + (now.tv_usec / 1000) - relative);
}

int	error_arguments(char *s, char *mess)
{
	printf("Invalid argument [%s]!\n", s);
	printf("%s%s!\n", KRED, mess);
	printf("%s", KNRM);
	return (1);
}

int	fill_struct(t_philo *data, char **s)
{
	data->num_of_philo = ft_atoi(s[1]);
	if (data->num_of_philo < 1)
		return (error_arguments(s[1], "There is no life without philosophers"));
	data->time_to_die = ft_atoi(s[2]);
	if (data->time_to_die < 0)
		return (error_arguments(s[2],
				"We all eventually die, even philosophers\n"));
	data->time_to_eat = ft_atoi(s[3]);
	if (data->time_to_eat < 0)
		return (error_arguments(s[3], "Philosophers need time to eat too"));
	data->time_to_sleep = ft_atoi(s[4]);
	if (data->time_to_sleep < 0)
		return (error_arguments(s[4], "Philosophers need to sleep too\n"));
	if (s[5])
		data->num_of_meals = ft_atoi(s[5]);
	else
		data->num_of_meals = -1;
	if (data->num_of_meals == 0)
		return (error_arguments(s[5],
				"Philosophers need to eat at least once"));
	return (0);
}
