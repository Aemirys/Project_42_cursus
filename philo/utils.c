/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:12:11 by emy               #+#    #+#             */
/*   Updated: 2024/08/05 09:27:13 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *ph, int i)
{
	pthread_mutex_lock(&ph->arg->dead);
	if (i)
		ph->arg->stop = i;
	if (ph->arg->stop)
	{
		pthread_mutex_unlock(&ph->arg->dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->arg->dead);
	return (0);
}

int	check_death_status(t_data *p)
{
	pthread_mutex_lock(&p->data.dead);
	if (p->data.stop)
	{
		pthread_mutex_unlock(&p->data.dead);
		return (1);
	}
	pthread_mutex_unlock(&p->data.dead);
	return (0);
}

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_exit("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

int	ft_exit(char *str)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	return (0);
}
