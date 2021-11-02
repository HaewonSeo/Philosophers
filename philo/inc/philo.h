/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 22:38:21 by haseo             #+#    #+#             */
/*   Updated: 2021/11/03 01:39:20 by haseo            ###   ########.fr       */
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

# define MAXINT			2147483647
# define MININT			-2147483648

# define LEFT(i, N)		((i + N - 1) % N)
# define RIGHT(i, N)	((i + 1) % N)

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING
}			t_state;
/*
typedef struct s_philo
{
	pthread_t			tid;
	t_state				state;
	pthread_mutex_t		mutex;
	int					left;
	int					right;
}						t_philo;

typedef struct s_info
{
	int					num_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_must_eat;
	int					time_start;
	pthread_mutex_t		mutex_test;
	int					cur;
	t_philo				*philo;
}						t_info;
*/

typedef struct s_info
{
	int					num_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_must_eat;
	int					time_start;
}						t_info;

typedef struct s_philo
{
	pthread_t			tid;
	int					id;
	int					left;
	int					right;
	t_info				*info;
	pthread_mutex_t		*check;
	pthread_mutex_t		*philo;
	pthread_mutex_t		*monitor;
	t_state				*state;
}						t_philo;

void					*ft_calloc(size_t num, size_t size);
int						arg_to_int(char *arg);
int						ft_perror(const char *str, int errno);
int						get_msec(int *msec);
int						thread_msleep(int msec, int time_start);

void					check(int i, t_philo *ph);
int						pickup(t_philo *ph);
int						eating(t_philo *ph);
int						putdown(t_philo *ph);
int						sleeping(t_philo *ph);
int						thinking(t_philo *ph);

#endif
