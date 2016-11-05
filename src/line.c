/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:24:42 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/04 16:50:23 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

char	*linedup(char *str)
{
	char	*tmp;

	if ((tmp = ft_strchr(str, '\n')) == NULL)
		return (ft_strnew(0));
	*tmp = 0;
	str = ft_strdup(str);
	str = strjoinfree(str, "\n");
	*tmp = '\n';
	return (str);
}

char	*linepop(char *str)
{
	char	*tmp;

	if ((tmp = ft_strchr(str, '\n')) == NULL)
		return (str);
	tmp = ft_strdup(tmp + 1);
	free(str);
	return (tmp);
}
