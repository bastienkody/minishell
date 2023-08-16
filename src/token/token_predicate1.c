/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_predicate1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:58:42 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/16 17:28:05 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_token_ambiguous_word(t_token *token)
{
	return (token->type == ambigous_word);
}

bool	is_token_error(t_token *token)
{
	return (token->type == error);
}
