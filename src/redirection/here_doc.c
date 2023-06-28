/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:19:21 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/22 14:19:24 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*	quotes in heredoc data : aucun effet!
	tout depend de LIM : si quote pas d'expansion
	trouver une commande qui lit sur stdin du glob pour check no * expansion
*/

/*	stops at lim or eof (modified gnl) - returns 0 if malloc failed	*/
int	launch_here_doc(int fd, char *lim, char **envp)
{
	char	*line;
	char	*data;

	data = ft_strdup("");
	if (!data)
		return (0);
	while (1)
	{
		ft_fprintf(1, "%s", HD_PROMPT);
		line = get_next_line(0);
		if (!line)
			return (free(data), 0);
		if (*line == 0 || !ft_strncmp(line, lim, ft_strlen(lim)))
			break ;
		data = strj(data, line);
		if (!data)
			return (0);
	}
	if (!is_str_quote_enclosed(lim))
		data = expand_dollar_here_doc(data, envp);
	if (!data)
		return (0);
	write(fd, data, ft_strlen(data));
	return (free(line), free(data), 1);
}

/*	create+open tmpfile in w, launch_hd to it. close n reopen in r	*/
int	open_here_doc(char *lim, char **envp)
{
	int			fd;
	static int	nb = 0;
	char		*pathname;

	pathname = ft_strjoin3(HD_START, ft_itoa(nb), HD_END);
	if (!pathname)
		return (MALLOC_FAIL_REDIR);
	nb++;
	fd = open(pathname, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	if (fd < 0)
		return (free(pathname), perror("open here_doc in w"), BAD_FD);
	if (!launch_here_doc(fd, lim, envp))
		return (free(pathname), close (fd), MALLOC_FAIL_REDIR);
	close(fd);
	fd = open(pathname, O_RDONLY, 00644);
	if (fd < 0)
		return (free(pathname), perror("open here_doc in rd"), BAD_FD);
	return (free(pathname), fd);
}

void	remove_heredoc_tmpfile(char *pathname)
{
	if (unlink(pathname))
		perror("unlink heredoc");
}
