/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:48:48 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/18 18:10:17 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	free(ast->data);
	llstclear(&(ast->children), (void (*)(void *))free_ast);
	free(ast);
}
