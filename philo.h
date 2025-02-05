/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 07:05:42 by jbergos           #+#    #+#             */
/*   Updated: 2025/02/05 15:20:48 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eat;
	int				nb_eat;
	long long int	last_eat;
	long long int	ttd;
	long long int	tte;
	long long int	tts;
	long long int	time_start;
	int				nb_philos;
	int				npte;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*eat_lock;
}	t_philo;

typedef struct s_program
{
	int				dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	eat_lock;
	t_philo			*philos;
}	t_program;

int				check_args(char **argv);
int				ft_atoi_scam(char *s);
void			init_input(t_philo *philo, char **argv);
void			init_philos(t_philo *philos, t_program *program, \
pthread_mutex_t *forks, char **argv);
void			init_forks(pthread_mutex_t *forks, int nb_philo);
void			init_prog(t_program *prog, t_philo *philos);
long long int	get_time(void);
void			mp(char *s, t_philo *philo, int id);
int				dead_loop(t_philo *philo);
void			*philo_routine(void *ph);
int				thread_create(t_program *prog, pthread_mutex_t *forks);
void			*monitor(void *phs);
void			eat(t_philo *philo);
void			clear_mutex(char *s, t_program *prog, pthread_mutex_t *forks);
void			smart_sleep(long long int time, int *dead);
#endif