/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:51:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/31 14:51:49 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	expand_token_list(t_llist **token_list_ptr, char **envp, int last_status)
{
	t_llist	*token_list;
	int		return_code;

	token_list = *token_list_ptr;
	return_code = manage_dollar_expansion(token_list, envp, last_status);
	if (return_code != 1)
		return (return_code);
	return_code = manage_quote_remove(token_list);
	if (return_code != 1)
		return (return_code);
	return_code = wildcard_list(&token_list, envp);
	if (return_code != 1)
		return (return_code);
	*token_list_ptr = token_list;
	return (1);
}
