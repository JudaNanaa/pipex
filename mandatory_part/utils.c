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

int	ft_double_tab_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_free_double_tab(char **split, int index)
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

char	**ft_args_add(char **args)
{
	int		len_args;
	char	**sortie;
	int		i;

	i = 0;
	len_args = ft_double_tab_strlen(args);
	sortie = malloc(sizeof(char *) * (len_args + 1));
	if (!sortie)
		return (NULL);
	while (i < len_args)
	{
		sortie[i] = malloc(sizeof(char) * (ft_strlen(args[i]) + 1));
		if (!sortie)
			return (ft_free_double_tab(sortie, i - 1), NULL);
		ft_strcpy(sortie[i], args[i]);
		i++;
	}
	sortie[i] = 0;
	return (ft_free_double_tab(args, ft_double_tab_strlen(args)), sortie);
}
