/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@contact.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:28:57 by madamou           #+#    #+#             */
/*   Updated: 2024/05/17 11:12:17 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void ft_close_file(int fd_file1, int fd_file2)
{
	if (fd_file1 != -1)
		close(fd_file1);
	if (fd_file2 != -1)
		close(fd_file2);
}

int main(int argc, char **argv)
{
	int fd_file1;

	if (argc == 5)
	{
		if (ft_check_if_file_exist(argv[1]) == -1)
			perror(strerror(errno));
		else
		{	
			fd_file1 = open(argv[1], O_RDWR);
			if (fd_file1 == -1)
				return (perror(strerror(errno)), 0);
			execve();
			close(fd_file1);
		}
	}
	return (0);
}
