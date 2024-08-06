/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:02:48 by emy               #+#    #+#             */
/*   Updated: 2024/08/06 09:53:08 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*is_dead(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	ft_usleep(ph->arg->die + 1);
	pthread_mutex_lock(&ph->arg->time_eat);
	pthread_mutex_lock(&ph->arg->finish);
	if (!check_death(ph, 0) && !ph->finish && ((actual_time() - ph->last_eat) \
	>= (long)(ph->arg->die)))
	{
		pthread_mutex_unlock(&ph->arg->time_eat);
		pthread_mutex_unlock(&ph->arg->finish);
		pthread_mutex_lock(&ph->arg->w_mutex);
		write_status("died\n", ph);
		pthread_mutex_unlock(&ph->arg->w_mutex);
		check_death(ph, 1);
	}
	else
	{
		pthread_mutex_unlock(&ph->arg->time_eat);
		pthread_mutex_unlock(&ph->arg->finish);
	}
	return (NULL);
}

void	*thread(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	if (ph->id % 2 == 0)
		ft_usleep(ph->arg->eat / 10);
	pthread_create(&ph->thread_death_id, NULL, is_dead, data);
	pthread_detach(ph->thread_death_id);
	while (!check_death(ph, 0))
	{
		launch(ph);
		if ((int)++ph->nb_eat == ph->arg->must_eat)
		{
			pthread_mutex_lock(&ph->arg->finish);
			ph->finish = 1;
			ph->arg->nb_p_finish++;
			if (ph->arg->nb_p_finish == ph->arg->total)
				check_death((pthread_mutex_unlock(&ph->arg->finish), ph), 2);
			else
				pthread_mutex_unlock(&ph->arg->finish);
			return (NULL);
		}
	}
	return (NULL);
}

int	ft_thread(t_data *p)
{
	int	i;

	i = 0;
	while (i < p->data.total)
	{
		p->ph[i].arg = &p->data;
		if (pthread_create(&p->ph[i].thread_id, NULL, thread, &p->ph[i]) != 0)
			return (ft_exit("Pthread failled\n"));
		i++;
	}
	return (1);
}
