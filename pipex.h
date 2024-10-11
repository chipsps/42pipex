/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchi <pchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:21:07 by pchi              #+#    #+#             */
/*   Updated: 2024/10/11 17:30:08 by pchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_proc
{
	char	**cmd_arr;
	char	*path;
}			t_proc;

void	find_path(char **envp, t_proc *child);
void	pipex(t_proc (*child)[2], char **av, char **envp);
void	child_one(char *filename, char **envp, t_proc child, int fd[2]);
void	child_two(char *filename, char **envp, t_proc child, int fd[2]);
void	free_exit(t_proc (*child)[2], int status);

#endif