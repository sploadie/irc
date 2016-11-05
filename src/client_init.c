/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:02:20 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/05 14:07:18 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

t_client	*client(void)
{
	static t_client	save;

	return (&save);
}

void	client_init(int fd)
{
	client()->fd = fd;
	FD_ZERO(CLIENT_ACTIVE);
	FD_SET(0, CLIENT_ACTIVE);
	FD_SET(1, CLIENT_ACTIVE);
	FD_SET(fd, CLIENT_ACTIVE);
	client()->cl_read = ft_strnew(0);
	client()->cl_write = ft_strnew(0);
	client()->sv_read = ft_strnew(0);
	client()->sv_write = ft_strnew(0);
}

void	client_reset(int fd)
{
	client()->fd = fd;
	FD_ZERO(CLIENT_ACTIVE);
	FD_SET(0, CLIENT_ACTIVE);
	FD_SET(1, CLIENT_ACTIVE);
	FD_SET(fd, CLIENT_ACTIVE);
	client()->cl_read  = strfresh(client()->cl_read);
	client()->cl_write = strfresh(client()->cl_write);
	client()->sv_read  = strfresh(client()->sv_read);
	client()->sv_write = strfresh(client()->sv_write);
}
