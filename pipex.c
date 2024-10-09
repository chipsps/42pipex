/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchi <pchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:23:09 by pchi              #+#    #+#             */
/*   Updated: 2024/10/09 20:41:03 by pchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	main(int ac, char **av)
// {
// 	int	fd[2];

// 	if (ac != 5)
// 	{
// 		ft_putstr_fd("Error: Bad arguments\n", 2);
// 		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (pipe(fd) < 0)
// 	{
// 		perror("");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (0);
// }
/*需要减2行*/
// if (*envp == NULL)
// 	return ;
void	find_path(char **envp, t_proc *child)
{
	char	**paths;
	char	*cmd_path_tmp;
	int		i;

	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	paths = ft_split((*envp + 5), ':');
	if (paths == NULL)
		return ;
	child->path = NULL;
	i = -1;
	while (paths[++i] && child->cmd_arr[0])
	{
		cmd_path_tmp = ft_strjoin(paths[i], "/");
		child->path = ft_strjoin(cmd_path_tmp, child->cmd_arr[0]);
		free(cmd_path_tmp);
		if (access(child->path, F_OK) == 0)
			break ;
		free(child->path);
		child->path = NULL;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}

void	pipex(t_proc (*child)[2], char **av, char **envp)
{
	int	fd[2];
	int	pid[2];

	if (pipe(fd) == -1)
		free_exit(child, EXIT_FAILURE);
	pid[0] = fork();
	if (pid[0] == -1)
		free_exit(child, EXIT_FAILURE);
	if (pid[0] == 0)
	{
		child_one(av[1], envp, (*child)[0], fd);
		free_exit(child, EXIT_FAILURE);
	}
	pid[1] = fork();
	if (pid[1] == -1)
		free_exit(child, EXIT_FAILURE);
	if (pid[1] == 0)
	{
		child_two(av[4], envp, (*child)[1], fd);
		free_exit(child, EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}

void	free_exit(t_proc (*child)[2], int status)
{
	int	i;

	i = -1;
	while ((*child)[0].cmd_arr[++i])
		free((*child)[0].cmd_arr[i]);
	free((*child)[0].cmd_arr);
	free((*child)[0].path);
	i = -1;
	while ((*child)[1].cmd_arr[++i])
		free((*child)[1].cmd_arr[i]);
	free((*child)[1].cmd_arr);
	free((*child)[1].path);
	exit(status);
}

void	child_one(char *filename, char **envp, t_proc child, int fd[2])
{
	int	fd_src;

	fd_src = open(filename, O_RDONLY, 0644);
	if (fd_src == -1)
	{
		perror(filename);
		return ;
	}
	if (!child.path)
	{
		ft_putstr_fd(child.cmd_arr[0], 2);
		ft_putstr_fd(": command not found.\n", 2);
		return ;
	}
	if (access(child.path, X_OK) != 0)
	{
		perror(child.cmd_arr[0]);
		return ;
	}
	dup2(fd_src, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execve(child.path, child.cmd_arr, envp);
	perror("pipex");
	exit(EXIT_FAILURE);
}

void	child_two(char *filename, char **envp, t_proc child, int fd[2])
{
	int	fd_dst;

	fd_dst = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!child.path)
	{
		ft_putstr_fd(child.cmd_arr[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return ;
	}
	if (access(child.path, X_OK) != 0)
	{
		perror(child.cmd_arr[0]);
		return ;
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_dst, STDOUT_FILENO);
	close(fd[1]);
	execve(child.path, child.cmd_arr, envp);
	perror("pipex");
	exit(EXIT_FAILURE);
}
