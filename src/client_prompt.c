/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 11:36:21 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/09/29 17:40:18 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static void			print_prompt(void)
{
	ft_putstr("\x1b[32mclient >\x1b[0m ");
}

static char			*read_prompt(void)
{
	char	*input;

	print_prompt();
	ft_putstr(readn(-1));
	input = readn(0);
	if (*(input + ft_strlen(input) - 1) != '\n')
		write(1, "\n", 1);
	return (input);
}

static t_sock_data	*change_connection(t_sock_data *sock, char *input)
{
	char		*tmp;

	if (ft_strncmp(input, "/connect ", 9) != 0)
		return (NULL);
	if ((tmp = ft_strchr(input + 9, ' ')) == NULL)
		return (NULL);
	*tmp = 0;
	if (sock == NULL)
		sock = c_connect(input + 9, tmp + 1);
	else
		c_reconnect(sock, input + 9, tmp + 1);
	*tmp = ' ';
	return (sock);
}

void				client_prompt(t_sock_data *sock)
{
	char	*input;

	if (sock->id == -1)
		return ((void)prompt_connect_only(sock));
	input = read_prompt();
	if (change_connection(sock, input) != NULL)
	{
		ft_putstr("\x1b[32mClient disconnected\n\x1b[0m");
		if (sock->id == -1)
			ft_putstr("\x1b[31mClient reconnection failed\n\x1b[0m");
	}
	client_send(sock, input);
	free(input);
	return ;
}

t_sock_data			*prompt_connect_only(t_sock_data *sock)
{
	char		*input;

	ft_putstr("\x1b[32mYou must connect with /connect to continue\n\x1b[0m");
	input = read_prompt();
	sock = change_connection(sock, input);
	free(input);
	return (sock);
}
