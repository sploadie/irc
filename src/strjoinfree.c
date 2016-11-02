/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoinfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 11:41:19 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/02 14:28:55 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

char	*strfresh(char *str)
{
	free(str);
	return (ft_strnew(0));
}

char	*strjoinfree(char *s1, char *s2)
{
	char	*new;
	char 	*tmp;
	char 	*s1_ptr;

	new = palloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	tmp = new;
	s1_ptr = s1;
	while (*s1_ptr != 0)
	{
		*tmp = *s1_ptr;
		++tmp;
		++s1_ptr;
	}
	while (*s2 != 0)
	{
		*tmp = *s2;
		++tmp;
		++s2;
	}
	*tmp = 0;
	free(s1);
	return (new);
}
