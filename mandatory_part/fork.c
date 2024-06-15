/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:29:53 by madamou           #+#    #+#             */
/*   Updated: 2024/06/15 16:30:50 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_creating_child(int **pipes, int i, int argc, int p_index)
{
	pid_t	pid;
	char	**argv;
	char	**envp;

	envp = ft_static_argv_or_envp("envp", NULL);
	argv = ft_static_argv_or_envp("argv", NULL);
	pid = fork();
	if (pid == -1)
		return (ft_printf("Error when creating a fork\n"), 1);
	if (pid == 0)
	{
		if (i == 2)
			return (ft_file_to_command_one(argv, envp, pipes, p_index));
		else if (p_index == 1 && i != 1)
			return (ft_first_command(pipes, i, p_index));
		else if (i == argc - 2)
			return (ft_command_one_to_outfile(argv, argc, pipes, p_index));
		else
			return (ft_command_to_command(pipes, i, p_index));
	}
	return (0);
}

int	ft_fork(int argc, char **argv, int **pipes)
{
	int	i;
	int	p_index;

	if (!ft_strcmp(argv[1], "here_doc"))
		i = 1;
	else
		i = 2;
	p_index = 1;
	while (i <= argc - 2)
	{
		if (!ft_strcmp(argv[i], "here_doc"))
		{
			if (ft_heredoc(argv[i + 1], pipes, p_index) == -1)
				return (1);
			i += 2;
		}
		else
		{
			if (ft_creating_child(pipes, i, argc, p_index) == 1)
				return (1);
			i++;
			p_index++;
		}
	}
	return (ft_free_pipe(pipes, argv), wait(NULL), 0);
}
