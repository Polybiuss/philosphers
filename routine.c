/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:20:19 by jbergos           #+#    #+#             */
/*   Updated: 2025/02/05 15:23:03 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	mp("is thinking", philo, philo->id);
}

void	dream(t_philo *philo)
{
	mp("is sleeping", philo, philo->id);
	smart_sleep(get_time() + philo->tts, philo->dead);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	mp("has taken a fork", philo, philo->id);
	if (philo->nb_philos == 1)
	{
		smart_sleep(get_time() + philo->ttd, philo->dead);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	mp("has taken a fork", philo, philo->id);
	philo->eat = 1;
	mp("is eating", philo, philo->id);
	pthread_mutex_lock(philo->eat_lock);
	philo->last_eat = get_time();
	philo->nb_eat++;
	pthread_mutex_unlock(philo->eat_lock);
	smart_sleep(get_time() + philo->tte, philo->dead);
	philo->eat = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (ph);
}
