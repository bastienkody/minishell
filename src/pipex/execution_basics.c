/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_basics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:46:45 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/11 14:44:35 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <dirent.h>

// /* returns null on malloc err ; ["", NULL] if no path or no envp	*/
char	**get_path(char **envp)
{
	char	**no_path;

	while (envp && *envp)
	{
		if (!ft_strncmp("PATH=", *envp, 5))
			return (ft_split(get_value(*envp), ':'));
		envp++;
	}
	no_path = malloc(2 * sizeof(char *));
	if (!no_path)
		return (NULL);
	no_path[0] = ft_strdup("");
	no_path[1] = NULL;
	return (no_path);
}

char	*get_full_cmd_name(char *cmd_name, char **envp)
{
	int		i;
	char	**path;
	char	*tmp_name;

	if (ft_strchr(cmd_name, '/'))
		return (ft_strdup(cmd_name));
	path = get_path(envp);
	if (!path)
		return (NULL);
	if (!ft_strlen(path[0]) && !path[1])
		return (free(path[0]), free(path), ft_strdup(""));
	i = -1;
	while (path[++i])
	{
		tmp_name = ft_strjoin(path[i], "/");
		tmp_name = strjoin(tmp_name, cmd_name);
		if (!tmp_name)
			return (free_char_matrix(path), NULL);
		if (!access(tmp_name, F_OK))
			return (free_char_matrix(path), tmp_name);
		free(tmp_name);
	}
	return (free_char_matrix(path), ft_strdup(""));
}

int	analyze_status(t_info *info)
{
	int		status;
	t_cmd	*last_cmd;

	last_cmd = cmd_last(info->cmd_start);
	status = info->exit_code;
	if (last_cmd->exist)
		return (ft_fprintf(1, "RET 127\n"), 127);
	if (last_cmd->is_exec)
		return (126);
	if (last_cmd->fd_in == REDIR_PB || last_cmd->fd_out == REDIR_PB)
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (status);
}

void	wait_cmds(t_info *info)
{
	int		child_status;
	pid_t	ret;

	ret = 0;
	while (ret != -1)
	{
		ret = waitpid(-1, &child_status, 0);
		if (ret == info->last_pid)
			info->exit_code = child_status;
	}
}

void	check_cmd_access(t_info *info, t_minishell *minishell)
{
	void	*tmp_dir_ptr;

	if (!*(info->cmds->name))
		(minishell->status = 0, free_and_exit(minishell));
	if (access(info->cmds->fullname, F_OK))
	{
		if (!ft_strchr(info->cmds->name, '/'))
			err_msg(info->cmds->name, ERR_CNF);
		else
			err_msg(info->cmds->name, ERR_NSFD);
		(minishell->status = 127, free_and_exit(minishell));
	}
	tmp_dir_ptr = opendir(info->cmds->fullname);
	if (tmp_dir_ptr)
	{
		closedir(tmp_dir_ptr);
		//free(tmp_dir_ptr);
		err_msg(info->cmds->name, ERR_IAD);
		(minishell->status = 126, free_and_exit(minishell));
	}
	if (access(info->cmds->fullname, X_OK))
	{
		err_msg(info->cmds->name, ERR_PERMDEN);
		(minishell->status = 126, free_and_exit(minishell));
	}
}

int	execute(char **cmd_args, t_info *info, t_minishell *minishell)
{
	if (info->cmds->fd_in < 0 || info->cmds->fd_out < 0)
		(minishell->status = 1, free_and_exit(minishell));
	if (!cmd_args)
		(minishell->status = 0, free_and_exit(minishell)); // cas redirection sans commande name ni args
	if (is_a_builtin(cmd_args, info->cmds->name))
		(minishell->status = exec_builtin(info->cmds->name, cmd_args, minishell), free_and_exit(minishell));
	check_cmd_access(info, minishell);
	execve(cmd_args[0], cmd_args, minishell->envp);
	perror(ERR_EXECVE);
	if (info->cmds->fd_in > NO_REDIR)
		close(info->cmds->fd_in);
	if (info->cmds->fd_out > NO_REDIR)
		close(info->cmds->fd_in);
	(minishell->status = 1, free_and_exit(minishell));
	return (1);
}
