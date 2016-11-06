/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 21:12:36 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/06 21:13:02 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	read_out(int sock, char *buf)
{
	ft_putstr("Reading from socket ");
	ft_putnbr(sock);
	ft_putstr(": \"");
	ft_putstr(buf);
	ft_putstr("\"\n");
}
