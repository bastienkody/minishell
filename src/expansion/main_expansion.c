/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:07:00 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/24 14:07:02 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expand_dollar_quotes_on_ast(t_ast *ast, char **envp)
{
	(void)envp;
	while (ast)
	{
		ft_fprintf(1, "%i\n", (int)ast->type);
		ft_fprintf(1, "%s\n", (char *)ast->data);
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
