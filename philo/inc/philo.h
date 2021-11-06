/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 22:38:21 by haseo             #+#    #+#             */
/*   Updated: 2021/11/06 00:15:18 by haseo            ###   ########.fr       */
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
	SLEEPING,
}			t_state;

typedef enum e_fork
{
	USABLE,
	UNUSABLE
}			t_fork;

typedef struct s_info
{
	int					num_philo;	// 1인 경우는?
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_must_eat;
	int					num_end_dine;
	long int			time_start;
}						t_info;

typedef struct s_mutex
{
	pthread_mutex_t		check;
	pthread_mutex_t		simulation;
	pthread_mutex_t		*philo;
	pthread_mutex_t		*monitor;
}						t_mutex;

typedef struct s_philo
{
	pthread_t			tid_dine;
	pthread_t			tid_monitor;
	int					id;
	int					left;
	int					right;
	int					eat;
	long int			time_last_dine;
	t_info				*info;
	t_mutex				*mutex;
	t_fork				*fork;
}						t_philo;

void					*ft_calloc(size_t num, size_t size);
int						arg_to_int(char *arg);
int						ft_perror(const char *str, int errno);
int						get_msec(long int *msec);
int						thread_msleep(long int msec, long int time_start);

int						check(int i, t_philo *ph);
int						pickup(t_philo *ph);
int						eating(t_philo *ph);
int						putdown(t_philo *ph);
int						sleeping(t_philo *ph);
int						thinking(t_philo *ph);

#endif
