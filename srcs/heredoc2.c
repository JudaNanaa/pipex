/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:31:34 by madamou           #+#    #+#             */
/*   Updated: 2024/06/15 17:05:25 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_parse_line(char *line)
{
	char	*dest;
	char	**envp;

	envp = ft_static_argv_or_envp("envp", NULL);
	dest = ft_strchr(line, '$');
	if (!dest)
		return (line);
	dest = ft_is_evn_variable(line, envp);
	return (free(line), dest);
}

int	ft_heredoc(char *limiter, int **pipes, int index)
{
	char	*true_limiter;
	char	*line;

	true_limiter = ft_limiter_newline(limiter);
	if (!true_limiter)
		return (-1);
	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (free(true_limiter), -1);
	line = ft_parse_line(line);
	if (!line)
		return (free(true_limiter), -1);
	while (ft_strcmp(line, true_limiter) != 0)
	{
		write(STDOUT_FILENO, "> ", 2);
		write(pipes[index - 1][1], line, ft_strlen(line));
		(free(line), line = get_next_line(STDIN_FILENO));
		if (!line)
			return (free(true_limiter), -1);
		line = ft_parse_line(line);
		if (!line)
			return (free(true_limiter), -1);
	}
	return (free(line), free(true_limiter), 0);
}
