/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:49:40 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/07 13:33:04 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

int			main(int argc, char *argv[])
{
	t_sock_data		*sock;

	if (argc > 3 || (argc == 2 && ft_strcmp(argv[1], "-h") == 0))
		pexit("Usage: ./client [machine [port]]\n", 1);
	client_init(0);
	if (argc == 1)
		sock = prompt_connect_only();
	else if (argc == 2)
		sock = c_connect(argv[1], "6697");
	else
		sock = c_connect(argv[1], argv[2]);
	if (sock == NULL)
	{
		perr("Error: client server connection failed\n");
		sock = prompt_connect_only();
	}
	ft_putstr("Client connected to server\n");
	client_reset(sock->id);
	print_prompt(NULL);
	client_prompt();
	free(sock);
	return (0);
}
