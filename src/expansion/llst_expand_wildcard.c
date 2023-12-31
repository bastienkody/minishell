/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_expand_wildcard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:35:20 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/25 12:15:38 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	add_filename(t_llist **wildcard_list, char *filename)
{
	char	*new_filename;
	t_token	*new_token;
	t_llist	*new_node;

	new_filename = ft_strdup(filename);
	if (new_filename == NULL)
		return (ALLOC_FAIL);
	new_token = token_new(word, new_filename);
	if (new_token == NULL)
		return (free(new_filename), ALLOC_FAIL);
	new_node = llstnew(new_token);
	if (new_node == NULL)
		return (token_free(new_token), ALLOC_FAIL);
	llstadd_back(wildcard_list, new_node);
	return (0);
}

t_llist	*wildcard_nodes_new(char *pattern)
{
	DIR *const		dir = opendir(".");
	struct dirent	*info;
	t_llist			*wildcard_list;

	if (dir == NULL)
		return (NULL);
	wildcard_list = NULL;
	info = readdir(dir);
	while (info != NULL)
	{
		if ((info->d_name[0] != '.') && match(pattern, info->d_name))
			if (add_filename(&wildcard_list, info->d_name) != 0)
				return (llstclear(&wildcard_list, token_free), NULL);
		info = readdir(dir);
	}
	if (closedir(dir) == -1)
		return (llstclear(&wildcard_list, token_free), NULL);
	return (wildcard_list);
}

int	get_nb_matched_files(const char *pattern)
{
	DIR *const		dir = opendir(".");
	int				nb_matched_files;
	struct dirent	*info;

	if (dir == NULL)
		return (0);
	nb_matched_files = 0;
	info = readdir(dir);
	while (info != NULL)
	{
		if ((info->d_name[0] != '.') && match(pattern, info->d_name))
			nb_matched_files++;
		info = readdir(dir);
	}
	if (closedir(dir) == -1)
		return (-1);
	return (nb_matched_files);
}

t_llist	*node_expand_wildcard(t_llist *node)
{
	int		nb_matched_files;
	t_token	*token;
	t_llist	*new_nodes;

	token = node->content;
	if (token->type == word && !is_prev_here_operator(node))
	{
		nb_matched_files = get_nb_matched_files(token->data);
		if (nb_matched_files == -1)
			new_nodes = NULL;
		else if (nb_matched_files == 0)
			new_nodes = node_dup(node);
		else if (!check_ambigous_redirect(node, nb_matched_files))
			new_nodes = ambigous_node_new(node);
		else
			new_nodes = wildcard_nodes_new(token->data);
	}
	else
		new_nodes = node_dup(node);
	return (new_nodes);
}

t_llist	*llst_expand_wildcard(t_llist *token_list)
{
	t_llist	*current;
	t_llist	*new_nodes;
	t_llist	*new_token_list;

	new_token_list = NULL;
	current = token_list;
	while (current != NULL)
	{
		new_nodes = node_expand_wildcard(current);
		if (new_nodes == NULL)
			return (llstclear(&new_token_list, token_free), NULL);
		llstadd_back(&new_token_list, new_nodes);
		current = current->next;
	}
	return (new_token_list);
}
