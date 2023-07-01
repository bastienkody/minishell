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

/* does not work : ptr pb on gnwne */
/*	to apply on all WORD, but not on here_doc data	*/
char	*rm_peer_quotes(char *str)
{
	char	*tmp;
	char	*ret;
	char	*close_quote;

	tmp = str;
	ret = ft_strdup("");
	if (!str || !ret)
		return (free(tmp), free(ret), NULL);
	while (*tmp)
	{
		if (*tmp == '\'' || *tmp == '\"')
		{
			if (*tmp == '\'')
				close_quote = strfind(tmp + 1, '\'');
			else
				close_quote = strfind(tmp + 1, '\"');
			tmp = get_next_word_not_expanded(&ret, tmp + 1, close_quote) ;
		}
		else
			tmp = get_next_word_not_expanded(&ret, tmp, strfind_if(tmp + 1, \
				is_c_quote));
		if (!tmp || !ret)
			return (free(str), NULL);
	}
	return (free(str), ret);
}
