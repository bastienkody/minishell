/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:05:23 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/25 17:05:27 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ntree *get_command_name_node(const t_ntree *simple_command_node)
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

char	*get_command_name(t_ntree *simple_command_node)
{
	t_ntree *const	cmd_name_node = get_command_name_node(simple_command_node);
	char *const		cmd_name = get_token(cmd_name_node->children->content)->data;

	return (ft_strdup(cmd_name));
}

size_t	get_args_length(t_ntree *simple_command_node)
{
	const t_llist *current = simple_command_node->children;
	size_t	i;

	i = 0;
	while (current != NULL)
	{
		if (get_token(current->content)->type == CMD_ARG)
			i++;
		current = current->next;
	}
	return (i);
}

void	free_char_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

char *get_arg_name(t_ntree *cmd_arg_node)
{
	t_token	*const token = ((t_ntree *)cmd_arg_node->children->content)->data;

	return (token->data);
}

char	**get_command_args(t_ntree *simple_command_node, char *command_name)
{
	char	**args;
	t_ntree	*cmd_name_node;
	t_llist	*current;
	int		i;

	args = malloc((get_args_length(simple_command_node) + 1) * sizeof(char *));
	if (args == NULL)
		return (NULL);
	cmd_name_node = get_command_name_node(simple_command_node);
	i = 0;
	args[i++] = command_name;
	current = cmd_name_node->children;
	while (current != NULL)
	{
		if (get_token(current->content)->type == CMD_ARG)
		{
			args[i] = ft_strdup(get_arg_name(((t_ntree *)current)->children->content));
			if (args[i] == NULL)
				return (free_char_matrix(args), NULL);
			i++;
		}
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

int	get_fd_in(t_ntree *simple_command_node)
{
	t_llist	*current;
	t_type	redirection_type;

	current = llstlast(simple_command_node->children);
	while (current != NULL)
	{
		if (get_token(current->content)->type == REDIRECTION)
		{
			redirection_type = get_redirection_type(current->content);
			if (redirection_type == less || redirection_type == dless)
				return ((intptr_t)(get_token(current->content)->data));
		}
		current = current->prev;
	}
	return (0);
}

int	get_fd_out(t_ntree *simple_command_node)
{
	t_llist	*current;
	t_type	redirection_type;

	current = llstlast(simple_command_node->children);
	while (current != NULL)
	{
		if (get_token(current->content)->type == REDIRECTION)
		{
			redirection_type = get_redirection_type(current->content);
			if (redirection_type == great || redirection_type == dgreat)
				return ((intptr_t)(get_token(current->content)->data));
		}
		current = current->prev;
	}
	return (0);
}

t_cmd	*cmd_new(t_ntree *simple_command_node, int index, char **envp)
{
	t_cmd	*cmd = malloc(sizeof(t_cmd));

	cmd->fd_in = get_fd_in(simple_command_node);
	cmd->fd_out = get_fd_out(simple_command_node);
	cmd->index = index;
	cmd->name = get_command_name(simple_command_node);
	cmd->fullname = get_full_cmd_name(cmd->name, envp);
	cmd->args = get_command_args(simple_command_node, cmd->fullname);
	cmd->exist = 0;
	cmd->is_exec = 0;
	cmd->next = NULL;

	return (cmd);
}

t_cmd	*cmd_last(t_cmd *cmds)
{
	if (cmds == NULL || cmds->next == NULL)
		return (cmds);
	return (cmd_last(cmds->next));
}

void	cmd_clear(t_cmd **cmds)
{
	t_cmd	*current;

	if (cmds == NULL)
		return ;
	current = *cmds;
	while (current != NULL)
	{
		free(current->fullname);
		free_char_matrix(current->args);
		current = current->next;
	}
	*cmds = NULL;
}

void	cmd_add_back(t_cmd **cmds, t_cmd *new_cmd)
{
	if (*cmds == NULL)
		*cmds = new_cmd;
	else
		cmd_last(*cmds)->next = new_cmd;
}

t_info	*get_pipex_info(t_ntree *pipeline_node, char **envp)
{
	t_info			*pipex_info = malloc(sizeof(t_info));
	const size_t	nb_cmd = llstsize(pipeline_node->children);
	t_llist			*current;
	t_cmd			*new_cmd;
	size_t			i;

	if (pipex_info == NULL)
		return (NULL);
	pipex_info->envp = &envp;
	pipex_info->exit_code = 0;
	pipex_info->last_pid = 0;
	pipex_info->cmds = NULL;
	current = pipeline_node->children;
	i = 0;
	while (i < nb_cmd)
	{
		new_cmd = cmd_new(current->content, i, envp);
		if (new_cmd == NULL)
			return (cmd_clear(&(pipex_info->cmds)), free(pipex_info), NULL);
		cmd_add_back(&(pipex_info->cmds), new_cmd);
		current = current->next;
		i++;
	}
	return (pipex_info);
}