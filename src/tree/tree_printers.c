/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_printers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:24:22 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/19 18:50:01 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static const char	*g_type_str[]
	= {
	"or",
	"and",
	"pipe",
	"great",
	"less",
	"dgreat",
	"dless",
	"compound",
	"word",
	"error",
	"COMPLETE_COMMAND",
	"COMPOUND_COMMAND",
	"LOGICAL_EXPRESSION",
	"PIPELINE",
	"SIMPLE_COMMAND",
	"CMD_NAME",
	"CMD_ARG",
	"CMD_PREFIX",
	"CMD_SUFFIX",
	"REDIRECTION",
	"OPERATOR",
	"FILENAME"
};

char	*type_to_string(t_type type)
{
	return ((char *)g_type_str[type]);
}

static void	print_data(t_ast *ast)
{
	if (ast->type == REDIRECTION || ast->type == OPERATOR)
		ft_fprintf(1, ": %d", (intptr_t)ast->data);
	else
		ft_fprintf(1, ": %s", (char *)ast->data);
}

static void	print_node(t_ast *ast, int depth)
{
	if (depth != 0)
		ft_fprintf(1, "+--- ");
	ft_fprintf(1, "%s", type_to_string(ast->type));
	if (ast->data != NULL)
		print_data(ast);
	ft_fprintf(1, "\n");
}

static void	print_tree_rec(t_ast *ast, bool flag[256], size_t depth, int islast)
{
	const t_llist	*current_child = ast->children;
	size_t			i;

	if (ast == NULL)
		return ;
	i = 0;
	while (++i < depth)
	{
		if (flag[i] == true)
			ft_fprintf(1, "|     ");
		else
			ft_fprintf(1, "     ");
	}
	if (depth == 0 || !islast)
		print_node(ast, depth);
	else
		(print_node(ast, depth), flag[depth] = false);
	while (current_child != NULL)
	{
		print_tree_rec(current_child->content,
			flag, depth + 1, current_child->next == NULL);
		current_child = current_child->next;
	}
	flag[depth] = true;
}

void	print_tree(t_ast *ast)
{
	bool	flag[256];

	ft_memset(flag, 1, 256);
	print_tree_rec(ast, flag, 0, 0);
}
