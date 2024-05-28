/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:56:16 by itahri            #+#    #+#             */
/*   Updated: 2024/05/28 03:58:21 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_strlen_2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_free_split(char **split, int index)
{
	if (split[index] == NULL)
	{
		while (index >= 0)
			free(split[index--]);
		free(split);
		return (0);
	}
	return (1);
}

char	**ft_args_add(char **args, char *str)
{
	int		len_args;
	char	**sortie;
	int		i;

	i = 0;
	len_args = ft_strlen_2(args);
	sortie = malloc(sizeof(char *) * (len_args + 1 + 1));
	if (!sortie)
		return (NULL);
	while (i < len_args)
	{
		sortie[i] = malloc(sizeof(char) * (ft_strlen(args[i]) + 1));
		if (!sortie)
			return (ft_free_split(sortie, i - 1), NULL);
		ft_strcpy(sortie[i], args[i]);
		i++;
	}
	sortie[i] = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!sortie)
		return (ft_free_split(sortie, i - 1), NULL);
	ft_strcpy(sortie[i], str);
	sortie[++i] = 0;
	return (sortie);
}
