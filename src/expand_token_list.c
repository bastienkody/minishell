/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:51:59 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/31 11:34:46 by aguyon           ###   ########.fr       */
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
	// ft_fprintf(1, "after dollar expansion\n");
	// llstiter(token_list, (t_unary_fun)print_token);
	return_code = manage_quote_remove(token_list);
	if (return_code != 1)
		return (return_code);
	// ft_fprintf(1, "after quote remove\n");
	// llstiter(token_list, (t_unary_fun)print_token);
	if (!llstreplace(&token_list, wildcard_list(token_list, envp), (t_del_fun)free_token))
		return (0);
	// ft_fprintf(1, "after wildcard\n");
	// llstiter(token_list, (t_unary_fun)print_token);
	*token_list_ptr = token_list;
	return (1);
}

// t_llist	*expand_token_list(t_llist *token_list, char **envp, int last_status)
// {
// 	if (!manage_dollar_expansion(token_list, envp, last_status))
// 		return (NULL);
// 	ft_fprintf(1, "after dollar expansion\n");
// 	llstiter(token_list, (t_unary_fun)print_token);
// 	if (!manage_quote_remove(token_list))
// 		return (NULL);
// 	ft_fprintf(1, "after quote remove\n");
// 	llstiter(token_list, (t_unary_fun)print_token);
// 	if (!llstreplace(&token_list, wildcard_list(token_list, envp), (t_del_fun)free_token))
// 		return (NULL);
// 	ft_fprintf(1, "after wildcard\n");
// 	llstiter(token_list, (t_unary_fun)print_token);
// 	return (token_list);
// }