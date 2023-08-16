/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:23:23 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/16 11:42:49 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_llist	*tokenization(const char *line)
{
	t_llist	*token_list;

	token_list = lsttok(line);
	if (token_list == NULL)
		return (NULL);
	llstremove_if(&token_list, (bool (*)(void *))is_str_blank, free);
	if (!llstreplace(&token_list, type_token(token_list), free))
		return (llstclear(&token_list, free), NULL);
	return (token_list);
}
