/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:03:36 by madamou           #+#    #+#             */
/*   Updated: 2024/06/12 00:16:16 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**ft_static_argv_or_envp(char *cas, char **envp_or_argv)
{
	static char	**argv;
	static char	**envp;

	if (!ft_strcmp("argv", cas) && envp_or_argv)
		argv = envp_or_argv;
	else if (!ft_strcmp("envp", cas) && envp_or_argv)
		envp = envp_or_argv;
	else if (ft_strcmp("argv", cas) == 0)
		return (argv);
	else if (ft_strcmp("envp", cas) == 0)
		return (envp);
	return (envp_or_argv);
}
