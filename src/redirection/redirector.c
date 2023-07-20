/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:50:44 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/22 11:50:46 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_in(char *filename, char **envp)
{
	int	fd;

	if (!check_amb_redir(filename, envp))
		return (err_msg(filename, ERR_AMB_REDIR), BAD_FD);
	filename = expand_dollar(filename, envp);
	if (!filename)
		return (MALLOC_FAIL);
	if (access(filename, F_OK))
		return (err_msg(filename, ERR_NSFD), BAD_FD);
	if (access(filename, R_OK))
		return (err_msg(filename, ERR_PERMDEN), BAD_FD);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("open infile");
	return (free(filename), fd);
}

int	open_out(int type, char *filename, char **envp)
{
	int	fd;

	if (!check_amb_redir(filename, envp))
		return (err_msg(filename, ERR_AMB_REDIR), BAD_FD);
	filename = expand_dollar(filename, envp);
	if (!filename)
		return (MALLOC_FAIL);
	if (!access(filename, F_OK) && access(filename, W_OK))
		return (err_msg(filename, ERR_PERMDEN), BAD_FD);
	fd = BAD_FD;
	if (type == great)
		fd = open(filename, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	else if (type == dgreat)
		fd = open(filename, O_APPEND | O_WRONLY | O_CREAT, 00644);
	if (fd < 0)
		perror("open outfile");
	return (free(filename), fd);
}

void	manage_redir(t_btree *root, char **envp)
{
	if (!root || envp)
		return ;
	return ;
}
