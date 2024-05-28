/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:28:57 by madamou           #+#    #+#             */
/*   Updated: 2024/05/19 19:56:12 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <unistd.h>

void ft_close_file(int fd_file1, int fd_file2)
{
	if (fd_file1 != -1)
		close(fd_file1);
	if (fd_file2 != -1)
		close(fd_file2);
}

int main(int argc, char **argv)
{
	char *path;
	int fd[2];
	int pid1;
	int pid2;
	char *path2;
	char **argv2;

	(void)argc;
	char **args = ft_split(argv[2], ' ');
	if (!args)
		return (1);
	path = ft_strjoin("/usr/bin/", args[0]);
	if (!path)
		return (ft_free_split(args, ft_strlen_2(args)), 2);
	args = ft_args_add(args, argv[1]);
	if (!args)
		return (ft_free_split(args, ft_strlen_2(args)), 3);
	char *test1[] = {NULL};


	argv2 = ft_split(argv[3], ' ');
	if (!argv2)
		return (ft_free_split(args, ft_strlen_2(args)), 7);
	path2 = ft_strjoin("/usr/bin/", argv2[0]);
	if (!path2)
		return (8);
	if (pipe(fd) < 0)
		return (ft_free_split(args, ft_strlen_2(args)), 4);
	pid1 = fork();
	if (pid1 < 0)
		return (ft_free_split(args, ft_strlen_2(args)), 5);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		execve(path, args, test1);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (ft_free_split(args, ft_strlen_2(args)), 6);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path2, argv2, test1);
	}
	close(fd[1]);
	close(fd[0]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
