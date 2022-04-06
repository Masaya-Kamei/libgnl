/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:03:07 by mkamei            #+#    #+#             */
/*   Updated: 2022/04/06 12:18:07 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_develop.h"

static int	get_valid_last_buf_len(t_dclist *buf_lst, char *nl_ptr)
{
	t_buf	*last_buf;

	last_buf = dclst_last(buf_lst)->p;
	if (nl_ptr)
		return (nl_ptr - get_buf_start(last_buf));
	else
		return (last_buf->left_len);
}

static int	split_into_line_and_save(
	char **line, t_dclist *buf_lst, char *nl_ptr)
{
	const int	last_len = get_valid_last_buf_len(buf_lst, nl_ptr);
	size_t		i;
	t_dclist	*lst;
	t_buf		*buf;

	*line = malloc(get_total_len(dclst_last(buf_lst)->prev) + last_len + 1);
	if (*line == NULL)
		return (-1);
	i = 0;
	lst = dclst_with_take_p(buf_lst->next, (void **)&buf);
	while (lst != dclst_last(buf_lst))
	{
		my_memcpy(&(*line)[i], get_buf_start(buf), buf->left_len);
		i += buf->left_len;
		lst = dclst_with_take_p(dclst_popdel_next(lst, free), (void **)&buf);
	}
	my_memcpy(&(*line)[i], get_buf_start(buf), last_len);
	(*line)[i + last_len] = '\0';
	if (nl_ptr)
		set_buf_member(buf, buf->start_i + last_len + 1,
			buf->left_len - last_len - 1, buf->left_len - last_len - 1);
	else
		dclst_clear(&buf_lst, free);
	return (1);
}

static bool	check_include_nl_in_save(t_dclist *buf_lst, char **nl_ptr)
{
	t_buf	*first_buf;

	*nl_ptr = NULL;
	if (dclst_exist(buf_lst))
	{
		first_buf = dclst_first(buf_lst)->p;
		*nl_ptr = my_memchr(
				get_buf_start(first_buf), '\n', first_buf->left_len);
	}
	return (*nl_ptr != NULL);
}

static int	read_until_include_nl(
	const int fd, t_dclist *buf_lst, char **nl_ptr)
{
	t_dclist	*new_lst;
	t_buf		*new_buf;
	ssize_t		readsize;

	if (check_include_nl_in_save(buf_lst, nl_ptr))
		return (1);
	while (1)
	{
		new_lst = dclst_new_size(sizeof(t_buf));
		if (new_lst == NULL)
			return (-1);
		new_buf = new_lst->p;
		readsize = read(fd, new_buf->buf, BUFFER_SIZE - 1);
		if (readsize <= 0)
			break ;
		new_buf->buf[readsize] = '\0';
		set_buf_member(new_lst->p, 0,
			readsize, readsize + get_total_len(dclst_last(buf_lst)));
		dclst_addback(buf_lst, new_lst);
		*nl_ptr = my_memchr(new_buf->buf, '\n', readsize);
		if (*nl_ptr)
			return (1);
	}
	dclst_delone(new_lst, free);
	return (readsize);
}

int	get_next_line(int fd, char **line)
{
	static t_dclist	*buf_lst;
	char			*nl_ptr;

	if (fd < 0 || fd >= 256 || line == NULL)
		return (-1);
	if (buf_lst == NULL)
	{
		buf_lst = dclst_new_size(sizeof(t_buf));
		if (buf_lst == NULL)
			return (-1);
		((t_buf *)buf_lst->p)->total_len = 0;
	}
	if (read_until_include_nl(fd, buf_lst, &nl_ptr) == -1
		|| split_into_line_and_save(line, buf_lst, nl_ptr) == -1)
	{
		dclst_clear(&buf_lst, free);
		return (-1);
	}
	return (nl_ptr != NULL);
}
