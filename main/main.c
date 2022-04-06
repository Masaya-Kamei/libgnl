/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:25:30 by mkamei            #+#    #+#             */
/*   Updated: 2022/04/05 14:07:13 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	cat_file_using_gnl(const int fd)
{
	char	*line;
	int		gnl_status;
	int		line_num;

	gnl_status = 1;
	line_num = 0;
	while (gnl_status == 1)
	{
		gnl_status = get_next_line(fd, &line);
		if (gnl_status == -1)
			break ;
		printf("%6d	[%d]:[%s]\n", ++line_num, gnl_status, line);
		free(line);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	int		fd;

	if (argc == 1)
		return (0);
	i = 0;
	while (++i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		cat_file_using_gnl(fd);
		close(fd);
	}
	// system("leaks a.out");
	return (0);
}
