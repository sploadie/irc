/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 13:26:26 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/06 20:58:54 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

t_server	*server(void)
{
	static t_server	save;

	return (&save);
}

void		server_init(int sock)
{
	int	i;

	FD_ZERO(SERVER_ACTIVE);
	server()->max = -1;
	server()->buf = palloc(sizeof(t_clientbuf) * fd_limit());
	server()->ch = palloc(sizeof(t_channel));
	server()->ch->name = ft_strdup("Lobby");
	server()->ch->next = NULL;
	i = 0;
	printf("FD Limit: %d\n", fd_limit());
	while (i < fd_limit())
	{
		server()->buf[i].nick = ft_strnew(9);
		server()->buf[i].read = ft_strnew(0);
		server()->buf[i].write = ft_strnew(0);
		server()->buf[i].set = 0;
		server()->buf[i].sock = i;
		server()->buf[i].channel = 0;
		++i;
	}
	FD_SET(sock, SERVER_ACTIVE);
	server()->listen = sock;
	server()->buf[sock].set = 2;
}
