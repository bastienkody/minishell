/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:35:20 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/31 16:03:43 by aguyon           ###   ########.fr       */
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
		return (0);
	new_token = token_new(word, new_filename);
	if (new_token == NULL)
		return (free(new_filename), 0);
	new_node = llstnew(new_token);
	if (new_node == NULL)
		return (free_token(new_token), 0);
	llstadd_back(wildcard_list, new_node);
	return (1);
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
		if (match(pattern, info->d_name))
		{
			if (!add_filename(&wildcard_list, info->d_name))
				return (llstclear(&wildcard_list, free_token), NULL);
		}
		info = readdir(dir);
	}
	if (wildcard_list == NULL && !add_filename(&wildcard_list, pattern))
		return (NULL);
	if (closedir(dir) == -1)
		return (llstclear(&wildcard_list, free_token), NULL);
	return (wildcard_list);
}

int	check_ambigous_redirect(t_llist *new_nodes, t_llist *prev_node)
{
	const t_token	*prev_token;

	if (prev_node == NULL)
		return (0);
	prev_token = prev_node->content;
	return (llstsize(new_nodes) >= 2 && is_str_redirection(prev_token->data));
}

int	wildcard_list(t_llist **token_list_ptr, char **envp)
{
	t_llist	*current;
	t_token	*token;
	t_llist	*new_nodes;
	t_llist	*new_token_list;

	new_token_list = NULL;
	current = *token_list_ptr;
	while (current != NULL)
	{
		token = current->content;
		if (token->type == word && !is_prev_here_operator(current))
			new_nodes = get_wildcard_nodes(token->data, envp);
		else
			new_nodes = node_dup(current);
		if (new_nodes == NULL)
			return (llstclear(&new_token_list, free_token), 0);
		if (check_ambigous_redirect(new_nodes, current->prev))
			return (llstclear(&new_token_list, free_token), EAMBREDIR);
		llstadd_back(&new_token_list, new_nodes);
		current = current->next;
	}
	llstreplace(token_list_ptr, new_token_list, free_token);
	return (1);
}

// int	main(int argc, char ** argv, char **envp)
// {
// 	t_llist	*leaf_list = NULL;

// 	((void)argc, (void)argv);

// 	llstadd_back(&leaf_list, llstnew(token_new(word, ft_strdup("g****.*"))));
// 	llstadd_back(&leaf_list, llstnew(token_new(word, ft_strdup("outfile"))));
// 	llstadd_back(&leaf_list, llstnew(token_new(word, ft_strdup("l*"))));
// 	llstiter(leaf_list, (t_unary_fun)print_token), puts("");
// 	if (!llstreplace(&leaf_list, wildcard_list(leaf_list, envp), free_token))
// 		return (llstclear(&leaf_list, (t_del_fun)free_token), 1);
// 	llstiter(leaf_list, (t_unary_fun)print_token), puts("");
// 	llstclear(&leaf_list, (t_del_fun)free_token);
// 	return (0);
// }