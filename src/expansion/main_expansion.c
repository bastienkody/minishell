/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:04:37 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/22 16:04:39 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expand_dollar_quotes_on_ast(t_ast *ast, char **envp)
{
	while (ast->children)
	{
		if (ast->type == 8)
		{
			ast->data = expand_dollar((char *)ast->data, envp);
			if (!ast->data)
				return (MALLOC_FAIL_REDIR);
		}
		ast->children = ast->children->next;
	}
	return (1);
}