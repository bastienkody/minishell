/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:19:21 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/16 17:12:51 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	launch_here_doc(int fd, const char *lim, t_minishell *minishell)
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
		data = expand_dollar_here_doc(data, minishell->envp, minishell->status);
	if (!data)
		return (FALSE);
	write(fd, data, ft_strlen(data));
	return (free(line), free(data), TRUE);
}

int	create_tmp_file(char *pathname, t_minishell *minishell)
{
	t_llist	*new_node;
	int		fd;

	fd = open(pathname, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	if (fd < 0)
		return (perror("open here_doc in w"), BAD_FD);
	new_node = llstnew(pathname);
	if (new_node == NULL)
		return (free(pathname), ALLOC_FAIL);
	llstadd_back(&minishell->here_doc_files, new_node);
	return (fd);
}

void	open_here_doc_child(const char *lim, int fd, t_minishell *minishell)
{
	set_here_doc_signals();
	if (!launch_here_doc(fd, lim, minishell))
	{
		if (g_last_signum == SIGINT)
			minishell->status = SIGINT;
		else
			minishell->status = 1;
	}
	(close(fd), free_and_exit(minishell));
}

int	open_here_doc_parent(int fd, char *pathname)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	wait(&status);
	if (WIFEXITED(status))
	{
		// ft_fprintf(2, "%d\n", WEXITSTATUS(status));
		return (-3);
	}
	close(fd);
	fd = open(pathname, O_RDONLY, 00644);
	if (fd < 0)
		return (perror("open here_doc in rd"), BAD_FD);
	return (fd);
}

/*	create+open tmpfile in w, launch_hd to it. close n reopen in r	*/
int	open_here_doc(const char *lim, t_minishell *minishell)
{
	static int	nb = 0;
	char *pathname;
	int fd;

	pathname = ft_strjoin3(HD_START, ft_itoa(nb++), HD_END);
	if (pathname == NULL)
		return (ALLOC_FAIL);
	fd = create_tmp_file(pathname, minishell);
	if (fd < -1)
		return (fd);
	if (fork() == 0)
		open_here_doc_child(lim, fd, minishell);
	else
		fd = open_here_doc_parent(fd, pathname);
	ft_fprintf(2, "%d\n", fd);
	return (fd);
}
