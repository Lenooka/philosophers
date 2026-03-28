/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oltolmac <oltolmac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:21:20 by oltolmac          #+#    #+#             */
/*   Updated: 2025/07/12 14:24:38 by oltolmac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stddef.h>
# include <unistd.h>
# include "limits.h"
# include <sys/time.h>
# include <sys/types.h>
# include <stdlib.h>
# define MAX_INT 2147483647
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

typedef struct s_table
{
	int					indx;
	int					num_ph;
	struct s_philo		*philo;
	pthread_mutex_t		*rightf;
	pthread_mutex_t		*leftf;
	pthread_mutex_t		eat;
	pthread_mutex_t		meals_mx;
	pthread_mutex_t		done;
	int					all_eaten;
	u_int64_t			last_eat;
	u_int64_t			start_time;
	int					done_eating;
}	t_table;
typedef struct s_philo
{
	int					time_to_die;
	int					num_of_philo;
	int					time_to_sleep;
	int					time_to_eat;
	int					num_of_meals;
	int					end;
	int					start;
	pthread_mutex_t		write;
	pthread_mutex_t		death;
	pthread_mutex_t		sim;
	pthread_t			*ph;
	pthread_t			mon_death;
	pthread_t			mon_meals;
	pthread_mutex_t		*fork;
	u_int64_t			start_t;
	t_table				*table;
}	t_philo;

int			check_atoi(char **argv);
int			exit_free(t_philo *philo, t_table *table, char *mess);
int			fill_struct(t_philo *data, char **s);
int			set_up_table(t_philo *philo, int i);
int			exit_just_mess(char *str);
u_int64_t	get_current_time(u_int64_t relative);
int			check_meals(char **argv);
int			checkfill_arguments(t_philo *phil, char **argv, int argc);
void		full_exit(t_philo *philo, t_table *table, char *mess);
int			init_mutex_forks(t_philo *philo);
void		destroy_back(t_philo *philo, int i);
void		free_table(t_table *table, t_philo *philo);
int			done_eat_check(t_table *inst);
int			set_mutex_cut(t_philo *philo);
int			exit_one(t_philo *philo, t_table *table, char *s);
int			set_mutex(t_philo *philo, t_table *table);

//monitor
void		*mm(void *ph);
void		*md(void *ph);

//feast
int			start_feast(t_philo *philo, t_table *table);
void		*one_philo_handler(t_table *table);
void		*ft_feast(void *ph);

//action
int			ft_think(t_table *inst);
void		pass_time(u_int64_t time);
int			food_count(t_table *inst);
u_int64_t	last_meal_time(t_table *philo);
void		meal_counter(t_table *inst);
void		limited_meals(t_table *inst);
int			eat_action(t_table *inst);
void		forks_action(t_table *inst, int take);
//UTILS
int			ft_strlen(char *s);
int			ft_atoi(const char *str);
void		ft_puterror_endl(char *s, int fd);
void		pass_time(u_int64_t time);
int			wait_for_creation(t_philo *philo);
int			not_dead(t_philo *philo);
//print
void		mess_out(t_table *inst, char *mess, int c);

#endif