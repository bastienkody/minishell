/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_apply.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:45:10 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/19 17:45:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ast_apply(t_ast *ast, t_funptr f)
{
	t_llist *current;

	f(ast);
	current = ast->children;
	while (current != NULL)
	{
		ast_apply(current->content, f);
		current = current->next;
	}
}