/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:28:57 by madamou           #+#    #+#             */
/*   Updated: 2024/06/08 17:22:13 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**ft_remove_key_in_path(char **envp)
{
	int		len;
	char	**envp_without_key;
	int		index;

	index = -1;
	len = ft_double_tab_strlen(envp);
	envp_without_key = malloc(sizeof(char *) * (len + 1));
	if (!envp_without_key)
		return (NULL);
	while (++index < len)
		envp_without_key[index] = ft_strdup(ft_strchr(envp[index], '=') + 1);
	envp_without_key[index] = NULL;
	return (envp_without_key);
}

char	*ft_strcat_all_envp(char **envp_without_key)
{
	char	*strcat_all_envp;
	int		len;
	int		index;

	len = 0;
	index = 0;
	while (envp_without_key[index])
		len += ft_strlen(envp_without_key[index++]);
	strcat_all_envp = malloc(sizeof(char) * (len + 1));
	if (!strcat_all_envp)
		return (NULL);
	index = 0;
	strcat_all_envp[0] = '\0';
	while (envp_without_key[index])
		strcat_all_envp = ft_strjoin_free_s1(strcat_all_envp,
				envp_without_key[index++]);
	return (strcat_all_envp);
}

char	*ft_find_path(char **envp, char *argv)
{
	char	**envp_without_key;
	char	*strcat_all_envp;
	char	**split_all_envp;
	char	*path;

	envp_without_key = ft_remove_key_in_path(envp);
	if (!envp_without_key)
		return (NULL);
	strcat_all_envp = ft_strcat_all_envp(envp_without_key);
	if (!strcat_all_envp)
	{
		ft_free_double_tab(envp_without_key,
			ft_double_tab_strlen(envp_without_key));
		return (NULL);
	}
	ft_free_double_tab(envp_without_key,
		ft_double_tab_strlen(envp_without_key));
	split_all_envp = ft_split(strcat_all_envp, ":\n");
	if (!split_all_envp)
		return (free(strcat_all_envp), NULL);
	path = ft_try_to_access_path(split_all_envp, argv);
	ft_free_double_tab(split_all_envp, ft_double_tab_strlen(split_all_envp));
	return (free(strcat_all_envp), path);
}

int	main(int argc, char **argv, char **envp)
{
	int	pid;
	int	fd[2];

	(void)argc;
	if (pipe(fd) == -1)
		return (ft_printf("Error when creating pipe\n"), 1);
	pid = fork();
	if (pid == -1)
		return (ft_printf("Error when try to fork\n"), 1);
	if (pid == 0)
	{
		if (ft_file_to_command_one(argv, envp, fd) == 1)
			return (1);
	}
	else
	{
		if (ft_command_one_to_command_two(argv, envp, fd) == 1)
			return (1);
	}
	return (0);
}
