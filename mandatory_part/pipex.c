/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:45:28 by madamou           #+#    #+#             */
/*   Updated: 2024/06/12 02:59:16 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	ft_file_to_command_one(char **argv, char **envp, int **fd, int size)
{
	char	**command1;
	int		infile;
	char	*path;

	command1 = ft_split(argv[2], " ");
	if (!command1)
		return (ft_free_pipe(fd, size), 1);
	path = ft_find_path(envp, command1[0]);
	if (!path)
	{
		ft_free_double_tab(command1);
		return (write(1, "Error when finding the path\n", 28), 1);
	}
	infile = open(argv[1], O_RDWR);
	if (infile == -1)
		return (ft_printf("Error when opening the file\n"), 0);
	(dup2(infile, STDIN_FILENO), dup2(fd[0][1], STDOUT_FILENO));
	(close(infile), ft_free_pipe(fd, size));
	if (execve(path, command1, envp) == -1)
		ft_printf("Error with execve command 1\n");
	return (1);
}

int	ft_command_one_to_outfile(char **argv, int argc, int **pipes)
{
	char	**command2;
	char	*path;
	int		output;
	char	**envp;

	envp = ft_static_argv_or_envp("envp", NULL);
	command2 = ft_split(argv[argc - 2], " ");
	if (!command2)
		return (ft_free_pipe(pipes, argc - 3), 1);
	path = ft_find_path(envp, command2[0]);
	if (!path)
	{
		(ft_free_double_tab(command2), ft_free_pipe(pipes, argc - 3));
		return (write(1, "Error when finding the path\n", 28), 1);
	}
	output = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output == -1)
		return (ft_printf("Error when opening the file\n"), 0);
	(dup2(pipes[argc - 5][0], STDIN_FILENO), dup2(output, STDOUT_FILENO));
	(ft_free_pipe(pipes, ft_double_tab_strlen(argv) - 3), close(output));
	if (execve(path, command2, envp) == -1)
		ft_printf("Error with execve command 2\n");
	return (1);
}

int	ft_command_to_command(int i, int **pipes)
{
	char	**command2;
	char	*path;
	char	**argv;
	char	**envp;

	argv = ft_static_argv_or_envp("argv", NULL);
	envp = ft_static_argv_or_envp("envp", NULL);
	command2 = ft_split(argv[i + 2], " ");
	if (!command2)
		return (1);
	path = ft_find_path(envp, command2[0]);
	if (!path)
	{
		ft_free_double_tab(command2);
		return (write(1, "Error when finding the path\n", 28), 1);
	}
	(dup2(pipes[i - 1][0], STDIN_FILENO), dup2(pipes[i][1], STDOUT_FILENO));
	ft_free_pipe(pipes, ft_double_tab_strlen(argv) - 3);
	if (execve(path, command2, envp) == -1)
		ft_printf("Error with execve command 2\n");
	return (1);
}
