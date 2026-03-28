/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:58:10 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/12 14:11:29 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	ft_puterror_endl(char *s, int fd)
{
	char	*red;
	char	*nrm;

	red = KRED;
	nrm = KNRM;
	if (!s)
		return ;
	write(fd, red, ft_strlen(red));
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
	write(fd, nrm, ft_strlen(nrm));
}

void	free_table(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_destroy(&philo->table[i].eat);
		pthread_mutex_destroy(&philo->fork[i]);
		pthread_mutex_destroy(&philo->table[i].meals_mx);
		i++;
	}
	free(philo->table);
}

void	full_exit(t_philo *philo, t_table *table, char *mess)
{
	if (table)
		free_table(table, philo);
	if (philo->ph)
		free(philo->ph);
	if (philo->fork)
	{
		free(philo->fork);
	}
	pthread_mutex_destroy(&philo->write);
	pthread_mutex_destroy(&philo->death);
	pthread_mutex_destroy(&philo->sim);
	ft_puterror_endl(mess, 2);
}

int	exit_free(t_philo *philo, t_table *table, char *mess)
{
	free(table);
	if (philo->ph)
		free(philo->ph);
	if (philo->fork)
		free(philo->fork);
	ft_puterror_endl(mess, 2);
	return (1);
}

int	exit_just_mess(char *str)
{
	ft_puterror_endl(str, 2);
	return (1);
}
