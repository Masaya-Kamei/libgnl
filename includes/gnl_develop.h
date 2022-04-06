/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoshie <hyoshie@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:09:39 by hyoshie           #+#    #+#             */
/*   Updated: 2021/09/23 09:09:39 by hyoshie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_DEVELOP_H
# define GNL_DEVELOP_H

# include <stdlib.h>
# include <unistd.h>
# include "dclist.h"

# define BUFFER_SIZE 1025

typedef struct s_buf
{
	char	buf[BUFFER_SIZE];
	int		start_i;
	size_t	left_len;
	size_t	total_len;
}			t_buf;

// utils
char	*get_buf_start(t_buf *target_buf);
size_t	get_total_len(t_dclist *target_buf_lst);
void	set_buf_member(t_buf *target_buf,
			const int start_i, const size_t left_len, const size_t total_len);
void	*my_memchr(const void *buf, int ch, size_t n);
void	*my_memcpy(void *dst, const void *src, size_t n);

#endif
