/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:51:30 by madamou           #+#    #+#             */
/*   Updated: 2024/06/14 19:46:44 by madamou          ###   ########.fr       */
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
int		ft_command_one_to_outfile(char **argv, int index, int **pipes, int p_index);
int		ft_command_to_command(int **pipes, int index, int p_index);
int ft_nb_pipes(char **argv);
int	ft_fork(int argc, char **argv, int **pipes);
int	ft_first_command(int **pipes, int i, int p_index);

int		**ft_malloc_pipes(char **argv);

char	**ft_static_argv_or_envp(char *cas, char **envp_or_argv);

char	*ft_strjoin_with_slash(char const *s1, char const *s2);
char	*ft_strjoin_free_s1(char *s1, char *s2);
char	*ft_try_to_access_path(char **envp, char *argv);
char	*ft_find_path(char **envp, char *argv);

void	ft_free_pipe(int **pipes, char **argv);
void	ft_free_double_tab(char **tab);

#endif
