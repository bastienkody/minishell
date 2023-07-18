/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_printers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:24:22 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/17 17:46:38 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static const char *g_type_str[] = {"or", "and", "pipe", "great", "less", "dgreat", "dless", "compound", "word", "error", "COMPLETE_COMMAND", "COMPOUND_COMMAND" ,"LOGICAL_EXPRESSION", "PIPELINE", "SIMPLE_COMMAND", "CMD_NAME", "CMD_ARG", "CMD_PREFIX", "CMD_SUFFIX", "REDIRECTION", "OPERATOR", "FILENAME"};

const char *type_to_string(t_type type)
{
	return (g_type_str[type]);
}

void	print_ast_full(t_ast *ast)
{
	if (ast == NULL)
		return ;
	ft_fprintf(1, "type:%s(%i), ptr:%s\n", type_to_string(ast->type), ast->type, ast->data);
	if (ast->data != NULL)
		ft_fprintf(1, "%s\n", (char *)ast->data);
	llstiter(ast->children, (void (*)(void *))print_ast_full);
}

void	print_ast_text(t_ast *ast)
{
	if (ast == NULL)
		return ;
	ft_fprintf(1, "%p\n", ast);
	if (ast->type > 0 && ast->type < 9)
		ft_fprintf(1, "%s\n", (char *)ast->data);
	llstiter(ast->children, (void (*)(void *))print_ast_text);
}

static void	print_node(t_ast *ast, int depth)
{
	if (depth != 0)
		ft_fprintf(1, "+--- ");
	ft_fprintf(1, "%s", type_to_string(ast->type));
	if (ast->data != NULL)
		ft_fprintf(1, ": %s", ast->data);
	ft_fprintf(1, "\n");
}

void	print_tree(t_ast *ast, int flag[256], int depth, int islast)
{
	if (ast == NULL)
		return ;
	for (int i = 1; i < depth; ++i)
	{
		if (flag[i] == 1)
			ft_fprintf(1, "|     ");
		else
			ft_fprintf(1, "     ");
	}
	if (depth == 0)
		print_node(ast, depth);
	else if (islast)
	{
		print_node(ast, depth);
		flag[depth] = 0;
	}
	else
		print_node(ast, depth);
	while (ast->children != NULL)
	{
		print_tree(ast->children->content, flag, depth + 1, ast->children->next == NULL);
		ast->children = ast->children->next;
	}
	flag[depth] = 1;
}