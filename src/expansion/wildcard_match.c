/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:47:50 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/24 12:48:18 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	matchstar(const char *pattern, const char *text);

int	match(const char *pattern, const char *text)
{
	if (pattern[0] == '\0')
		return (*text == '\0');
	if (pattern[0] == '*')
		return (matchstar(pattern + 1, text));
	if (*text != '\0' && pattern[0] == *text)
		return (match(pattern + 1, text + 1));
	return (0);
}

static int	matchstar(const char *pattern, const char *text)
{
	if (match(pattern, text))
		return (1);
	while (*text != '\0' && text++)
		if (match(pattern, text))
			return (1);
	return (0);
}
