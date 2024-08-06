/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estosche <estosche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:12:24 by emy               #+#    #+#             */
/*   Updated: 2024/08/06 15:00:32 by estosche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_args
{
	int				total;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	long int		start_t;
	int				nb_p_finish;
	int				stop;
	pthread_mutex_t	w_mutex;
	pthread_mutex_t	dead;
	pthread_mutex_t	time_eat;
	pthread_mutex_t	finish;

}				t_args;

typedef struct s_philo
{
	int				id;
	int				finish;
	long int		last_eat;
	unsigned int	nb_eat;
	pthread_t		thread_id;
	pthread_t		thread_death_id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	t_args			*arg;
}				t_philo;

typedef struct s_data
{
	t_philo	*ph;
	t_args	data;
}			t_data;

//main
void		ft_end(t_data *p);

// init
int			num(char **argv, int i, int j);
int			ft_parser(int argc, char **argv, t_data *p);
void		init_mutex(t_data *p);
int			init(t_data *p);

//thread
void		*is_dead(void *data);
void		*thread(void *data);
int			ft_thread(t_data *p);

//launch
void		write_status(char *str, t_philo *ph);
void		sleep_or_think(t_philo *ph);
void		routine(t_philo *ph, pthread_mutex_t *f_f, pthread_mutex_t *s_f);
void		launch(t_philo *ph);

//utils
long int	actual_time(void);
int			check_death_status(t_data *p);
int			check_death(t_philo *ph, int i);
int			ft_exit(char *str);
void		ft_usleep(long int time_in_ms);

//utils_libft
ssize_t		ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *str);

#endif