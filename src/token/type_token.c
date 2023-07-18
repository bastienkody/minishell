/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:42:20 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/18 13:48:19 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int (*const	g_type_predicate[])(const char *str)
	= {
	is_str_or,
	is_str_and,
	is_str_pipe,
	is_str_great,
	is_str_less,
	is_str_dgreat,
	is_str_dless,
	is_str_compound,
	is_str_word,
	NULL,
};

static void	free_token(t_token *token)
{
	free(token->text);
}

static t_type	get_type(const char *text)
{
	t_type	type;

	type = 0;
	while (g_type_predicate[type])
	{
		if (g_type_predicate[type](text))
			break ;
		type++;
	}
	return (type);
}

static t_token	*new_token(char *text)
{
	const t_type	type = get_type(text);
	t_token *const	new = malloc(sizeof(t_token));

	if (new == NULL)
		return (NULL);
	*new = (t_token){text, type};
	return (new);
}

t_llist	*type_token(t_llist	*token_list)
{
	return (llstmap(token_list, (void *(*)(void *))new_token,
		(void (*)(void *))free_token));
}
