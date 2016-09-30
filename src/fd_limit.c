/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_limit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 11:01:15 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/09/30 11:12:46 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"

int		fd_limit(void)
{
	static int		saved = -42;
	struct rlimit	limits;

	if (saved != -42)
		return (saved);
	if (getrlimit(RLIMIT_NOFILE, &limits) < 0)
		pexit("getrlimits failed.\n", 1);
	saved = limits.rlim_cur;
	return (saved);
}
