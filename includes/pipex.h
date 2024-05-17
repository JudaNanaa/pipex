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

#ifndef _PIPEX_H
# define _PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
#include <string.h>


int ft_check_if_file_exist(char *path);

#endif