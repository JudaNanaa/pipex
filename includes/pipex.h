/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:51:30 by madamou           #+#    #+#             */
/*   Updated: 2024/05/17 10:16:32 by madamou          ###   ########.fr       */
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

int		ft_free_double_tab(char **tab, int index);
int		ft_double_tab_strlen(char **str);
int		ft_file_to_command_one(char **argv, char **envp, int *fd);
int		ft_command_one_to_command_two(char **argv, char **envp, int *fd);

char	**ft_args_add(char **args);

char	*ft_strjoin_with_slash(char const *s1, char const *s2);
char	*ft_strjoin_free_s1(char *s1, char *s2);
char	*ft_try_to_access_path(char **envp, char *argv);
char	*ft_find_path(char **envp, char *argv);

#endif
