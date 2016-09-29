/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 15:35:45 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/09/29 17:30:01 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_H
# define IRC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/param.h>
# include <stdint.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <dirent.h>
# include "libft.h"

# include <sys/select.h>

# define BUF_SIZE 256

typedef struct sockaddr_in	t_sockaddr_in;

typedef struct		s_sock_data
{
	int				id;
	t_sockaddr_in	addr;
}					t_sock_data;

void				client_prompt(t_sock_data *sock);
t_sock_data			*prompt_connect_only(t_sock_data *sock);
void				client_send(t_sock_data *sock, char *input);
t_sock_data			*c_connect(char *hostname, char *port);
int					c_disconnect(t_sock_data *sock);
int					c_reconnect(t_sock_data *sock, char *hostname, char *port);

char				*readn(int fd);

char				*strjoinfree(char *s1, char *s2);

char				*get_root(void);
char				*get_dir(void);
char				*basename(char *str);

void				pexit(char *str, int outno);
int					perr(char *str);

#endif
