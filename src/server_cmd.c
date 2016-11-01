/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 17:46:20 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/01 18:10:43 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

void	server_cmd_nick(t_clientbuf *client)
{
	if (ft_strlen(client->read) == 6)
		ft_strncpy(client->nick, "Anon", 9);
	else
		ft_strncpy(client->nick, client->read + 6, 9);

}

void	server_cmd_join(t_clientbuf *client)
{
	;
}

void	server_cmd_who(t_clientbuf *client)
{
	;
}

void	server_cmd_msg(t_clientbuf *client)
{
	;
}

void	server_cmd(t_clientbuf *client)
{
	if (ft_strncmp(client->read, "/nick ", 6) == 0)
		server_cmd_nick(client);
	else if (ft_strncmp(client->read, "/join ", 6) == 0)
		server_cmd_join(client);
	else if (ft_strncmp(client->read, "/who ", 5) == 0)
		server_cmd_who(client);
	else if (ft_strncmp(client->read, "/msg ", 5) == 0)
		server_cmd_msg(client);
	else
		client->write = strjoinfree(client->write, "Error: Unknown command\n");
}
