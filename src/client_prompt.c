/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 11:36:21 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/05 17:13:09 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

static void			print_prompt(void)
{
	ft_putstr("\x1b[32mclient >\x1b[0m ");
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

void				client_prompt(void)
{
	char		*tmp;

	print_prompt();
	while (42)
	{
		client_select();
		if (ft_strlen(client()->sv_read) != 0)
		{
			ft_putstr("\r\033[2K\x1b[0m");
			ft_putstr(client()->sv_read);
			client()->sv_read = strfresh(client()->sv_read);
			print_prompt();
		}
		if (ft_strchr(client()->cl_read, '\n') == NULL)
			continue ;
		if (ft_strncmp(client()->cl_read, "/connect ", 9) == 0)
		{
			prompt_connect_only();
			continue ;
		}
		client()->sv_write = strjoinfree(client()->sv_write, (tmp = linedup(client()->cl_read)));
		free(tmp);
		client()->cl_read = linepop(client()->cl_read);
		print_prompt();
	}
}

t_sock_data	*prompt_connect_only(void)
{
	t_sock_data *sock;
	char		*input;

	sock = NULL;
	client_reset(0);
	if (ft_strchr(client()->cl_read, '\n') == NULL)
	{
		ft_putstr("\x1b[32mYou must connect with /connect to continue\n\x1b[0m");
		print_prompt();
	}
	while (sock == NULL)
	{
		client_select();
		input = linedup(client()->cl_read);
		if (ft_strlen(input) != 0)
		{
			client()->cl_read = linepop(client()->cl_read);
			if (ft_strncmp(input, "/connect ", 9) == 0)
				if ((sock = change_connection(sock, input)) == NULL)
					perr("Error: client server connection failed\n");
			if (sock == NULL)
				ft_putstr("\x1b[32mYou must connect with /connect to continue\n\x1b[0m");
			if (sock == NULL)
				print_prompt();
		}
		free(input);
	}
	client_reset(sock->id);
	return (sock);
}
