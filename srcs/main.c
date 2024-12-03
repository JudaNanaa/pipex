/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 01:14:25 by madamou           #+#    #+#             */
/*   Updated: 2024/12/03 02:19:05 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc < 5)
		return (ft_dprintf(2, "Pipex need at least 4 arguments\n"), 1);
	if (argc == 5 && ft_strcmp(argv[1], "here_doc") == 0)
		return (ft_dprintf(2, "Pipex need 5 arguments if here_doc\n"), 1);
	ft_bzero(&data, sizeof(t_pipex));
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	data.infile = -1;
	data.nb_cmd = argc - 3;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		data.infile = heredoc(&data);
		data.nb_cmd = argc - 4;
	}
	data.pid = malloc(sizeof(pid_t) * data.nb_cmd);
	if (data.pid == NULL)
		return (ft_dprintf(STDERR_FILENO, "Error malloc function\n"), 1);
	if (create_child(&data) == -1)
		return (free(data.pid), -1);
	waiting_child(&data);
	return (data.status);
}
