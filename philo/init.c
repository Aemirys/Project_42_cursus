/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:34:07 by emy               #+#    #+#             */
/*   Updated: 2024/08/06 09:53:57 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	num(char **argv, int i, int j)
{
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9' || ft_strlen(argv[j]) > 10)
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	ft_parser(int argc, char **argv, t_data *p)
{
	if ((argc == 5 || argc == 6) && num(argv, 0, 1))
	{
		p->data.total = ft_atoi(argv[1]);
		p->data.die = ft_atoi(argv[2]);
		p->data.eat = ft_atoi(argv[3]);
		p->data.sleep = ft_atoi(argv[4]);
		p->data.must_eat = -1;
		if (argc == 6)
			p->data.must_eat = ft_atoi(argv[5]);
		if (p->data.total <= 0 || p->data.die <= 0 || p->data.eat <= 0
			|| p->data.sleep <= 0)
			return (0);
		return (1);
	}
	return (0);
}

void	init_mutex(t_data *p)
{
	pthread_mutex_init(&p->data.w_mutex, NULL);
	pthread_mutex_init(&p->data.dead, NULL);
	pthread_mutex_init(&p->data.time_eat, NULL);
	pthread_mutex_init(&p->data.finish, NULL);
}

int	init(t_data *p)
{
	int	i;

	i = 0;
	p->data.start_t = actual_time();
	p->data.stop = 0;
	p->data.nb_p_finish = 0;
	init_mutex(p);
	while (i < p->data.total)
	{
		p->ph[i].id = i + 1;
		p->ph[i].last_eat = p->data.start_t;
		p->ph[i].nb_eat = 0;
		p->ph[i].finish = 0;
		p->ph[i].r_fork = NULL;
		pthread_mutex_init(&p->ph[i].l_fork, NULL);
		if (p->data.total == 1)
			return (1);
		if (i == p->data.total - 1)
			p->ph[i].r_fork = &p->ph[0].l_fork;
		else
			p->ph[i].r_fork = &p->ph[i + 1].l_fork;
		i++;
	}
	return (1);
}
