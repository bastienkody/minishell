/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_info_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:52:29 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 18:02:43 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_ntree	*get_command_name_node(const t_ntree *simple_command_node)
{
	const t_llist	*current;

	current = simple_command_node->children;
	while (current != NULL)
	{
		if (get_token(current->content)->type == CMD_NAME)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

static size_t	get_args_length(t_ntree *simple_command_node)
{
	const t_llist	*current = simple_command_node->children;
	size_t			i;

	i = 0;
	while (current != NULL)
	{
		if (get_token(current->content)->type == CMD_ARG)
			i++;
		current = current->next;
	}
	return (i);
}

static char	*get_arg_name(t_ntree *cmd_arg_node)
{
	t_token *const	token = ((t_ntree *)cmd_arg_node->children->content)->data;

	return (token->data);
}

char	*get_command_name(t_ntree *simple_command_node)
{
	t_ntree *const	cmd_name_node = get_command_name_node(simple_command_node);
	t_ntree *const	word_node = cmd_name_node->children->content;
	char *const		cmd_name = get_token(word_node)->data;

	return (ft_strdup(cmd_name));
}

char	**get_command_args(t_ntree *simple_command_node, char *command_name)
{
	char	**args;
	t_ntree	*cmd_name_node;
	t_llist	*current;
	int		i;

	args = malloc((get_args_length(simple_command_node) + 2) * sizeof(char *));
	if (args == NULL)
		return (NULL);
	cmd_name_node = get_command_name_node(simple_command_node);
	i = 0;
	args[i] = ft_strdup(command_name);
	if (args[i] == NULL)
		return (NULL);
	i++;
	current = simple_command_node->children;
	while (current != NULL)
	{
		if (get_token(current->content)->type == CMD_ARG)
		{
			args[i] = ft_strdup(get_arg_name(current->content));
			if (args[i] == NULL)
				return (free_char_matrix(args), NULL);
			i++;
		}
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}
