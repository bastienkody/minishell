/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:48:07 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/16 20:56:24 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_node_cmd_name(t_ntree *node)
{
	const t_type	type = get_token(node)->type;

	return (type == CMD_NAME);
}

t_cmd	*cmd_new(t_ntree *simple_command_node, int index, char **envp)
{
	t_cmd *const	cmd = malloc(sizeof(t_cmd));
	t_llist *const	children = simple_command_node->children;

	if (cmd == NULL)
		return (NULL);
	*cmd = (t_cmd){};
	cmd->fd_in = get_fd_in(simple_command_node);
	cmd->fd_out = get_fd_out(simple_command_node);
	cmd->index = index;
	if (llstfind_if(children, (t_predicate)is_node_cmd_name))
	{
		cmd->name = get_command_name(simple_command_node);
		if (cmd->name == NULL)
			return (free(cmd), NULL);
		cmd->fullname = get_full_cmd_name(cmd->name, envp);
		if (cmd->fullname == NULL)
			return (free(cmd->name), free(cmd), NULL);
		cmd->args = get_command_args(simple_command_node, cmd->name);
		if (cmd->name == NULL)
			return (free(cmd->name), free(cmd->fullname), free(cmd), NULL);
	}
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
	t_cmd	*next;

	if (*cmds == NULL)
		return ;
	current = *cmds;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->fullname);
		free_char_matrix(current->args);
		free(current);
		current = next;
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
