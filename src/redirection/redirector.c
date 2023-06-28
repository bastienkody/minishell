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

void	err_msg(char *str, char *err)
{
	ft_fprintf(2, "minishell: %s: %s\n", str, err);
}

int	open_in(t_token *token, char **envp)
{
	int	fd;

	token->text = expand_dollar_redir_file(token->text, envp);
	if (!token->text)
		return (-1);
	if (access(token->text, F_OK))
		return (err_msg(token->text, ERR_NSFD), BAD_FD);
	if (access(token->text, R_OK))
		return (err_msg(token->text, ERR_PERMDEN), BAD_FD);
	fd = open(token->text, O_RDONLY);
	if (fd < 0)
		perror("open infile");
	return (fd);
}

int	open_out(t_type *type_prev, t_token *token, char **envp)
{
	int	fd;

	token->text = expand_dollar_redir_file(token->text, envp);
	if (!token->text)
		return (-1);
	if (!access(token->text, F_OK) && access(token->text, W_OK))
		return (err_msg(token->text, ERR_PERMDEN), BAD_FD);
	fd = -1;
	if (*type_prev == great)
		fd = open(token->text, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	else if (*type_prev == dgreat)
		fd = open(token->text, O_APPEND | O_WRONLY | O_CREAT, 00644);
	if (fd < 0)
		perror("open outfile");
	return (fd);
}

void	manage_redir(t_btree *root, char **envp)
{
	if (!root || envp)
		return ;
	return ;
}
