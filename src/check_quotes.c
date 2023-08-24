/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:53:29 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 16:55:03 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	is_word_quotes_closed(const char *str)
{
	bool	is_inside_quote;
	char	quote;

	is_inside_quote = false;
	quote = '\0';
	while (*str != '\0')
	{
		if (ft_strchr("\'\"", *str))
		{
			if (is_inside_quote && *str == quote)
			{
				is_inside_quote = false;
				quote = '\0';
			}
			else if (!is_inside_quote)
			{
				is_inside_quote = true;
				quote = *str;
			}
		}
		str++;
	}
	return (!is_inside_quote);
}

static bool	is_token_good(t_token *token)
{
	if (token->type == word && !is_word_quotes_closed(token->data))
		return (false);
	return (true);
}

bool	check_quotes(t_llist *token_list)
{
	return (llstall_of(token_list, (void *)is_token_good));
}
