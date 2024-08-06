/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:12:07 by emy               #+#    #+#             */
/*   Updated: 2024/08/05 16:54:19 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_end(t_data *p)
{
	int	i;

	i = -1;
	while (!check_death_status(p))
		ft_usleep(1);
	while (++i < p->data.total)
		pthread_join(p->ph[i].thread_id, NULL);
	pthread_mutex_destroy(&p->data.w_mutex);
	i = -1;
	while (++i < p->data.total)
		pthread_mutex_destroy(&p->ph[i].l_fork);
	if (p->data.stop == 2)
		printf("Each philo has eaten %d time(s)\n", p->data.must_eat);
	pthread_mutex_lock(&p->data.finish);
	pthread_mutex_unlock(&p->data.finish);
	free(p->ph);
}

int	main(int argc, char **argv)
{
	t_data	p;

	if (!(ft_parser(argc, argv, &p)))
		return (ft_exit("Invalid arguments\n"));
	p.ph = malloc(sizeof(t_philo) * p.data.total);
	if (!p.ph)
		return (ft_exit("Error malloc\n"));
	if (!init(&p) || !ft_thread(&p))
		return (free(p.ph), 0);
	ft_end(&p);
}
