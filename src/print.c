/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 13:36:48 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/09/29 18:01:40 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	pexit(char *str, int outno)
{
	write(2, str, ft_strlen(str));
	exit(outno);
}

int		perr(char *str)
{
	ft_putstr_fd("\x1b[31m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\x1b[0m", 2);
	return (0);
}
