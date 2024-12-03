/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 00:17:28 by madamou           #+#    #+#             */
/*   Updated: 2024/12/03 01:54:07 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_child(t_pipex *data, int *fd, int index)
{
	char	*path;
	char	**args;

	free(data->pid);
	if (index == 0)
		first_child_redir(data, fd);
	else if (index == data->nb_cmd - 1)
		last_child_redir(data);
	else
		middle_child_redir(data, fd);
	if (ft_strcmp(data->argv[1], "here_doc") == 0)
		index++;
	args = ft_split(data->argv[index + 2], " ");
	if (args == NULL)
		(ft_dprintf(STDERR_FILENO, "Error malloc function\n"), exit(-1));
	path = find_path(args[0], data);
	if (path == NULL)
	{
		ft_dprintf(STDERR_FILENO, "Command not found\n");
		free_split(args);
		exit(127);
	}
	execve(path, args, data->envp);
	ft_dprintf(STDERR_FILENO, "Error execve function\n");
	(free_split(args), free(path), exit(-1));
}

int	create_child(t_pipex *data)
{
	int	fd[2];
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (i != data->nb_cmd - 1 && pipe(fd) == -1)
			return (ft_dprintf(STDERR_FILENO, "Error pipe function\n"), 1);
		data->pid[i] = fork();
		if (data->pid[i] == -1)
		{
			if (i != data->nb_cmd - 1)
				(close(fd[0]), close(fd[1]));
			return (ft_dprintf(STDERR_FILENO, "Error fork function\n"), -1);
		}
		if (data->pid[i] == 0)
			exec_child(data, fd, i);
		if (i != data->nb_cmd - 1)
			close(fd[1]);
		if (data->infile != -1)
			close(data->infile);
		data->infile = fd[0];
		i++;
	}
	return (0);
}

void	waiting_child(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		waitpid(data->pid[i], &data->status, 0);
		i++;
	}
	free(data->pid);
	if (WIFEXITED(data->status))
		data->status = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status))
		data->status = 128 + WTERMSIG(data->status);
}
