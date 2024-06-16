/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:41:06 by madamou           #+#    #+#             */
/*   Updated: 2024/06/14 20:02:05 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <time.h>
#include <unistd.h>

void	ft_free_pipe(int **pipes, char **argv)
{
	int	i;
	int	size;

	i = 0;
	size = ft_nb_pipes(argv) + 1;
	while (i < size)
	{
		(close(pipes[i][0]), close(pipes[i][1]));
		free(pipes[i]);
		i++;
	}
	free(pipes);
	pipes = NULL;
}

void	ft_free_pipe_size(int **pipes, int i)
{
	while (i > 0)
	{
		i--;
		(close(pipes[i][0]), close(pipes[i][1]));
		free(pipes[i]);
	}
	free(pipes);
	pipes = NULL;
}

int	**ft_malloc_pipes(char **argv)
{
	int	i;
	int	**pipes;
	int	size;

	size = ft_nb_pipes(argv) + 1;
	pipes = malloc(sizeof(int *) * size);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < size)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (ft_free_pipe_size(pipes, i), NULL);
		if (pipe(pipes[i]) == -1)
			return (ft_free_pipe_size(pipes, i + 1), NULL);
		i++;
	}
	return (pipes);
}

int	ft_nb_pipes(char **argv)
{
	int	nb_args;
	int	i;

	i = 0;
	nb_args = ft_double_tab_strlen(argv);
	nb_args -= 2;
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "here_doc"))
		{
			nb_args -= 2;
			i++;
		}
		i++;
	}
	if (ft_strcmp(argv[1], "here_doc") != 0)
		nb_args--;
	nb_args--;
	return (nb_args);
}
