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

	(void)envp;
	while (ast)
	{
		//ast->data = expand_dollar((char *)ast->data, envp);
		ft_fprintf(1, "%i\n", (int)ast->type);
		ft_fprintf(1, "%s\n", (char *)ast->data);
	//	if (!ast->data)
	//		return (MALLOC_FAIL_REDIR);
		if (ast->children)
			ast = ast->children->content;
		else
		{
			ft_fprintf(1, "ast->children vaut null\n");
		 	ast = NULL;
		}
	}
	return (1);
}
