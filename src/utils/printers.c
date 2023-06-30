/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:10:02 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/22 14:47:09 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static const char	*g_type[]
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
	"error"
};

void	print_item(void *item)
{
	if (!item)
		return ;
	ft_putstr_fd((char *)item ,1);
	ft_putstr_fd("\n", 1);
}

void	print_llist(t_llist *start)
{
	if (!start)
		return ;
	ft_fprintf(1, "------------------\n");
	llstiter(start, &print_item);
	ft_fprintf(1, "------------------\n");
}

void	print_token(t_token *token)
{
	ft_fprintf(1, "text : %s, type : %s\n", token->text, g_type[token->type]);
}

void	print_env(char **envp)
{
	while (envp && *envp)
	{
		ft_fprintf(1, "%s\n", *envp);
		envp++;
	}
}
