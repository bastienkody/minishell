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

/*	stops at lim or eof	*/
void	launch_here_doc(int fd, char *lim)
{
	char	*line;
	char	*data;

	data = ft_strdup("");
	if (!data)
		return ;
	while (1)
	{
		ft_fprintf(1, "%s", HD_PROMPT);
		line = get_next_line(0); // attention gnl modifie
		if (!line)
			return (free(data));
		if (*line == 0 || ft_strcmp(line, lim))
			break ;
		data = strj(data, line);
		if (!data)
			return ;
	}
	write(fd, data, ft_strlen(data));
	return (free(line), free(data));
}

int	open_here_doc(t_token *token, char *lim)
{
	int			fd;
	static int	nb = 0;
	char		*pathname;

	pathname = ft_strjoin3(HD_START, ft_itoa(nb), HD_END);
	if (!pathname)
		return (NULL);
	nb++;
	fd = open(pathname, O_WRONLY | O_CREAT, 00644);
	if (fd < 0)
		perror("open here_doc in wr");
	launch_here_doc(fd, lim);
	close(fd);
	fd = open(pathname, O_RDONLY, 00644);
	if (fd < 0)
		perror("open here_doc in rd");
	return (fd);
}

void	remove_heredoc_tmpfile(char *pathname)
{
	if (unlink(pathname))
		perror("unlink heredoc");
}
