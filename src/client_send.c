/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 17:20:51 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/02 18:07:01 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	client_send(t_sock_data *sock, char *input)
{
	send(sock->id, input, ft_strlen(input), 0);
	(void)sock;
	ft_putendl(input);
}
