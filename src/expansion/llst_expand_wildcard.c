/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_expand_wildcard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:35:20 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/08 18:59:33 by aguyon           ###   ########.fr       */
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

t_llist	*get_wildcard_nodes(char *pattern, char **envp)
{
	char *const		current_dir = get_pwd(envp);
	DIR				*dir;
	struct dirent	*info;
	t_llist			*wildcard_list;

	dir = opendir(current_dir);
	if (dir == NULL)
		return (NULL);
	wildcard_list = NULL;
	info = readdir(dir);
	while (info != NULL)
	{
		if ((info->d_name[0] != '.') && match(pattern, info->d_name))
		{
			if (add_filename(&wildcard_list, info->d_name) != 0)
				return (llstclear(&wildcard_list, token_free), NULL);
		}
		info = readdir(dir);
	}
	if (wildcard_list == NULL && add_filename(&wildcard_list, pattern) != 0)
		return (NULL);
	if (closedir(dir) == -1)
		return (llstclear(&wildcard_list, token_free), NULL);
	return (wildcard_list);
}

int	check_ambigous_redirect(t_llist *node, char *pattern, char **envp)
{
	char *const		current_dir = get_pwd(envp);
	DIR				*dir;
	struct dirent	*info;
	int				nb_word;
	t_token			*prev_token;

	dir = opendir(current_dir);
	if (dir == NULL)
		return (1);
	info = readdir(dir);
	nb_word = 0;
	while (info != NULL)
	{
		if (match(pattern, info->d_name))
			nb_word++;
		info = readdir(dir);
	}
	if (closedir(dir) == -1)
		return (1);
	if (node->prev == NULL)
		return (0);
	prev_token = node->prev->content;
	return (is_str_redirection(prev_token->data) && nb_word >= 2);

}

// int	check_ambigous_redirect(t_llist *new_nodes, t_llist *prev_node)
// {
// 	const t_token	*prev_token;

// 	if (prev_node == NULL)
// 		return (0);
// 	prev_token = prev_node->content;
// 	return (llstsize(new_nodes) >= 2 && is_str_redirection(prev_token->data));
// }

t_llist *get_ambigous_node(t_llist *node)
{
	t_llist	*new_node;
	t_token	*token;

	new_node = node_dup(node);
	if (new_node == NULL)
		return (NULL);
	token = new_node->content;
	token->type = ambigous_word;
	return (new_node);
}

t_llist *llst_expand_wildcard(t_llist *token_list, char **envp)
{
	t_llist	*current;
	t_token	*token;
	t_llist	*new_nodes;
	t_llist	*new_token_list;

	new_token_list = NULL;
	current = token_list;
	while (current != NULL)
	{
		token = current->content;
		if (token->type == word && check_ambigous_redirect(current, token->data, envp))
			new_nodes = get_ambigous_node(current);
		else if (token->type == word && !is_prev_here_operator(current))
			new_nodes = get_wildcard_nodes(token->data, envp);
		else
			new_nodes = node_dup(current);
		if (new_nodes == NULL)
			return (llstclear(&new_token_list, token_free), NULL);
		llstadd_back(&new_token_list, new_nodes);
		// if (check_ambigous_redirect(new_nodes, current->prev))
		// 	return (llstclear(&new_token_list, token_free), EAMBREDIR);
		current = current->next;
	}
	return (new_token_list);
}

// int	main(int argc, char ** argv, char **envp)
// {
// 	t_llist	*leaf_list = NULL;

// 	((void)argc, (void)argv);

// 	llstadd_back(&leaf_list, llstnew(token_new(word, ft_strdup("g****.*"))));
// 	llstadd_back(&leaf_list, llstnew(token_new(word, ft_strdup("outfile"))));
// 	llstadd_back(&leaf_list, llstnew(token_new(word, ft_strdup("l*"))));
// 	llstiter(leaf_list, (t_unary_fun)print_token), puts("");
// 	if (!llstreplace(&leaf_list, wildcard_list(leaf_list, envp), token_free)))
// 		return (llstclear(&leaf_list, (t_del_fun)token_free)), 1);
// 	llstiter(leaf_list, (t_unary_fun)print_token), puts("");
// 	llstclear(&leaf_list, (t_del_fun)token_free));
// 	return (0);
// }