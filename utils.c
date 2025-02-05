/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:30:00 by jbergos           #+#    #+#             */
/*   Updated: 2025/02/05 15:24:05 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		++i;
	return (i);
}

int	ft_atoi_scam(char *s)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		res = (10 * res) + (s[i] - '0');
		++i;
	}
	if (res > 2147483647)
		return (-1);
	return ((int)res);
}

long long int	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	clear_mutex(char *s, t_program *prog, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (s)
	{
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&prog->eat_lock);
	pthread_mutex_destroy(&prog->write_lock);
	pthread_mutex_destroy(&prog->dead_lock);
	while (i < prog->philos[0].nb_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		++i;
	}
}

void	smart_sleep(long long int time, int *dead)
{
	long long int	i;

	i = get_time();
	while (*dead != 1)
	{
		if (i >= time)
			break ;
		usleep(50);
		i = get_time();
	}
}
