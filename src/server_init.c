/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 13:26:26 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/09/30 13:26:37 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

t_server	*server(void)
{
	static t_server	save;

	return (&save);
}

void	server_init(void)
{
	int	i;

	FD_ZERO(SERVER_ACTIVE);
	server()->max = -1;
	server()->buf = palloc(sizeof(t_strbuf) * fd_limit());
	i = 0;
	while (i < fd_limit())
	{
		server()->buf[i++].read = ft_strnew(0);
		server()->buf[i++].write = ft_strnew(0);
		server()->buf[i++].set = 0;
	}
}
