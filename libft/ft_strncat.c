/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 22:09:53 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/06 18:57:15 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, char *src, int nb)
{
	int		i;
	char	*end_dest;

	if (nb <= 0)
		return (dest);
	end_dest = dest + ft_strlen(dest);
	i = 0;
	while (i < nb && src[i] != '\0')
	{
		end_dest[i] = src[i];
		i++;
	}
	while (i < nb)
	{
		end_dest[i++] = '\0';
	}
	end_dest[i] = '\0';
	return (dest);
}
