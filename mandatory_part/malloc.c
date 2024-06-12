/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:41:06 by madamou           #+#    #+#             */
/*   Updated: 2024/06/11 21:40:58 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <unistd.h>

void	ft_free_pipe(int **pipes, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		(close(pipes[i][0]), close(pipes[i][1]));
		free(pipes[i++]);
	}
	free(pipes);
	pipes = NULL;
}

int	**ft_malloc_pipes(int size)
{
	int	i;
	int	**pipes;

	pipes = malloc(sizeof(int *) * size);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < size)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (ft_free_pipe(pipes, i), NULL);
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}
