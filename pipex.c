/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrinaldi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:48:04 by nrinaldi          #+#    #+#             */
/*   Updated: 2024/04/09 13:23:10 by nrinaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_proc(int *fd, char **argv, char **envn)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		write(2, "Permission denied error\n", 24);
		exit(1);
	}
	dup2(fd[0], 0);
	dup2(fd_out, 1);
	close(fd[1]);
	ft_exec(argv[3], envn);
}

void	child_proc(int *fd, char **argv, char **envn)
{
	if (access (argv[1], R_OK) != 0)
	{
		perror("No Permission allowed");
		exit(1);
	}
	if (access (argv[1], F_OK) != 0)
	{
		perror("file has not been found");
		exit(1);
	}
	dup2(fd[1], 1);
	dup2(open(argv[1], O_RDONLY), 0);
	close(fd[0]);
	ft_exec(argv[2], envn);
}

int	main(int argc, char **argv, char **envn)
{
	int	fd[2];
	int	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe creation failed");
			exit(1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			exit(1);
		}
		if (!pid)
			child_proc(fd, argv, envn);
		parent_proc(fd, argv, envn);
		waitpid(pid, NULL, 0);
	}
	else
		write(2, "err in source - input.txt cmd1 cmd 2 output.txt", 45);
	return (0);
}
