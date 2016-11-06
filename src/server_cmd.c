/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 17:46:20 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/06 21:26:05 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static void	server_cmd_nick(t_clientbuf *client)
{
	char		*tmp;
	int			i;
	t_clientbuf	*clients;

	if (client->read[5] != ' ' && client->read[5] != '\0')
	{
		client->write = strjoinfree(client->write, "Error: Unknown command\n");
		return ;
	}
	tmp = ft_strrchr(client->read, ' ');
	if (tmp == NULL || tmp[1] == '\0')
		return ((void)ft_strncpy(client->nick, "Anon", 9));
	tmp = ft_strncpy(client->nick, tmp + 1, 9);
	while (*tmp != '\0')
		if (*(tmp++) == '\n')
			*(tmp - 1) = 'n';
	clients = server()->buf;
	i = -1;
	while (++i <= server()->max)
	{
		if (ft_strcmp(clients[i].nick, client->nick) == 0 && i != client->sock)
			return ((void)(ft_strncpy(client->nick, "Anon", 9)
	&& (client->write = strjoinfree(client->write, "Error: Nick taken\n"))));
	}
	client->write = strjoinfree(client->write, "Notice: Nick changed\n");
}

static void	server_cmd_join(t_clientbuf *cl)
{
	int			i;
	t_clientbuf	*cs;

	if (cl->read[5] != ' ' && cl->read[5] != '\0')
		return ((void)(cl->write = strjoinfree(cl->write, "Error: Ba join\n")));
	if (cl->read[5] == '\0' || ft_strlen(ft_strrchr(cl->read, ' ') + 1) == 0)
	{
		if (cl->channel == 0)
			return ;
		cl->write = strjoinfree(cl->write, "Notice: Leaving channel <");
		cl->write = strjoinfree(cl->write, channel_name(cl->channel));
		cl->write = strjoinfree(cl->write, ">\n");
		return ((void)(cl->channel = 0));
	}
	cl->channel = channel_get(ft_strrchr(cl->read, ' ') + 1);
	cs = server()->buf;
	i = -1;
	while (++i <= server()->max)
		if (cs[i].channel == cl->channel)
		{
			cs[i].write = strjoinfree(cs[i].write, "Notice: New user joined <");
			cs[i].write = strjoinfree(cs[i].write, channel_name(cl->channel));
			cs[i].write = strjoinfree(cs[i].write, ">\n");
		}
}

static void	server_cmd_who(t_clientbuf *client)
{
	int			i;
	t_clientbuf	*clients;

	if (client->channel == 0)
	{
		client->write = strjoinfree(client->write, "Notice: In Lobby\n");
		return ;
	}
	client->write = strjoinfree(client->write, "Channel <");
	client->write = strjoinfree(client->write, channel_name(client->channel));
	client->write = strjoinfree(client->write, "> Members\n");
	clients = server()->buf;
	i = 0;
	while (i <= server()->max)
	{
		if (clients[i].channel == client->channel)
		{
			client->write = strjoinfree(client->write, clients[i].nick);
			client->write = strjoinfree(client->write, "\n");
		}
		++i;
	}
}

static void	server_cmd_msg(t_clientbuf *client)
{
	int			i;
	size_t		len;
	t_clientbuf	*clients;
	char		*tmp;

	tmp = client->read + 5;
	clients = server()->buf;
	i = 0;
	while (i <= server()->max)
	{
		len = ft_strlen(clients[i].nick);
		if (ft_strncmp(tmp, clients[i].nick, len) == 0 && tmp[len] == ' ')
		{
			client->read += 5 + len + 1;
			clients[i].write = write_msg(clients[i].write, client);
			client->read -= 5 + len + 1;
			return ;
		}
		++i;
	}
	client->write = strjoinfree(client->write, "Error: Nick not found\n");
}

void		server_cmd(t_clientbuf *client)
{
	if (ft_strncmp(client->read, "/nick", 5) == 0)
		server_cmd_nick(client);
	else if (ft_strncmp(client->read, "/join", 5) == 0)
		server_cmd_join(client);
	else if (ft_strncmp(client->read, "/who", 5) == 0)
		server_cmd_who(client);
	else if (ft_strncmp(client->read, "/msg ", 5) == 0)
		server_cmd_msg(client);
	else
		client->write = strjoinfree(client->write, "Error: Unknown command\n");
}
