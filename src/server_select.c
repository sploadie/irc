/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 12:00:15 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/06 21:14:41 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	server_set(int sock)
{
	server()->buf[sock].set = 1;
	ft_strncpy(server()->buf[sock].nick, "Anon", 9);
	server()->buf[sock].read = strfresh(server()->buf[sock].read);
	server()->buf[sock].write = strfresh(server()->buf[sock].write);
	server()->buf[sock].channel = 0;
	FD_SET(sock, SERVER_ACTIVE);
	if (sock > server()->max)
		server()->max = sock;
}

void	server_clr(int sock)
{
	int	i;

	printf("Server: disconnecting from socket %d\n", sock);
	ft_bzero(server()->buf[sock].nick, 10);
	server()->buf[sock].set = 0;
	server()->buf[sock].channel = 0;
	FD_CLR(sock, SERVER_ACTIVE);
	if (sock == server()->max)
	{
		i = sock;
		while (--i >= 0)
		{
			if (server()->buf[i].set == 1)
				break ;
		}
		server()->max = i;
	}
}

void	server_accept(void)
{
	int				new_sock;
	t_sockaddr_in	addr;
	socklen_t		size;

	if (FD_ISSET(server()->listen, SERVER_READ))
	{
		size = sizeof(t_sockaddr_in);
		new_sock = accept(server()->listen, (void*)&addr, &size);
		printf("Server: connection from host %s, port %hd: Socket %d\n",
			inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), new_sock);
		server_set(new_sock);
	}
}

void	server_read(int sock)
{
	char	buf[BUF_SIZE + 1];
	int		ret;
	char	*tmp;

	ret = recv(sock, buf, BUF_SIZE, 0);
	if (ret < 1)
		return (server_clr(sock));
	buf[ret] = 0;
	read_out(sock, buf);
	tmp = server()->buf[sock].read;
	server()->buf[sock].read = ft_strjoin(tmp, buf);
	free(tmp);
}

void	server_select(void)
{
	int				i;
	struct timeval	timeout;

	FD_ZERO(SERVER_READ);
	FD_ZERO(SERVER_WRITE);
	FD_COPY(SERVER_ACTIVE, SERVER_READ);
	FD_COPY(SERVER_ACTIVE, SERVER_WRITE);
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	i = select(server()->max + 1, SERVER_READ, SERVER_WRITE, NULL, &timeout);
	if (i < 0)
		return ((void)perr("Select encountered an error.\n"));
	i = 0;
	while (i <= server()->max)
	{
		if (server()->buf[i].set == 1 && FD_ISSET(i, SERVER_READ))
			server_read(i);
		if (server()->buf[i].set == 1 && FD_ISSET(i, SERVER_WRITE))
		{
			send(i, server()->buf[i].write, strlen(server()->buf[i].write), 0);
			server()->buf[i].write = strfresh(server()->buf[i].write);
		}
		++i;
	}
	server_accept();
}
