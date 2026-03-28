/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:07:12 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/12 14:36:58 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// 1 philo.num_of_philo);
	// 2 philo.time_to_die);
	// 3 philo.time_to_eat);
	// 4 philo.time_to_sleep);
	// 5 philo.num_of_meals);	
int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc != 5 && argc != 6)
	{
		exit_just_mess("Wrong amount of arguments!");
		return (0);
	}
	if (checkfill_arguments(&philo, argv, argc) == 1)
		return (0);
	if (fill_struct(&philo, argv) == 1)
		return (0);
	if (set_up_table(&philo, 0) == 1)
		return (0);
	if (start_feast(&philo, philo.table) == 1)
		return (0);
	full_exit(&philo, philo.table, NULL);
	return (0);
}
