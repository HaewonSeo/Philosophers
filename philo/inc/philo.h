/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 22:38:21 by haseo             #+#    #+#             */
/*   Updated: 2021/11/16 00:02:31 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

# define BLK "\033[0;30m"
# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define YEL "\033[0;33m"
# define BLU "\033[0;34m"
# define MAG "\033[0;35m"
# define CYN "\033[0;36m"
# define WHT "\033[0;37m"
# define EOC "\033[0m"

# define MAXINT 2147483647
# define MININT -2147483648

typedef enum e_state
{
	TAKEN,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	COMPLETE
}			t_state;

typedef struct s_info
{
	int					nr_philos;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					nr_must_eat;
	int					nr_end_dine;
	long int			time_start;
}						t_info;

typedef struct s_mutex
{
	pthread_mutex_t		simulation;
	pthread_mutex_t		*fork;
}						t_mutex;

typedef struct s_philo
{
	pthread_t			tid_dine;
	pthread_t			tid_monitor;
	int					id;
	int					l;
	int					r;
	int					nr_dininig;
	long int			time;
	long int			time_last_dine;
	t_info				*info;
	t_mutex				*mutex;
}						t_philo;

/*
** Simulation
*/

int						simulation(t_philo *ph);
int						pickup(t_philo *ph);
int						eating(t_philo *ph);
int						putdown(t_philo *ph);
int						sleeping(t_philo *ph);
int						thinking(t_philo *ph);

/*
** Utility
*/

int						ft_atoi(char *s);
void					*ft_calloc(size_t num, size_t size);
int						ft_perror(const char *str, int errno);
int						print_state(t_philo *ph, t_state state);
int						get_msec(long int *msec);
int						thread_msleep(long int msec, long int time_start);

#endif
