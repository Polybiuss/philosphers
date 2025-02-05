/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:32:02 by jbergos           #+#    #+#             */
/*   Updated: 2025/02/05 05:59:31 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mp(char *s, t_philo *philo, int id)
{
	long long int	t;

	pthread_mutex_lock(philo->write_lock);
	t = get_time() - philo->time_start;
	if (!dead_loop(philo))
		printf("%llu %d %s\n", t, id, s);
	pthread_mutex_unlock(philo->write_lock);
}

int	philo_dead(t_philo *philo, long long int ttd)
{
	pthread_mutex_lock(philo->eat_lock);
	if (get_time() - philo->last_eat >= ttd && philo->eat == 0)
		return (pthread_mutex_unlock(philo->eat_lock), 1);
	pthread_mutex_unlock(philo->eat_lock);
	return (0);
}

int	is_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nb_philos)
	{
		if (philo_dead(&philos[i], philos[i].ttd))
		{
			mp("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_all_ate(t_philo *philos)
{
	int	i;
	int	all_eat;

	i = 0;
	all_eat = 0;
	if (philos[0].npte == -1)
		return (0);
	while (i < philos[0].nb_philos)
	{
		pthread_mutex_lock(philos[i].eat_lock);
		if (philos[i].nb_eat >= philos[i].npte)
			++all_eat;
		pthread_mutex_unlock(philos[i].eat_lock);
		++i;
	}
	if (all_eat == philos[0].nb_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *phs)
{
	t_philo	*philos;

	philos = (t_philo *)phs;
	while (1)
	{
		if (is_dead(philos) || is_all_ate(philos))
			break ;
	}
	return (phs);
}
