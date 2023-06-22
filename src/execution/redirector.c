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

	if (acces(token->text, F_OK))
		return (err_msg(token, ERR_NSFD), -1);
	if (acces(token->text, R_OK))
		return (err_msg(token, ERR_PERMDEN), -1);
	fd = open(token->text, O_RDONLY);
	if (!fd)
		perror("open infile");
	return (fd);
}

int	open_out(t_type *type_prev, t_token *token)
{
	int	fd;

	if (!acces(token->text, F_OK) && acces(token->text, W_OK))
		return (err_msg(token, ERR_PERMDEN), -1);
	if (!ft_strcmp(type_prev, great))
		fd = open(token->text, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	else if (!ft_strcmp(type_prev, dgreat))
		fd = open(token->text, O_APPEND | O_WRONLY | O_CREAT, 00644);
	if (!fd)
		perror("open outfile");
	return (fd);
}

void	manage_redir(t_btree *root)
{

}
