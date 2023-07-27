/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:35:20 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 20:10:13 by aguyon           ###   ########.fr       */
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

static int add_filename(t_llist **matching_files, char *filename)
{
	char	*new_filename;
	t_llist	*new_node;

	new_filename = ft_strdup(filename);
	if (new_filename == NULL)
		return (0);
	new_node = ast_new(word, new_filename, NULL);
	if (new_node == NULL)
		return (free(new_filename), 0);
	llstadd_back(matching_files, new_node);
	return (1);
}

t_llist	*get_matching_files(char *pattern, char **envp)
{
	char *const current_dir = get_pwd(envp);
	DIR	*dir;
	t_llist	*matching_files;
	struct dirent* info;

	dir = opendir(current_dir);
	if (dir == NULL)
		return (NULL);
	matching_files = NULL;
	info = readdir(dir);
	while (info != NULL)
	{
		if (match(pattern, info->d_name))
			if (!add_filename(&matching_files, info->d_name))
				return (llstclear(&matching_files, (t_del)ast_free));
		info = readdir(dir);
	}
	if (closedir(dir) == -1)
		return (llstclear(&matching_files, (t_del)ast_free), NULL);
	return (matching_files);
}

void replace(t_llist **leaf_list, t_llist *to_replace, t_llist *replace)
{
	t_llist *const prev = to_replace->prev;
	t_llist *const next = to_replace->next;

	llstremoveone(leaf_list, to_replace, (t_del_fun)ast_free);
	llstadd_after(&prev, replace);
	replace->next = next;
}

int manage_wildcard(t_llist *leaf_list, char **envp)
{
	t_llist	*current;
	t_llist	*get_matching_files;
	t_token	*prev_token;
	t_token	*token;

	current = leaf_list;
	prev_token = NULL;
	while (current != NULL)
	{
		if (current->prev != NULL)
			prev_token = get_token(current->prev->content);
		token = get_token(current->content);
		if (token->type == word && ft_strcmp(prev_token->data, "<<") != 0)
			replace(&leaf_list, current, NULL);
		current = current->next;
	}
	return (1);
}