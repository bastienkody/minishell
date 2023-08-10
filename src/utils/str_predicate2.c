/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_predicate2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:54:39 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/10 13:55:23 by aguyon           ###   ########.fr       */
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

	if (len > 2 && str[0] == '(' && str[len - 1] == ')')
		return (check_parenthesis(str));
	return (0);
}

// int	is_str_word(const char *str)
// {
// 	int		is_inside_quote;
// 	char	quote;

// 	is_inside_quote = 0;
// 	quote = '\0';
// 	while (*str != '\0')
// 	{
// 		if (ft_strchr("\'\"", *str))
// 		{
// 			if (is_inside_quote && *str == quote)
// 			{
// 				is_inside_quote = 0;
// 				quote = '\0';
// 			}
// 			else if (!is_inside_quote)
// 			{
// 				is_inside_quote = 1;
// 				quote = *str;
// 			}
// 		}
// 		str++;
// 	}
// 	return (!is_inside_quote);
// }

int	is_str_word(const char *str)
{
	(void)str;
	return (1);
}