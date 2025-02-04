/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:28:29 by jbergos           #+#    #+#             */
/*   Updated: 2025/02/04 18:38:47 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_input(t_philo *philo, char **argv)
{
	philo->ttd = ft_atoi_scam(argv[2]);
	philo->tte = ft_atoi_scam(argv[3]);
	philo->tts = ft_atoi_scam(argv[4]);
	philo->nb_philos = ft_atoi_scam(argv[1]);
	if (argv[5])
		philo->npte = ft_atoi_scam(argv[5]);
	else
		philo->npte = -1;
}

void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi_scam(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].eat = 0;
		philos[i].nb_eat = 0;
		init_input(&philos[i], argv);
		philos[i].time_start = get_time();
		philos[i].last_eat = get_time();
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].eat_lock = &program->eat_lock;
		philos[i].dead = &program->dead;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].nb_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		++i;
	}
}

void	init_prog(t_program *prog, t_philo *philos)
{
	prog->dead = 0;
	prog->philos = philos;
	pthread_mutex_init(&prog->write_lock, NULL);
	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->eat_lock, NULL);
}
