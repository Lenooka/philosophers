/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:32:51 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/11 18:47:30 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	long			mc;
	long			g;

	i = 0;
	g = 0;
	mc = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			mc *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		g = g * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(g * mc));
}

size_t	st_atoi(const char *str)
{
	unsigned int	i;
	long			mc;
	long			g;

	i = 0;
	g = 0;
	mc = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			mc *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		g = g * 10 + (str[i] - '0');
		i++;
	}
	return ((size_t)(g * mc));
}

long	ft_strtol(const char *str, char **endptr)
{
	long	result;

	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
		{
			if (endptr != NULL)
			{
				*endptr = (char *)str;
			}
			return (LONG_MAX);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	if (endptr != NULL)
	{
		*endptr = (char *)str;
	}
	return (result);
}

size_t	fft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	check_atoi(char **argv)
{
	int			i;
	char		*endptr;
	long long	value;

	i = 1;
	while (argv[i])
	{
		value = ft_strtol(argv[i], &endptr);
		if (ft_atoi(argv[1]) > 1000000)
		{
			return (printf("To many philosophers for my program!"), 0);
		}
		if (*endptr != '\0')
		{
			printf("%sError converting argument to int: %s\n", KRED, argv[i]);
			return (0);
		}
		if (value > INT_MAX || value < INT_MIN)
		{
			printf("%sInteger overflow in argument: %s\n", KRED, argv[i]);
			return (0);
		}
		i++;
	}
	return (1);
}
