/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:45:28 by madamou           #+#    #+#             */
/*   Updated: 2024/06/16 17:41:08 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <fcntl.h>
#include <stdio.h>

int	ft_file_to_command_one(char **argv, char **envp, int **pipes, int p_index)
{
	char	**command1;
	int		infile;
	char	*path;

	command1 = ft_split(argv[2], " ");
	if (!command1)
		return (ft_free_pipe(pipes, argv), 1);
	path = ft_find_path(envp, command1[0]);
	infile = open(argv[1], O_RDWR);
	if (infile == -1)
		return (perror(strerror(errno)), 1);
	if (dup2(infile, STDIN_FILENO)
		+ dup2(pipes[p_index][1], STDOUT_FILENO) < 0)
		return (close(infile), ft_free_pipe(pipes, argv),
			perror(strerror(errno)), 1);
	(close(infile), ft_free_pipe(pipes, argv));
	execve(path, command1, envp);
	perror(strerror(errno));
	return (free(path), ft_free_double_tab(command1), 1);
}

int	ft_command_one_to_outfile(char **argv, int argc, int **pipes, int p_index)
{
	char	**command2;
	char	*path;
	int		outfile;
	char	**envp;

	envp = ft_static_argv_or_envp("envp", NULL);
	command2 = ft_split(argv[argc - 2], " ");
	if (!command2)
		return (ft_free_pipe(pipes, argv), 1);
	path = ft_find_path(envp, command2[0]);
	if (!ft_strcmp(argv[argc - 5], "here_doc"))
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		return (printf("oui\n"), perror(strerror(errno)), 1);
	if (dup2(pipes[p_index - 1][0], STDIN_FILENO)
		+ dup2(outfile, STDOUT_FILENO) < 0)
		return (ft_free_pipe(pipes, argv), close(outfile),
			perror(strerror(errno)), 1);
	(ft_free_pipe(pipes, argv), close(outfile));
	(execve(path, command2, envp), ft_free_pipe(pipes, argv), close(outfile));
	return (perror(strerror(errno)), 1);
}

int	ft_command_to_command(int **pipes, int i, int p_index)
{
	char	**command2;
	char	*path;
	char	**argv;
	char	**envp;

	argv = ft_static_argv_or_envp("argv", NULL);
	envp = ft_static_argv_or_envp("envp", NULL);
	command2 = ft_split(argv[i], " ");
	if (!command2)
		return (ft_free_pipe(pipes, argv), 1);
	path = ft_find_path(envp, command2[0]);
	if (dup2(pipes[p_index - 1][0], STDIN_FILENO)
		+ dup2(pipes[p_index][1], STDOUT_FILENO) < 0)
		return (ft_free_pipe(pipes, argv), perror(strerror(errno)), 1);
	ft_free_pipe(pipes, argv);
	execve(path, command2, envp);
	perror(strerror(errno));
	return (free(path), ft_free_double_tab(command2), 1);
}

int	ft_first_command(int **pipes, int i, int p_index)
{
	char	**command2;
	char	*path;
	char	**argv;
	char	**envp;

	argv = ft_static_argv_or_envp("argv", NULL);
	envp = ft_static_argv_or_envp("envp", NULL);
	command2 = ft_split(argv[i], " ");
	if (!command2)
		return (ft_free_pipe(pipes, argv), 1);
	path = ft_find_path(envp, command2[0]);
	if (dup2(pipes[p_index - 1][0], STDIN_FILENO)
		+ dup2(pipes[p_index][1], STDOUT_FILENO) < 0)
		return (ft_free_pipe(pipes, argv), perror(strerror(errno)), 1);
	ft_free_pipe(pipes, argv);
	execve(path, command2, envp);
	perror(strerror(errno));
	return (free(path), ft_free_double_tab(command2), 1);
}
