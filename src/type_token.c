/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:42:20 by aguyon            #+#    #+#             */
/*   Updated: 2023/06/21 21:46:26 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static const char *g_token_text[] = {"||", "&&", "|", ">", "<", ">>", "<<", NULL};

static void	free_token(t_token *token)
{
	free(token->text);
}

static int check_quote(const char *text)
{
	const char quote = text[0];
	const size_t len = ft_strlen(text);

	return (len > 1 && text[len - 1] == quote);
}

static int check_parenthesis(const char *text)
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

static t_type	hash_text(const char *text)
{
	int	i;

	i = 0;
	while (g_token_text[i])
	{
		if (ft_strcmp(text, g_token_text[i]) == 0)
			break ;
		i++;
	}
	if (text[0] == '(' || text[0] == ')')
	{
		if (check_parenthesis(text))
			return (subshell);
		else
			return (error);
	}
	if ((text[0] == '\'' || text[0] == '\"') && !check_quote(text))
		return (error);
	return (i);
}

static t_token	*new_token(char *text)
{
	t_token	*new;
	const t_type hash = hash_text(text);

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	*new = (t_token){text, hash};
	return (new);
}

t_llist	*type_token(t_llist	*token_list)
{
	return (llstmap(token_list, (void *(*)(void *))new_token,(void(*)(void *))free_token));
}