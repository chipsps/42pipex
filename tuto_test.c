/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchi <pchi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:55:32 by pchi              #+#    #+#             */
/*   Updated: 2024/08/01 20:59:16 by pchi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

// Define a macro for a specific child exit code (if we do not
// specify this exit code during compilation with the
// -D CHILD_EXIT_CODE=[number] option), by default, it will be 42:
// #ifndef CHILD_EXIT_CODE
// # define CHILD_EXIT_CODE 42
// #endif

// // Define a macro for the expected exit status
// #define EXPECTED_CODE 42

// Child process routine:
void	child_routine(void)
{
	printf("\e[36mChild: Hi! I'm the child in an infinite loop.\e[0m\n");
	while (1)
		continue ;
}

void	kill_and_get_children(pid_t *pid)
{
	int	status;
	int	i;

	printf("Parent: I'm the murderous parent.\n");
	i = 0;
	while (i < 3)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
	printf("Parent: I killed all my children!!! Mwahahahaaa!\n");
	i = 0;
	while (i < 3)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			printf("Parent: Child [%d] terminated normally.", pid[i]);
		else if (WIFSIGNALED(status))
		{
			printf("Parent: Child [%d] was interrupted.\n", pid[i]);
			if (WTERMSIG(status) == SIGTERM)
				printf("\e[31mParent: Child [%d] got the %d signal, SIGTERM\e[0m\
						\n", pid[i], WTERMSIG(status));
			if (WTERMSIG(status) == SIGKILL)
				printf("\e[31mParent: Child [%d] got the %d signal, SIGKILL\e[0m\
						\n", pid[i], WTERMSIG(status));
		}
		i++;
	}
}

// Parent process routine:
// void	parent_routine(pid_t pid)
// {
// 	int status;

// 	printf("Parent: I'm the parent. PID received from fork = %d\n", pid);
// 	printf("Parent: Waiting for my child with PID [%d].\n", pid);
// 	waitpid(pid, &status, 0); // Wait for child
// 	printf("Parent: My child exited with status %d\n", status);
// 	if (WIFEXITED(status)) // If child exited normally
// 	{
// 		printf("Parent: My child's exit code is %d\n",
// 			   WEXITSTATUS(status));
// 		if (WEXITSTATUS(status) == EXPECTED_CODE)
// 			printf("Parent: That's the code I expected!\n");
// 		else
// 			printf("Parent: I was not expecting that code...\n");
// 	}
// }

int	main(void)
{
	pid_t	pid[3];
	int		i;

	i = 0;
	while (i < 3)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (EXIT_FAILURE);
		else if (pid[i] == 0)
			child_routine();
		else if (pid[i] > 0)
			printf("Parent: Child #%d created with pid = %d.\n", i, pid[i]);
		usleep(1000);//delay next child's creation
		i++;
	}
	kill_and_get_children(pid);
	return (EXIT_SUCCESS);
}
