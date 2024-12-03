/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 01:14:59 by madamou           #+#    #+#             */
/*   Updated: 2024/12/03 02:32:00 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

# define MSG_EOF "here-document delimited by end-of-file (wanted `%s')\n"

typedef struct s_pipex
{
	char	**argv;
	char	**envp;
	int		argc;
	int		infile;
	pid_t	*pid;
	int		nb_cmd;
	int		status;
}			t_pipex;

// Redirections
void		middle_child_redir(t_pipex *data, int *fd);
void		last_child_redir(t_pipex *data);
void		first_child_redir(t_pipex *data, int *fd);
int			heredoc(t_pipex *data);
// Path
char		*find_path(char *cmd, t_pipex *data);

// Child
void		waiting_child(t_pipex *data);
int			create_child(t_pipex *data);

#endif