/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 17:46:20 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/07 13:41:37 by tgauvrit         ###   ########.fr       */
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
		ft_strlcat(client->write, "Error: Unknown command\n", BUF_SIZE);
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
	&& (ft_strlcat(client->write, "Error: Nick taken\n", BUF_SIZE))));
	}
	ft_strlcat(client->write, "Notice: Nick changed\n", BUF_SIZE);
}

static void	server_cmd_join(t_clientbuf *cl)
{
	int			i;
	t_clientbuf	*cs;

	if (cl->read[5] != ' ' && cl->read[5] != 'e' && cl->read[5] != '\0')
		return ((void)(ft_strlcat(cl->write,
			"Error: Unknown command\n", BUF_SIZE)));
		if (cl->read[5] != ' ' || ft_strlen(ft_strrchr(cl->read, ' ') + 1) == 0)
	{
		if (cl->channel == 0)
			return ;
		ft_strlcat(cl->write, "Notice: Leaving channel #", BUF_SIZE);
		ft_strlcat(cl->write, channel_name(cl->channel), BUF_SIZE);
		ft_strlcat(cl->write, "\n", BUF_SIZE);
		return ((void)(cl->channel = 0));
	}
	cl->channel = channel_get(ft_strrchr(cl->read, ' ') + 1);
	cs = server()->buf;
	i = -1;
	while (++i <= server()->max)
		if (cs[i].channel == cl->channel)
		{
			ft_strlcat(cs[i].write, "Notice: New user joined #", BUF_SIZE);
			ft_strlcat(cs[i].write, channel_name(cl->channel), BUF_SIZE);
			ft_strlcat(cs[i].write, "\n", BUF_SIZE);
		}
}

static void	server_cmd_who(t_clientbuf *client)
{
	int			i;
	t_clientbuf	*clients;

	if (client->channel == 0)
	{
		ft_strlcat(client->write, "Notice: In Lobby\n", BUF_SIZE);
		return ;
	}
	ft_strlcat(client->write, "Channel #", BUF_SIZE);
	ft_strlcat(client->write, channel_name(client->channel), BUF_SIZE);
	ft_strlcat(client->write, " Members\n", BUF_SIZE);
	clients = server()->buf;
	i = 0;
	while (i <= server()->max)
	{
		if (clients[i].channel == client->channel)
		{
			ft_strlcat(client->write, clients[i].nick, BUF_SIZE);
			ft_strlcat(client->write, "\n", BUF_SIZE);
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
			write_msg(clients[i].write, client->nick,
				client->read + 5 + len + 1);
			return ;
		}
		++i;
	}
	ft_strlcat(client->write, "Error: Nick not found\n", BUF_SIZE);
}

void		server_cmd(t_clientbuf *client)
{
	if (ft_strncmp(client->read, "/nick", 5) == 0)
		server_cmd_nick(client);
	else if (ft_strncmp(client->read, "/join", 5) == 0)
		server_cmd_join(client);
	else if (ft_strncmp(client->read, "/leave", 7) == 0)
		server_cmd_join(client);
	else if (ft_strncmp(client->read, "/who", 5) == 0)
		server_cmd_who(client);
	else if (ft_strncmp(client->read, "/msg ", 5) == 0)
		server_cmd_msg(client);
	else
		ft_strlcat(client->write, "Error: Unknown command\n", BUF_SIZE);
}
