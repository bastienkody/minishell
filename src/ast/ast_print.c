/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:01:21 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/25 16:12:28 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static void print_pipeline(t_info *pipex_info)
// {

// }

static void	print_data(t_token *token)
{
	ft_fprintf(1, "%s", type_to_string(token->type));
	if (token->data == NULL)
		return ;
	// if (token->type == OPERATOR)
	// 	ft_fprintf(1, ": %s", type_to_string(token->type));
	if (token->type == REDIRECTION)
		ft_fprintf(1, ": %d", (intptr_t)token->data);
	else if (token->type == PIPELINE)
		ft_fprintf(1, ": %p", token->data);
	else
		ft_fprintf(1, ": %s", (char *)token->data);
}

void	ast_print(t_ntree *ast)
{
	ntree_print(ast, (t_unary_fun)print_data);
}

void	print_leaf(t_ntree *leaf)
{
	t_token *const	token = get_token(leaf);

	ft_fprintf(1, "type : %s, ", type_to_string(token->type));
	ft_fprintf(1, "data : %s\n", (char *)token->data);
}

