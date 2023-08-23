/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:19:21 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/23 14:39:15 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_dollar_here_doc(char *data, char **envp, int status)
{
	char	*res;

	res = expand_dollar_here_doc(data, envp, status);
	free(data);
	if (res == NULL)
		return (NULL);
	return (res);
}

int	launch_here_doc(int fd, const char *lim, t_minishell *minishell)
{
	char	*line;
	char	*data;

	(void)minishell;
	data = ft_strdup("");
	if (!data)
		return (ERRALLOC);
	while (1)
	{
		line = readline(HD_PROMPT);
		if (g_last_signum == SIGINT)
			return (free(data), ERRSIGINT);
		if (!line)
			break ;
		if (!ft_strcmp(line, lim))
			break ;
		data = strj(data, strj(line, ft_strdup("\n")));
		if (!data)
			return (ERRALLOC);
	}
	data = expand_dollar(data, minishell->envp, minishell->status);
	// if (!is_str_quote_enclosed(lim))
	// 	data = expand_dollar_here_doc(data, minishell->envp, minishell->status);
	if (!data)
		return (ERRALLOC);
	write(fd, data, ft_strlen(data));
	return (free(line), free(data), SUCCESS);
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
		return (close(fd), free(pathname), ALLOC_FAIL);
	llstadd_back(&minishell->here_doc_files, new_node);
	return (fd);
}

void	open_here_doc_child(const char *lim, int fd, t_minishell *minishell)
{
	set_here_doc_signals();
	minishell->status = launch_here_doc(fd, lim, minishell);
	close(fd);
	free_and_exit(minishell);
}

int	open_here_doc_parent(int fd, char *pathname)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	wait(&status);
	status = WEXITSTATUS(status);
	if (status != 0)
		return (status);
	close(fd);
	fd = open(pathname, O_RDONLY, 00644);
	if (fd < 0)
		return (perror("open here_doc in rd"), ERRFD);
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
		return (ERRALLOC);
	fd = create_tmp_file(pathname, minishell);
	if (fd < -1)
		return (fd);
	if (fork() == 0)
		open_here_doc_child(lim, fd, minishell);
	else
		fd = open_here_doc_parent(fd, pathname);
	return (fd);
}
