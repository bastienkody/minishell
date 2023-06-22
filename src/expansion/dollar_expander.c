/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:04:37 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/22 16:04:39 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_key(char *line)
{
	char	*end;

	end = strfind(line, '=');
	if (!end)
		return (NULL);
	*end = '\0';
	return (line);
}

static char	*get_value(char *line)
{
	return (strfind(line, '=') + 1);
}

static char	*expand_wd(char *word, char **envp)
{
	char	*tmp_var;

	while (envp && *envp)
	{
		if (!ft_strcmp(word, get_key(*envp)))
			return (get_value(*envp));
		envp++;
	}
	return ("");
}

/*	only dollar + quoted stuff are expanded + quotes arent removed
	do not handle : ${}	*/
char	*expand_here_doc(char *str, char **envp)
{
	int		i;
	char	*ret;
	char	*new_wd;
	char	*wd_end;

	i = -1;
	while (str[++i])
	{
		if (is_c_dollar(str[i]))
		{
			wd_end = strfind_if(str + i, &is_str_blank);
			new_wd = expand_wd(extract_wd(str+i, wd_end), envp);
			ret = ft_realloc(ret, sizeof(ft_strlen(ret) + ft_strlen(new_wd)));
			if (!ret)
				return (NULL);
			while (&str[i] != wd_end)
				i++;
		}
		else 

	}	
}
