/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:54:03 by madamou           #+#    #+#             */
/*   Updated: 2024/06/14 23:46:20 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/pipex.h"
#include <strings.h>
#include <unistd.h>

char *ft_limiter_newline(char *limiter)
{
	char *dest;
	int i;

	i = ft_strlen(limiter);
	dest = malloc(sizeof(char) * (i + 2));
	if (!dest)
		return (NULL);
	ft_strcpy(dest, limiter);
	dest[i++] = '\n';
	dest[i] = '\0';
	return (dest);
}

// char **ft_parse_line(char *line)
// {
// 	char *dest;
//
//
// 	return (dest);
// }

int ft_heredoc(char *limiter, int **pipes, int index)
{
	char *true_limiter;
	char *line;

	true_limiter = ft_limiter_newline(limiter);
	if (!true_limiter)
		return (-1);
	write(STDOUT_FILENO, "> ", 2);	
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (-1);
	// line = ft_parse_line(line);
	while (ft_strcmp(line, true_limiter) != 0)
	{
		write(STDOUT_FILENO, "> ", 2);	
		write(pipes[index - 1][1], line, ft_strlen(line));
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (-1);
	}
	return (0);
}

int ft_creating_child(int **pipes, int i, int argc, int p_index)
{
	pid_t	pid;
	char **argv;
	char **envp; 

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
	int		i;
	int		p_index;

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
	ft_free_pipe(pipes, argv);
	wait(NULL);
	return (0);
}
