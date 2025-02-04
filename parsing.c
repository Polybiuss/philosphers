/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergos <jbergos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:02:46 by jbergos           #+#    #+#             */
/*   Updated: 2025/02/04 16:14:37 by jbergos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_empty_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '\0')
			return (1);
		++i;
	}
	return (0);
}

int	check_num(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}

int	check_length_arg(char **argv)
{
	int	i;
	int	j;
	int	zero;

	i = 0;
	while (argv[i])
	{
		j = 0;
		zero = 0;
		while (argv[i][zero] == '0' && argv[i][zero])
			++zero;
		while (argv[i][zero + j])
			j++;
		if (j > 10)
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char **argv)
{
	if (check_empty_args(argv))
		return (write(2, "Err, empty args\n", 17), 1);
	if (check_num(argv))
		return (write(2, "Err, args must be int\n", 23), 1);
	if (check_length_arg(argv))
		return (write(2, "Err, int too big", 17), 1);
	if (ft_atoi_scam(argv[1]) <= 0 || ft_atoi_scam(argv[1]) > 200)
		return (write(2, "Err, arg 1 incorrect value", 27), 1);
	if (ft_atoi_scam(argv[2]) <= 0)
		return (write(2, "Err, arg 2 incorrect value", 27), 1);
	if (ft_atoi_scam(argv[3]) <= 0)
		return (write(2, "Err, arg 3 incorrect value", 27), 1);
	if (ft_atoi_scam(argv[4]) <= 0)
		return (write(2, "Err, arg 4 incorrect value", 27), 1);
	if (argv[5] && (ft_atoi_scam(argv[5]) <= 0 || ft_atoi_scam(argv[5]) > 200))
		return (write(2, "Err, arg 5 incorrect value", 27), 1);
	return (0);
}
