/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:54:03 by madamou           #+#    #+#             */
/*   Updated: 2024/06/17 00:57:13 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_limiter_newline(char *limiter)
{
	char	*dest;
	int		i;

	i = ft_strlen(limiter);
	dest = malloc(sizeof(char) * (i + 2));
	if (!dest)
		return (NULL);
	ft_strcpy(dest, limiter);
	dest[i++] = '\n';
	dest[i] = '\0';
	return (dest);
}

char	*ft_normal_format(char *line, char *dest, int *i)
{
	int	len;

	len = ft_strlen(dest);
	dest = ft_realloc(dest, 2);
	if (!dest)
		return (NULL);
	while (line[*i] && line[*i] != '$')
	{
		dest = ft_realloc(dest, 2);
		if (!dest)
			return (NULL);
		dest[len++] = line[*i];
		dest[len] = '\0';
		(*i)++;
	}
	return (dest);
}

char	*ft_create_variable(char *line, int i)
{
	int		j;
	char	*var;

	j = 0;
	while (line[i + j] && line[i + j] != ' ' && (line[i + j] < 9
			|| line[i + j] > 13))
		j++;
	var = malloc(sizeof(char) * (j + 2));
	if (!var)
		return (NULL);
	var = ft_strncpy(var, &line[i], j);
	var[j++] = '=';
	var[j] = '\0';
	return (var);
}

char	*ft_check_if_variable_exist(char **envp, char *var, char *dest, int j)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(var, envp[index], j) == 0)
		{
			dest = ft_realloc(dest, ft_strlen(&envp[index][j]));
			if (!dest)
				return (free(var), NULL);
			ft_strcat(dest, &envp[index][j]);
			break ;
		}
		index++;
	}
	if (!envp[index])
	{
		dest = ft_realloc(dest, j + 1);
		if (!dest)
			return (free(var), NULL);
		dest = ft_strcat(dest, "$");
		ft_strcat(dest, var);
		dest[ft_strlen(dest) - 1] = '\0';
	}
	return (free(var), dest);
}

char	*ft_is_evn_variable(char *line, char **envp)
{
	char	*dest;
	char	*var;
	int		i;

	i = 0;
	dest = NULL;
	while (line[i])
	{
		dest = ft_normal_format(line, dest, &i);
		if (dest == NULL)
			return (NULL);
		if (!line[i])
			return (dest);
		if (line[i] == '$')
			i++;
		var = ft_create_variable(line, i);
		if (!var)
			return (free(dest), NULL);
		i = i + ft_strlen(var) - 1;
		dest = ft_check_if_variable_exist(envp, var, dest, ft_strlen(var));
		if (!dest)
			return (NULL);
	}
	return (dest);
}
