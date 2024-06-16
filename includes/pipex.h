/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:51:30 by madamou           #+#    #+#             */
/*   Updated: 2024/06/16 14:33:28 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

int		ft_double_tab_strlen(char **str);
int		ft_file_to_command_one(char **argv, char **envp, int **fd, int p_index);
int		ft_command_one_to_outfile(char **argv, int index, int **pipes,
			int p_index);
int		ft_command_to_command(int **pipes, int index, int p_index);
int		ft_nb_pipes(char **argv);
int		ft_fork(int argc, char **argv, int **pipes);
int		ft_first_command(int **pipes, int i, int p_index);
int		ft_heredoc(char *limiter, int **pipes, int index);

int		**ft_malloc_pipes(char **argv);

char	**ft_static_argv_or_envp(char *cas, char **envp_or_argv);
char	**ft_split_no_malloc(char *s, char *c, char **split);

char	*ft_strjoin_with_slash(char const *s1, char const *s2);
char	*ft_strjoin_free_s1(char *s1, char *s2);
char	*ft_try_to_access_path(char **envp, char *argv);
char	*ft_find_path(char **envp, char *argv);
char	*ft_parse_line(char *line);
char	*ft_limiter_newline(char *limiter);
char	*ft_normal_format(char *line, char *dest, int *i);
char	*ft_create_variable(char *line, int i);
char	*ft_check_if_variable_exist(char **envp, char *var, char *dest, int j);
char	*ft_is_evn_variable(char *line, char **envp);

void	ft_free_pipe(int **pipes, char **argv);
void	ft_free_double_tab(char **tab);

#endif
