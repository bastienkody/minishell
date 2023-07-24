/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:23:23 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/19 14:42:23 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_llist	*lexer(const char *line)
{
	t_llist	*token_list;
	t_llist	*temp;

	token_list = lsttok(line);
	if (token_list == NULL)
		return (NULL);
	temp = new_llst_with_compound(token_list);
	llstclear(&token_list, free);
	if (temp == NULL)
		return (NULL);
	token_list = temp;
	llstremove_if(&token_list, (int (*)(void *))is_str_blank, free);
	temp = type_token(token_list);
	llstclear(&token_list, free);
	if (temp == NULL)
		return (NULL);
	token_list = temp;
	return (token_list);
}
