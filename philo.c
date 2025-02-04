/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 07:08:59 by jbergos           #+#    #+#             */
/*   Updated: 2025/02/04 18:41:10 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_program		prog;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (argc != 5 && argc != 6)
		return (write(2, "Err, need 4 or 5 arg\n", 22), 1);
	if (check_args(argv))
		return (1);
	philos = malloc(sizeof(t_philo) * (ft_atoi_scam(argv[1])));
	forks = malloc(sizeof(pthread_mutex_t) * (ft_atoi_scam(argv[1])));
	init_prog(&prog, philos);
	init_forks(forks, ft_atoi_scam(argv[1]));
	init_philos(philos, &prog, forks, argv);
	printf("nb : %d\n", prog.philos[0].nb_philos);
	thread_create(&prog, forks);
	clear_mutex(NULL, &prog, forks);
	free(philos);
	free(forks);
}
