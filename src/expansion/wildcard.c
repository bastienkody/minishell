/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:35:20 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/28 16:22:26 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	matchstar(char *regexp, char *text);

int	match(char *regexp, char *text)
{
	if (regexp[0] == '\0')
		return (*text == '\0');
	if (regexp[0] == '*')
		return (matchstar(regexp + 1, text));
	if (*text != '\0' && regexp[0] == *text)
		return (match(regexp + 1, text + 1));
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
			return (envp[i] + 4);
		i++;
	}
	return (NULL);
}

static int	add_filename(t_llist **wildcard_list, char *filename)
{
	char	*new_filename;
	t_ntree	*new_leaf;
	t_llist	*new_node;

	new_filename = ft_strdup(filename);
	if (new_filename == NULL)
		return (0);
	new_leaf = ast_new(word, new_filename, NULL);
	if (new_leaf == NULL)
		return (free(new_filename), 0);
	new_node = llstnew(new_leaf);
	if (new_node == NULL)
		return (ast_free(new_leaf), 0);
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
				return (llstclear(&wildcard_list, (t_del_fun)ast_free), NULL);
		}
		info = readdir(dir);
	}
	if (wildcard_list == NULL && !add_filename(&wildcard_list, pattern))
		return (NULL);
	if (closedir(dir) == -1)
		return (llstclear(&wildcard_list, (t_del_fun)ast_free), NULL);
	return (wildcard_list);
}

int	is_prev_here_operator(t_llist *leaf_list)
{
	t_token	*prev_token;

	if (leaf_list->prev == NULL)
		return (0);
	prev_token = get_token(leaf_list->prev->content);
	return (ft_strcmp(prev_token->data, "<<") == 0);
}

t_llist	*wildcard_list(t_llist *leaf_list, char **envp)
{
	t_llist	*current;
	t_token	*token;
	t_llist	*new_nodes;
	t_llist	*new_leaf_list;

	new_leaf_list = NULL;
	current = leaf_list;
	while (current != NULL)
	{
		token = get_token(current->content);
		if (token->type == word && !is_prev_here_operator(current))
		{
			new_nodes = get_wildcard_nodes(token->data, envp);
			if (new_nodes == NULL)
				return (llstclear(&new_leaf_list, (t_del_fun)ast_free), NULL);
			llstadd_back(&new_leaf_list, new_nodes);
		}
		current = current->next;
	}
	return (new_leaf_list);
}

int	main(int argc, char ** argv, char **envp)
{
	t_llist	*leaf_list = NULL;
	t_llist	*new_leaf_list;

	((void)argc, (void)argv);

	llstadd_back(&leaf_list, llstnew(ast_new(word, ft_strdup("g****.*"), NULL)));
	llstadd_back(&leaf_list, llstnew(ast_new(word, ft_strdup("outfile"), NULL)));
	llstadd_back(&leaf_list, llstnew(ast_new(word, ft_strdup("l*"), NULL)));
	llstiter(leaf_list, (t_unary_fun)ast_print), puts("");
	new_leaf_list = wildcard_list(leaf_list, envp);
	if (new_leaf_list == NULL)
		return (llstclear(&leaf_list, (t_del_fun)ast_free), 1);
	llstiter(new_leaf_list, (t_unary_fun)ast_print), puts("");
	llstclear(&leaf_list, (t_del_fun)ast_free);
	return (0);
}