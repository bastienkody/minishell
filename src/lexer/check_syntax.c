/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:28:44 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/10 12:48:49 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_syntax(t_llist *token_list)
{
	t_llist	*current;

	current = token_list;
	while (current != NULL)
	{
		if (is_token_pipe(current->content)
			|| is_token_logical_operator(current->content))
		{
			if (current->prev == NULL || current->next == NULL)
				return (-1);
			if (is_token_operator(current->prev->content)
				|| is_token_operator(current->next->content))
				return (-1);
		}
		else if (is_token_redirection(current->content)
			|| is_token_here_doc(current->content))
		{
			if (current->next && current->next->content == NULL)
				return (-1);
			if (current->next == NULL || !is_token_word(current->next->content))
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
