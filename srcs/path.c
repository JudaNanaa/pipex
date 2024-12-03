/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 00:16:11 by madamou           #+#    #+#             */
/*   Updated: 2024/12/03 00:16:34 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path_in_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_pipex *data)
{
	char	*path_var;
	char	**split_paths;
	int		i;

	if (cmd == NULL || access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	path_var = find_path_in_env(data->envp);
	if (path_var == NULL)
		return (NULL);
	split_paths = ft_split(path_var + 5, ":");
	if (split_paths == NULL)
		return (NULL);
	i = 0;
	while (split_paths[i])
	{
		path_var = ft_strjoin(split_paths[i], "/");
		if (path_var == NULL)
			return (free_split(split_paths), NULL);
		path_var = ft_re_strjoin(path_var, cmd);
		if (path_var == NULL || access(path_var, F_OK | X_OK) == 0)
			return (free_split(split_paths), path_var);
		free(path_var);
		i++;
	}
	return (free_split(split_paths), NULL);
}
