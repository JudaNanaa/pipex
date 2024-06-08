/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:45:28 by madamou           #+#    #+#             */
/*   Updated: 2024/06/07 21:01:46 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <fcntl.h>
#include <unistd.h>

int	ft_file_to_command_one(char **argv, char **envp, int *fd)
{
	char	**command1;
	int		infile;
	char	*path;

	command1 = ft_split(argv[2], " ");
	if (!command1)
		return (1);
	path = ft_find_path(envp, command1[0]);
	if (!path)
	{
		ft_free_double_tab(command1, ft_double_tab_strlen(command1));
		return (write(1, "Error when finding the path\n", 28), 1);
	}
	command1 = ft_args_add(command1);
	infile = open(argv[1], O_RDWR);
	if (infile == -1)
		return (ft_printf("Error when opening the file\n"), 0);
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	if (execve(path, command1, envp) == -1)
		ft_printf("Error with execve command 1\n");
	return (1);
}

int	ft_command_one_to_command_two(char **argv, char **envp, int *fd)
{
	char	**command2;
	char	*path;
	int		output;

	command2 = ft_split(argv[3], " ");
	if (!command2)
		return (1);
	path = ft_find_path(envp, command2[0]);
	if (!path)
	{
		ft_free_double_tab(command2, ft_double_tab_strlen(command2));
		return (write(1, "Error when finding the path\n", 28), 1);
	}
	command2 = ft_args_add(command2);
	output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	dup2(output, STDOUT_FILENO);
	if (execve(path, command2, envp) == -1)
		ft_printf("Error with execve command 2\n");
	return (1);
}
