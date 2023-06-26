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

void	err_msg(t_token *token, char *err)
{
	ft_fprintf(2, "minishell: %s: %s\n", token->text, err);
}

int	open_in(t_token *token)
{
	int	fd;

	// expansion to do on token->text
	if (access(token->text, F_OK))
		return (err_msg(token, ERR_NSFD), BAD_FD);
	if (access(token->text, R_OK))
		return (err_msg(token, ERR_PERMDEN), BAD_FD);
	fd = open(token->text, O_RDONLY);
	if (!fd)
		perror("open infile");
	return (fd);
}

int	open_out(t_type *type_prev, t_token *token)
{
	int	fd;

	// expansion to do on token->text
	if (!access(token->text, F_OK) && access(token->text, W_OK))
		return (err_msg(token, ERR_PERMDEN), BAD_FD);
	if (*type_prev == great)
		fd = open(token->text, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	else if (*type_prev == dgreat)
		fd = open(token->text, O_APPEND | O_WRONLY | O_CREAT, 00644);
	if (!fd)
		perror("open outfile");
	return (fd);
}

void	manage_redir(t_btree *root, char **envp)
{
	if (!root || envp)
		return ;
	return ;
}
