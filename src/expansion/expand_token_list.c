/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:51:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/03 15:07:11 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expand_token_list(t_llist **token_list_ptr, char **envp)
{
	t_llist	*token_list;
	int		return_code;

	token_list = *token_list_ptr;
	return_code = manage_dollar_expansion(token_list, envp);
	if (return_code == EAMBREDIR)
		return (ft_fprintf(2, ERR_AMB_REDIR), EAMBREDIR);
	if (return_code == 0)
		return (ft_fprintf(2, ERR_ALLOC), ALLOC_FAIL);
	return_code = manage_quote_remove(token_list);
	if (return_code == ALLOC_FAIL)
		return (ft_fprintf(2, ERR_ALLOC), ALLOC_FAIL);
	return_code = wildcard_list(&token_list, envp);
	if (return_code == EAMBREDIR)
		return (ft_fprintf(2, ERR_AMB_REDIR), EAMBREDIR);
	if (return_code == ALLOC_FAIL)
		return (ft_fprintf(2, ERR_ALLOC), ALLOC_FAIL);
	*token_list_ptr = token_list;
	return (0);
}
