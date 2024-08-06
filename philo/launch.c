/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:34:35 by emy               #+#    #+#             */
/*   Updated: 2024/08/06 09:53:47 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(char *str, t_philo *ph)
{
	long int	time;

	time = -1;
	time = actual_time() - ph->arg->start_t;
	if (time >= 0 && time <= 2147483647 && !check_death(ph, 0))
	{
		printf("%ld ", time);
		printf("%d %s", ph->id, str);
	}
}

void	sleep_or_think(t_philo *ph)
{
	pthread_mutex_lock(&ph->arg->w_mutex);
	write_status("is sleeping\n", ph);
	pthread_mutex_unlock(&ph->arg->w_mutex);
	ft_usleep(ph->arg->sleep);
	pthread_mutex_lock(&ph->arg->w_mutex);
	write_status("is thinking\n", ph);
	pthread_mutex_unlock(&ph->arg->w_mutex);
}

void	routine(t_philo *ph, pthread_mutex_t *f_f, pthread_mutex_t *s_f)
{
	pthread_mutex_lock(f_f);
	pthread_mutex_lock(&ph->arg->w_mutex);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->arg->w_mutex);
	pthread_mutex_lock(s_f);
	pthread_mutex_lock(&ph->arg->w_mutex);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->arg->w_mutex);
	pthread_mutex_lock(&ph->arg->w_mutex);
	write_status("is eating\n", ph);
	pthread_mutex_lock(&ph->arg->time_eat);
	ph->last_eat = actual_time();
	pthread_mutex_unlock(&ph->arg->time_eat);
	pthread_mutex_unlock(&ph->arg->w_mutex);
	ft_usleep(ph->arg->eat);
	pthread_mutex_unlock(s_f);
	pthread_mutex_unlock(f_f);
}

void	launch(t_philo *ph)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (&ph->l_fork < ph->r_fork)
	{
		first_fork = &ph->l_fork;
		second_fork = ph->r_fork;
	}
	else
	{
		first_fork = ph->r_fork;
		second_fork = &ph->l_fork;
	}
	if (!first_fork || !second_fork)
		return ;
	routine(ph, first_fork, second_fork);
	sleep_or_think(ph);
}
