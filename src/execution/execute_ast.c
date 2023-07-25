/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:58:45 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/25 18:32:23 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

typedef int (*t_execute_ast_fun)(t_ntree *ast);

int	execute_pipeline(t_ntree *ast);
int	execute_complete_command(t_ntree *ast);
int	execute_compound_command(t_ntree *ast);
int	execute_logical_expression(t_ntree *ast);

t_execute_ast_fun get_execute_function(t_ntree *ast)
{
	const t_type type = get_token(ast)->type;

	if (type == PIPELINE)
		return (execute_pipeline);
	else if (type == COMPLETE_COMMAND)
		return (execute_complete_command);
	else if (type == COMPOUND_COMMAND)
		return (execute_compound_command);
	else if (type == LOGICAL_EXPRESSION)
		return (execute_logical_expression);
	else
		return (NULL);
}

int	execute_ast(t_ntree *ast)
{
	const t_execute_ast_fun	execute_function = get_execute_function(ast);

	return (execute_function(ast));
}

int	execute_complete_command(t_ntree *ast)
{
	t_ntree *const			child = ast->children->content;
	const t_execute_ast_fun	execute_function = get_execute_function(child);

	return (execute_function(child));
}

int	execute_pipeline(t_ntree *ast)
{
	t_info *const	pipex_info = get_token(ast)->data;

	return (pipex(pipex_info));
}

int	execute_compound_command(t_ntree *ast)
{
	t_ntree *const			child = ast->children->content;
	const t_execute_ast_fun	execute_function = get_execute_function(child);

	return (execute_function(child));
}

int	execute_logical_expression(t_ntree *ast)
{
	t_ntree *const	lhs = ast->children->content;
	t_ntree *const	rhs = ast->children->next->content;
	const t_execute_ast_fun	lhs_execute_function = get_execute_function(lhs);
	const t_execute_ast_fun	rhs_execute_function = get_execute_function(rhs);
	int	lhs_return_status;

	lhs_return_status = lhs_execute_function(lhs);
	if (lhs_return_status == 0 && ft_strcmp(get_token(lhs->data)->data, "&&"))
		return (rhs_execute_function(rhs));
	else if (lhs_return_status != 0 && ft_strcmp(get_token(lhs->data)->data, "||"))
		return (rhs_execute_function(rhs));
	return (lhs_return_status);
}
