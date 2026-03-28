/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:29:10 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/12 14:22:00 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	check_meals(char **argv)
{
	if (ft_atoi(argv[5]) < 0)
	{
		printf("%s", KRED);
		printf("Philosophers can't eat absence of meals!\n");
		printf("%s", KNRM);
		printf("Ammount of meals : %s\n", argv[5]);
		return (1);
	}
	return (0);
}

int	checkfill_arguments(t_philo *phil, char **argv, int argc)
{
	int	i;
	int	j;

	j = 1;
	(void)phil;
	if (argc == 6)
		check_meals(argv);
	while (argv[j])
	{
		i = 0;
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
			{
				printf("%sInvalid argument : %s\n", KRED, argv[j]);
				printf("%s", KNRM);
				return (1);
			}
			i++;
		}
		j++;
	}
	if (!check_atoi(argv))
		return (1);
	return (0);
}
