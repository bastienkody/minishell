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


typedef struct s_token
{
	char	*text;
	t_type	type;
}	t_token;

typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item; // token
}	t_btree;


void	err_msg(t_token *token, char *err)
{
	ft_fprintf(2, "minishell: %s: %s\n", token->text, err);
}

int	open_here_doc(t_token *token, char *lim)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		
}

int	open_in(t_token *token)
{
	if (acces(token->text, F_OK))
		return (err_msg(token, ERR_NSFD), -1);
	if (acces(token->text, R_OK))
		return (err_msg(token, ERR_PERMDEN), -1);
	return (open(token->text, O_RDONLY));
}

int	open_out(t_type *type_prev, t_token *token)
{
	if (!acces(token->text, F_OK) && acces(token->text, W_OK))
		return (err_msg(token, ERR_PERMDEN), -1);
	if (!ft_strcmp(type_prev, great))
		return (open(token->text, O_TRUNC | O_WRONLY | O_CREAT, 00644));
	else if (!ft_strcmp(type_prev, dgreat))
		return (open(token->text, O_APPEND | O_WRONLY | O_CREAT, 00644));
}

