/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:37:10 by madamou           #+#    #+#             */
/*   Updated: 2024/06/12 03:01:11 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strjoin_with_slash(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (str == NULL)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	str[i] = '/';
	i++;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (free(s1), NULL);
	while (s1[j])
		str[i++] = s1[j++];
	free(s1);
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	**ft_add_command(char **envp, char *argv)
{
	char	**envp_with_command;
	int		index;

	index = 0;
	envp_with_command = malloc(sizeof(char *) * (ft_double_tab_strlen(envp)
				+ 1));
	if (!envp_with_command)
		return (NULL);
	while (envp[index])
	{
		envp_with_command[index] = ft_strjoin_with_slash(envp[index], argv);
		if (!envp_with_command[index])
		{
			ft_free_double_tab(envp_with_command);
			return (NULL);
		}
		index++;
	}
	envp_with_command[index] = NULL;
	return (envp_with_command);
}

char	*ft_try_to_access_path(char **envp, char *argv)
{
	char	**envp_with_command;
	int		index;
	char	*path;

	index = 0;
	envp_with_command = ft_add_command(envp, argv);
	while (envp_with_command[index])
	{
		if (access(envp_with_command[index], F_OK) == 0)
		{
			path = ft_strdup(envp_with_command[index]);
			ft_free_double_tab(envp_with_command);
			return (path);
		}
		index++;
	}
	return (ft_free_double_tab(envp_with_command), NULL);
}
