/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 13:37:09 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/07 12:51:26 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	server_do(t_clientbuf *client)
{
	char	*tmp;

	while ((tmp = ft_strchr(client->read, '\n')) != NULL)
	{
		ft_putstr("ServerDo: Socket ");
		ft_putnbr(client->sock);
		ft_putstr(": line found.\n");
		*tmp = 0;
		if (client->read == tmp)
			*tmp = '@';
		else if (client->read[0] == '/')
			server_cmd(client);
		else
			channels_write(client);
		ft_strcpy(client->read, tmp + 1);
	}
}

void	server_do_all(void)
{
	int	i;

	i = 0;
	while (i <= server()->max)
	{
		if (server()->buf[i].set == 1)
			server_do(server()->buf + i);
		++i;
	}
}

int		main(int argc, char *argv[])
{
	t_sock_data	sock;

	get_root();
	if (argc != 2)
		pexit("Usage: ./serveur port\n", 1);
	if ((sock.id = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		pexit("Error: server socket creation failed\n", 1);
	sock.addr.sin_port = htons(ft_atoi(argv[1]));
	sock.addr.sin_family = AF_INET;
	sock.addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock.id, (void*)&(sock.addr), sizeof(sock.addr)) < 0)
		pexit("Error: server bind failed\n", 1);
	printf("Server bound to host %s, port %hd.\n",
		inet_ntoa(sock.addr.sin_addr), ntohs(sock.addr.sin_port));
	if (listen(sock.id, 5) == -1)
		pexit("Error: server listen failed\n", 1);
	printf("Listen worked.\n");
	server_init(sock.id);
	while (42)
	{
		server_select();
		server_do_all();
	}
	return (0);
}
