/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 15:35:45 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/11/06 21:14:07 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_H
# define IRC_H

# include <stdlib.h>
# include <string.h>
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

# include <stdio.h>
# include <sys/select.h>

# define BUF_SIZE 4096

# define SERVER_ACTIVE ((fd_set*)server())
# define SERVER_READ ((fd_set*)server() + 1)
# define SERVER_WRITE ((fd_set*)server() + 2)

# define CLIENT_ACTIVE ((fd_set*)client())
# define CLIENT_READ ((fd_set*)client() + 1)
# define CLIENT_WRITE ((fd_set*)client() + 2)

typedef struct sockaddr_in	t_sockaddr_in;

typedef struct				s_sock_data
{
	int						id;
	t_sockaddr_in			addr;
}							t_sock_data;

typedef struct				s_clientbuf
{
	int						set;
	int						sock;
	char					*nick;
	char					*read;
	char					*write;
	int						channel;
}							t_clientbuf;

typedef struct				s_channel
{
	char					*name;
	struct s_channel		*next;
}							t_channel;

typedef struct				s_server
{
	fd_set					active;
	fd_set					read;
	fd_set					write;
	int						listen;
	int						max;
	t_clientbuf				*buf;
	t_channel				*ch;
}							t_server;

typedef struct				s_client
{
	fd_set					active;
	fd_set					read;
	fd_set					write;
	int						fd;
	char					*cl_read;
	char					*cl_write;
	char					*sv_read;
	char					*sv_write;
}							t_client;

t_server					*server(void);
void						server_init(int sock);
void						server_set(int sock);
void						server_select(void);
void						server_accept(void);
void						server_cmd(t_clientbuf *client);

void						read_out(int sock, char *buf);

char						*write_msg(char *dest, t_clientbuf *client);
int							channel_get(char *name);
char						*channel_name(int id);
void						channels_write(t_clientbuf *client);

void						pexit(char *str, int outno);
int							perr(char *str);

void						*palloc(size_t size);

int							fd_limit(void);

char						*strjoinfree(char *s1, char *s2);
char						*strfresh(char *str);

char						*linedup(char *str);
char						*linepop(char *str);

t_client					*client(void);
void						client_init(int fd);
void						client_reset(int fd);
void						client_select(void);

void						client_prompt(void);
t_sock_data					*prompt_connect_only(void);
t_sock_data					*c_connect(char *hostname, char *port);
int							c_disconnect(t_sock_data *sock);
int							c_reconnect(t_sock_data *sock, char *hostname,
										char *port);

char						*get_root(void);
char						*get_dir(void);
char						*basename(char *str);

#endif
