/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_basics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:46:45 by bguillau          #+#    #+#             */
/*   Updated: 2023/08/05 10:11:52 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		return (WTERMSIG(status));
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

int	execute(char *cmd_name, char **cmd_args, t_info *info)
{
	if (info->cmds->fd_in < 0 || info->cmds->fd_out < 0)
		exit(1);
	if (!cmd_args)
		return (0); // cas redirection sans commande name ni args
	if (is_a_builtin(cmd_args, cmd_name))
	{
		ft_fprintf(1, "%s is_a builtin\n", cmd_name);
		return (exec_builtin(cmd_name, cmd_args, &(info->envp)));
	}
	else
		ft_fprintf(1, "%s is not a builtin\n", cmd_name);
	if (access(info->cmds->fullname, F_OK))
	{
		if (!ft_strchr(cmd_name, '/'))
			err_msg(cmd_name, ERR_CNF);
		else
			err_msg(cmd_name, ERR_NSFD);
		exit(127);
	}
	if (access(info->cmds->fullname, X_OK))
	{
		err_msg(cmd_name, ERR_PERMDEN);
		exit(126);
	}
	execve(cmd_args[0], cmd_args, info->envp);
	perror(ERR_EXECVE);
	if (info->cmds->fd_in > NO_REDIR)
		close(info->cmds->fd_in);
	if (info->cmds->fd_out > NO_REDIR)
		close(info->cmds->fd_in);
	exit(EXIT_FAILURE);
	return (1);
}
