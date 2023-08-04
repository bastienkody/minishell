/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:16:57 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/01 17:22:04 by aguyon           ###   ########.fr       */
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

void	token_print(t_token *token)
{
	ft_fprintf(1, "text : %s, type : %s\n", token->data, g_type[token->type]);
}
