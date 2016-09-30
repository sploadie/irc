/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 13:37:09 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/09/30 14:18:19 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	server_do(void)
{
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
	server_init();
	server_set(sock.id);
	server()->listen = sock.id;
	while (42)
	{
		server_select();
		server_do();
	}
	return (0);
}
