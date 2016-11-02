/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 13:37:16 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/02 18:22:30 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

int			main(int argc, char *argv[])
{
	t_sock_data		*sock;

	if (argc > 3 || (argc == 2 && ft_strcmp(argv[1], "-h") == 0))
		pexit("Usage: ./client [machine [port]]\n", 1);
	if (argc == 1)
	{
		while ((sock = prompt_connect_only(NULL)) == NULL)
			perr("Error: client server connection failed\n");
	}
	else if (argc == 2)
		sock = c_connect(argv[1], "6697");
	else
		sock = c_connect(argv[1], argv[2]);
	if (sock == NULL)
	{
		pexit("Error: client server connection failed\n", 1);
		while ((sock = prompt_connect_only(NULL)) == NULL)
			perr("Error: client server connection failed\n");
	}
	ft_putstr("Client connected to server\n");
	while (42)
		client_prompt(sock);
	return (0);
}
