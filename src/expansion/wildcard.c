/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:35:20 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 19:20:16 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	matchstar(char *regexp, char *text);

int	match(char *regexp, char *text)
{
	if (regexp[0] == '\0')
		return (*text == '\0');
	if (regexp[0] == '*')
		return(matchstar(regexp+1, text));
	if (*text != '\0' && regexp[0]==*text)
		return (match(regexp+1, text+1));
	return (0);
}

int	matchstar(char *regexp, char *text)
{
	if (match(regexp, text))
		return (1);
	while (*text != '\0' && text++)
		if (match(regexp, text))
			return (1);
	return (0);
}

char	*get_pwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PWD=", 4) == 0)
		{
			puts(envp[i] + 4);
			return (envp[i] + 4);
		}
		i++;
	}
	return (NULL);
}

t_llist	*get_matching_files(DIR *dir, char *regexp)
{
	t_llist	*matching_files;
	char	*new_filename;
	t_llist	*new_leaf;
	struct dirent* info;

	matching_files = NULL;
	info = readdir(dir);
	while (info != NULL)
	{
		if (match(regexp, info->d_name))
		{
			new_filename = ft_strdup(info->d_name);
			if (new_filename == NULL)
				return (NULL);
			new_leaf = ast_new(word, new_filename, NULL);
			if (new_leaf == NULL)
				return (free(new_filename), NULL);
			llstadd_back(&matching_files, new_leaf);
		}
		info = readdir(dir);
	}
	return (matching_files);
}

int manage_wildcard(char *pattern, char **envp)
{
	char *const	current_dir = get_pwd(envp);
	DIR *const	dir = opendir(current_dir);
	t_llist	*matching_files;

	if (dir == NULL)
		return (0);
	matching_files = NULL;
	if (closedir(dir) == -1)
		return (free(matching_files), 0);
	return (1);
}

// t_llist	*replace(t_ntree *leaf)
// {

// }

int no_name(t_ntree *ast, char **envp)
{
	t_llist	*current;
	t_token	*token;

	if (ast == NULL)
		return (1);
	token = get_token(ast);
	if (token->type == CMD_NAME || token->type == CMD_ARG || token->type == FILENAME)
	{
		//replace
	}
	else
	{
		current = ast->children;
		while (current != NULL)
		{
			if (!no_name(current->content, envp))
				return (0);
			current = current->next;
		}
	}
	return (1);
}