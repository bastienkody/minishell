/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:08:19 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/28 15:45:28 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_str_dgreat(const char *str)
{
	return (ft_strcmp(str, ">>") == 0);
}

int	is_str_dless(const char *str)
{
	return (ft_strcmp(str, "<<") == 0);
}

static int	check_parenthesis(const char *text)
{
	int	n;

	n = 0;
	while (*text && n >= 0)
	{
		if (*text == '(')
			n++;
		else if (*text == ')')
			n--;
		text++;
	}
	return (n == 0);
}

int	is_str_compound(const char *str)
{
	const size_t	len = ft_strlen(str);

	return (len > 2 && str[0] == '(' && str[len - 1] == ')'
		&& check_parenthesis(str));
}

int	is_str_word(const char *str)
{
	int		is_inside_quote;
	char	quote;

	is_inside_quote = 0;
	quote = '\0';
	while (*str != '\0')
	{
		if (ft_strchr("\'\"", *str))
		{
			if (is_inside_quote && *str == quote)
			{
				is_inside_quote = 0;
				quote = '\0';
			}
			else if (!is_inside_quote)
			{
				is_inside_quote = 1;
				quote = *str;
			}
		}
		str++;
	}
	return (!is_inside_quote);
}
