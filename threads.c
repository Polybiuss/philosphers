/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:08:16 by jbergos           #+#    #+#             */
/*   Updated: 2025/02/04 18:42:11 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_create(t_program *prog, pthread_mutex_t *forks)
{
	pthread_t	monitoring;
	int			i;

	if (pthread_create(&monitoring, NULL, &monitor, prog->philos) != 0)
		clear_mutex("Err, creation thread", prog, forks);
	i = 0;
	while (i < prog->philos[0].nb_philos)
	{
		printf("hiiii\n");
		if (pthread_create(&prog->philos[i].thread, NULL, &philo_routine, &prog->philos[i]) != 0)
			clear_mutex("Err, creation thread", prog, forks);
		++i;
	}
	i = 0;
	if (pthread_join(monitoring, NULL) != 0)
		clear_mutex("Err, thread join", prog, forks);
	while (i < prog->philos[i].nb_philos)
	{
		if (pthread_join(prog->philos[i].thread, NULL) != 0)
			clear_mutex("Err, thread join", prog , forks);
		++i;
	}
	return (0);
}