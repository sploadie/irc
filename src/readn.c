/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 12:11:47 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/09/29 17:57:01 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static size_t	quicklen(char *s)
{
	char *tmp;

	tmp = s;
	while (*tmp != 0)
		++tmp;
	return (tmp - s);
}

static char		*strupgrade(char *str, size_t buffer)
{
	char	*new;
	char 	*tmp;
	char	*str_tmp;

	if (str == NULL)
		return (ft_strnew(buffer + 1));
	new = malloc((quicklen(str) + buffer + 1) * sizeof(char));
	if (new == NULL)
		pexit("Malloc failed.\n", 1);
	str_tmp = str;
	tmp = new;
	while (*str_tmp != 0)
	{
		*tmp = *str_tmp;
		++tmp;
		++str_tmp;
	}
	str_tmp = tmp + buffer;
	while (str_tmp != tmp)
	{
		*str_tmp = 0;
		--str_tmp;
	}
	free(str);
	return (new);
}

static char		*strdump(char **str, int fd)
{
	char	*tmp;

	tmp = *str;
	if (tmp == NULL)
		tmp = ft_strnew(0);
	if (fd < -1)
		*str = ft_strnew(0);
	return (tmp);
}

char			*readn(int fd)
{
	static char	*buf = NULL;
	char		*tmp;
	int			ret;
	int			offset;

	if (fd < 0)
		return (strdump(&buf, fd));
	buf = strupgrade(buf, BUF_SIZE);
	offset = 0;
	while ((ret = read(fd, buf + offset, BUF_SIZE)) > 0)
	{
		if (ft_strchr(buf, '\n') != NULL)
			break ;
		buf = strupgrade(buf, BUF_SIZE);
		offset += ret;
	}
	tmp = buf;
	if ((buf = ft_strchr(buf, '\n')) == NULL)
		buf = ft_strnew(0);
	else
		buf = ft_strdup(buf + 1);
	if (ft_strchr(tmp, '\n') != NULL)
		*(ft_strchr(tmp, '\n') + 1) = 0;
	return (tmp);
}
