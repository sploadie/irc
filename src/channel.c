/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 10:46:33 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/07 13:12:56 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

int		channel_get(char *name)
{
	int			i;
	t_channel	*ch;

	ch = server()->ch;
	i = 0;
	while (ft_strcmp(ch->name, name) && ch->next != NULL)
	{
		ch = ch->next;
		i++;
	}
	if (ft_strcmp(ch->name, name) == 0)
		return (i);
	ch->next = palloc(sizeof(t_channel));
	ch->next->name = ft_strdup(name);
	ch->next->next = NULL;
	return (i + 1);
}

char	*channel_name(int id)
{
	t_channel	*ch;

	ch = server()->ch;
	while (id-- > 0 && ch->next != NULL)
		ch = ch->next;
	if (id >= 0)
		return ("");
	return (ch->name);
}

void	write_msg(char *dest, char *nick, char *msg)
{
	ft_strlcat(dest, "<", BUF_SIZE);
	ft_strlcat(dest, nick, BUF_SIZE);
	ft_strlcat(dest, "> ", BUF_SIZE);
	ft_strlcat(dest, msg, BUF_SIZE);
	ft_strlcat(dest, "\n", BUF_SIZE);
}

void	channels_write(t_clientbuf *client)
{
	int			i;
	t_clientbuf	*clients;

	write_msg(client->write, client->nick, client->read);
	if (client->channel == 0)
		return ;
	clients = server()->buf;
	i = 0;
	while (i <= server()->max)
	{
		if (clients[i].channel == client->channel && i != client->sock)
			write_msg(clients[i].write, client->nick, client->read);
		++i;
	}
}
