/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 10:39:06 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/09/30 10:45:41 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	*palloc(size_t size)
{
	void	*tmp;

	tmp = malloc(size);
	if (tmp == NULL)
		pexit("\x1b[31mMalloc failed.\n\x1b[0m", 1);
	return (tmp);
}
