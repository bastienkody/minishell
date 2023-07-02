/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_printers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:24:22 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/21 13:24:24 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static const char *g_type_str[] = {"or", "and", "pipe", "great", "less", "dgreat", "dless", "compound", "word", "error", "COMPLETE_COMMAND", "LOGICAL_EXPRESSION", "PIPELINE", "SIMPLE_COMMAND", "CMD_NAME", "CMD_ARG", "CMD_PREFIX", "CMD_SUFFIX", "REDIRECTION", "OPERATOR", "FILENAME"};

const char *type_to_string(t_type type)
{
	return (g_type_str[type]);
}

void	print_ast_full(t_ast *ast)
{
	if (ast == NULL)
		return ;
	ft_fprintf(1, "%s\n", type_to_string(ast->type));
	if (ast->type > 0 && ast->type < 9)
		ft_fprintf(1, "%s\n", (char *)ast->data);
	llstiter(ast->children, (void (*)(void *))print_ast_full);
}

void	print_ast_text(t_ast *ast)
{
	if (ast == NULL)
		return ();
	if (ast->type > 0 && ast->type < 9)
		ft_fprintf(1, "%s\n", (char *)ast->data);
	llstiter(ast->children, (void (*)(void *))print_ast_text);
}