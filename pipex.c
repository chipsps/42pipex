/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchi <pchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:23:09 by pchi              #+#    #+#             */
/*   Updated: 2024/08/02 17:50:33 by pchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	int	fd[2];

	if (ac != 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	return (0);
}
