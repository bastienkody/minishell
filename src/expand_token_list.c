/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:51:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/29 15:37:17 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_llist	*expand_token_list(t_llist *token_list, char **envp, int last_status)
{
	if (!manage_dollar_expansion(token_list, envp, last_status))
		return (NULL);
	ft_fprintf(1, "after dollar expansion\n");
	llstiter(token_list, (t_unary_fun)print_token);
	if (!manage_quote_remove(token_list))
		return (NULL);
	ft_fprintf(1, "after quote remove\n");
	llstiter(token_list, (t_unary_fun)print_token);
	if (!llstreplace(&token_list, wildcard_list(token_list, envp), (t_del_fun)free_token))
		return (NULL);
	ft_fprintf(1, "after wildcard\n");
	llstiter(token_list, (t_unary_fun)print_token);
	return (token_list);
}