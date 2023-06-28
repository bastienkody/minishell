/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:36:22 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/28 10:36:26 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*	to apply on all WORD, but not on here_doc data	*/
char	*rm_peer_quotes(char *str)
{
	char	*open_quote;
	char	*close_quote;
	char	*ret;
	
	ret = ft_strdup("");
	if (!str || !ret)
		return (free(str), free(ret), NULL);
	while (*str)
	{
		if (is_c_quote(*str))
		{
			open_quote = str;
			if (is_c_quote(*str) == 1)
				close_quote = strfind(str + 1, '\'');
			else
				close_quote = strfind(str + 1, '\"');
			str = get_next_word_not_expanded(&ret, str + 1, close_quote) + 1;
		}
		else
			str = get_next_word_not_expanded(&ret, str, strfind_if(str + 1, is_c_quote));
		if (!str || !ret)
			return (NULL);
	}
	return (free(str), ret);
}
