/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:19:21 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/16 11:34:01 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	launch_here_doc(int fd, const char *lim, char **envp, int status)
{
	char	*line;
	char	*data;

	data = ft_strdup("");
	if (!data)
		return (FALSE);
	while (1)
	{
		line = readline(HD_PROMPT);
		if (g_last_signum == SIGINT)
			return (free(data), FALSE);
		if (!line)
			break ;
		if (!ft_strcmp(line, lim))
			break ;
		data = strj(data, strj(line, ft_strdup("\n")));
		if (!data)
			return (FALSE);
	}
	if (!is_str_quote_enclosed(lim))
		data = expand_dollar_here_doc(data, envp, status);
	if (!data)
		return (FALSE);
	write(fd, data, ft_strlen(data));
	return (free(line), free(data), TRUE);
}

/*	create+open tmpfile in w, launch_hd to it. close n reopen in r	*/
int	open_here_doc(const char *lim, char **envp, int status, \
t_llist **here_doc_list_ptr)
{
	int			fd;
	static int	nb = 0;
	char		*pathname;
	t_llist		*new_node;
	int			sstatus;

	pathname = ft_strjoin3(HD_START, ft_itoa(nb++), HD_END);
	if (!pathname)
		return (ALLOC_FAIL);
	new_node = llstnew(pathname);
	if (new_node == NULL)
		return (free(pathname), ALLOC_FAIL);
	llstadd_back(here_doc_list_ptr, new_node);
	fd = open(pathname, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	if (fd < 0)
		return (perror("open here_doc in w"), BAD_FD);
	pid_t pid = fork();
	if (pid == 0)
	{
		set_here_doc_signals();
		if (!launch_here_doc(fd, lim, envp, status))
		{
			close(fd);
			exit(1);
		}
		close(fd);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &sstatus, 0);
		if (WIFSIGNALED(sstatus))
			return (-3);
		close(fd);
		fd = open(pathname, O_RDONLY, 00644);
		if (fd < 0)
			return (perror("open here_doc in rd"), BAD_FD);
	}
	return (fd);
}

void	remove_heredoc_tmpfile(char *pathname)
{
	if (access(pathname, X_OK) == 0 && unlink(pathname) != 0)
		perror("unlink heredoc");
}
