/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_connect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 11:21:07 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/06 20:55:44 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

t_sock_data	*c_connect(char *hostname, char *port)
{
	t_sock_data		sock;
	struct hostent	*host;

	if ((sock.id = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return (NULL);
	sock.addr.sin_family = AF_INET;
	sock.addr.sin_port = htons(ft_atoi(port));
	if ((host = gethostbyname(hostname)) == NULL)
		return (NULL);
	ft_memcpy(&sock.addr.sin_addr.s_addr, host->h_addr, host->h_length);
	if (connect(sock.id, (void*)&(sock.addr), sizeof(sock.addr)) < 0)
		return (NULL);
	return (ft_memdup(&sock, sizeof(t_sock_data)));
}

int			c_disconnect(t_sock_data *sock)
{
	int	ret;

	ret = close(sock->id);
	if (ret == 0)
		free(sock);
	return (ret);
}

int			c_reconnect(t_sock_data *sock, char *hostname, char *port)
{
	int				ret;
	struct hostent	*host;

	ret = close(sock->id);
	if ((sock->id = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return ((sock->id = -1));
	sock->addr.sin_family = AF_INET;
	sock->addr.sin_port = htons(ft_atoi(port));
	if ((host = gethostbyname(hostname)) == NULL)
		return ((sock->id = -1));
	ft_memcpy(&sock->addr.sin_addr.s_addr, host->h_addr, host->h_length);
	if (connect(sock->id, (void*)&(sock->addr), sizeof(sock->addr)) < 0)
		return ((sock->id = -1));
	return (ret);
}
