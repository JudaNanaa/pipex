/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 00:15:01 by madamou           #+#    #+#             */
/*   Updated: 2024/12/03 02:36:02 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	heredoc(t_pipex *data)
{
	int		fd[2];
	char	*lim;
	char	*line;

	lim = data->argv[2];
	if (pipe(fd) == -1)
		return (ft_dprintf(STDERR_FILENO, "Error heredoc\n"), -1);
	while (1)
	{
		ft_dprintf(STDERR_FILENO, "here_doc> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			ft_dprintf(STDERR_FILENO, "\nPipex: warning: ");
			ft_dprintf(STDERR_FILENO, MSG_EOF, lim);
			break ;
		}
		line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, lim) == 0)
			break ;
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	(free(line), close(fd[1]));
	return (fd[0]);
}

void	first_child_redir(t_pipex *data, int *fd)
{
	close(fd[0]);
	if (ft_strcmp(data->argv[1], "here_doc") != 0)
		data->infile = open(data->argv[1], O_RDONLY);
	if (data->infile == -1)
	{
		if (ft_strcmp(data->argv[1], "here_doc") != 0)
			ft_dprintf(STDERR_FILENO, "Error infile open\n");
		close(fd[1]);
		exit(1);
	}
	dup2(data->infile, STDIN_FILENO);
	close(data->infile);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	last_child_redir(t_pipex *data)
{
	int	outfile;

	if (ft_strcmp(data->argv[1], "here_doc") == 0)
		outfile = open(data->argv[data->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile = open(data->argv[data->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		ft_dprintf(STDERR_FILENO, "Error outfile open\n");
		close(data->infile);
		exit(1);
	}
	dup2(data->infile, STDIN_FILENO);
	close(data->infile);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
}

void	middle_child_redir(t_pipex *data, int *fd)
{
	close(fd[0]);
	dup2(data->infile, STDIN_FILENO);
	close(data->infile);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}
