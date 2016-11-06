/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:17:30 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/06 20:57:13 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

char	*client_read(int fd, char *str)
{
	char	buf[BUF_SIZE + 1];
	int		ret;

	if (fd == 0)
		ret = read(fd, buf, BUF_SIZE);
	else
		ret = recv(fd, buf, BUF_SIZE, 0);
	if (ret < 1)
		return (str);
	buf[ret] = 0;
	return (strjoinfree(str, buf));
}

char	*client_write(int fd, char *str)
{
	if (ft_strlen(str) == 0)
		return (str);
	if (fd == 1)
		write(1, str, ft_strlen(str));
	else
		send(fd, str, ft_strlen(str), 0);
	return (strfresh(str));
}

void	client_select(void)
{
	int				ret;
	struct timeval	timeout;

	FD_ZERO(CLIENT_READ);
	FD_ZERO(CLIENT_WRITE);
	FD_COPY(CLIENT_ACTIVE, CLIENT_READ);
	FD_COPY(CLIENT_ACTIVE, CLIENT_WRITE);
	timeout.tv_sec = 0;
	timeout.tv_usec = 50;
	ret = select(client()->fd + 1, CLIENT_READ, CLIENT_WRITE, NULL, &timeout);
	if (ret < 0)
		return ((void)perr("Select encountered an error.\n"));
	if (FD_ISSET(0, CLIENT_READ))
		client()->cl_read = client_read(0, client()->cl_read);
	if (FD_ISSET(client()->fd, CLIENT_READ) && client()->fd > 0)
		client()->sv_read = client_read(client()->fd, client()->sv_read);
	if (FD_ISSET(client()->fd, CLIENT_WRITE) && client()->fd > 0)
		client()->sv_write = client_write(client()->fd, client()->sv_write);
}
