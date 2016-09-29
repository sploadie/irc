/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoinfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 11:41:19 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/09/29 17:32:56 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	quicklen(char *s)
{
	char *tmp;

	tmp = s;
	while (*tmp != 0)
		++tmp;
	return (tmp - s);
}

char			*strjoinfree(char *s1, char *s2)
{
	char	*new;
	char 	*tmp;

	new = malloc((quicklen(s1) + quicklen(s2) + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	tmp = new;
	while (*s1 != 0)
	{
		*tmp = *s1;
		++tmp;
		++s1;
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
