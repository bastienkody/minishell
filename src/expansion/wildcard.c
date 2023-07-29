/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:35:20 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/29 16:42:55 by aguyon           ###   ########.fr       */
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
				return (llstclear(&wildcard_list, (t_del_fun)free_token), NULL);
		}
		info = readdir(dir);
	}
	if (wildcard_list == NULL && !add_filename(&wildcard_list, pattern))
		return (NULL);
	if (closedir(dir) == -1)
		return (llstclear(&wildcard_list, (t_del_fun)free_token), NULL);
	return (wildcard_list);
}

int	is_prev_here_operator(t_llist *token_list)
{
	t_token	*prev_token;

	if (token_list->prev == NULL)
		return (0);
	prev_token = token_list->prev->content;
	return (ft_strcmp(prev_token->data, "<<") == 0);
}

t_llist	*node_dup(t_llist *node)
{
	const t_token	*original_token = node->content;
	t_llist			*new_node;
	t_token			*new_token;
	char			*new_str;

	new_str = ft_strdup(original_token->data);
	if (new_str == NULL)
		return (NULL);
	new_token = token_new(original_token->type, new_str);
	if (new_token == NULL)
		return (free(new_str), NULL);
	new_node = llstnew(new_token);
	if (new_node == NULL)
		return (free_token(new_token), NULL);
	return (new_node);

}

int	is_str_redirection(const char *str)
{
	return (is_str_great(str) == 0
		||  is_str_dgreat(str) == 0
		|| is_str_less(str) == 0);
}

int	check_ambigous_redirect(t_llist *new_nodes , t_llist *prev_node)
{
	const t_token	*prev_token;

	if (prev_node == NULL)
		return (0);
	prev_token = prev_node->content;
	return (llstsize(new_nodes) >= 2 && is_str_redirection(prev_token->data));
}

t_llist	*wildcard_list(t_llist *token_list, char **envp)
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
		if (token->type == word && !is_prev_here_operator(current))
		{
			new_nodes = get_wildcard_nodes(token->data, envp);
			if (new_nodes == NULL)
				return (llstclear(&new_token_list, (t_del_fun)free_token), NULL);
			if (check_ambigous_redirect(new_nodes, current->prev))
				return (llstclear(&new_token_list, (t_del_fun)free_token), puts("Error wildcard\n"), NULL);
		}
		else
		{
			new_nodes = node_dup(current);
			if (new_nodes == NULL)
				return (llstclear(&new_token_list, (t_del_fun)free_token), NULL);
		}
		llstadd_back(&new_token_list, new_nodes);
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
// 	if (!llstreplace(&leaf_list, wildcard_list(leaf_list, envp), (t_del_fun)free_token))
// 		return (llstclear(&leaf_list, (t_del_fun)free_token), 1);
// 	llstiter(leaf_list, (t_unary_fun)print_token), puts("");
// 	llstclear(&leaf_list, (t_del_fun)free_token);
// 	return (0);
// }