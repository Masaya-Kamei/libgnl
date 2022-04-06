/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 11:51:52 by mkamei            #+#    #+#             */
/*   Updated: 2022/04/06 10:42:19 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_develop.h"

char	*get_buf_start(t_buf *target_buf)
{
	return (target_buf->buf + target_buf->start_i);
}

size_t	get_total_len(t_dclist *target_buf_lst)
{
	return (((t_buf *)target_buf_lst->p)->total_len);
}

void	set_buf_member(t_buf *target_buf,
	const int start_i, const size_t left_len, const size_t total_len)
{
	target_buf->start_i = start_i;
	target_buf->left_len = left_len;
	target_buf->total_len = total_len;
}

void	*my_memchr(const void *s, int c, size_t n)
{
	const uint64_t	char_mask = (unsigned char)c * 0x0101010101010101ull;
	uint64_t		ull_char;
	size_t			i;

	i = 0;
	while (n - i > 7)
	{
		ull_char = *((uint64_t *)(s + i)) ^ char_mask;
		if ((ull_char - 0x0101010101010101) & ~ull_char & 0x8080808080808080)
			break ;
		i += 8;
	}
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}

void	*my_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;

	i = 0;
	while (n - i > 7)
	{
		*((uint64_t *)(dst + i)) = *((uint64_t *)(src + i));
		i += 8;
	}
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
