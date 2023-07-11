#include "../../inc/minishell.h"

/* returns null on malloc err ; ["", NULL] if no path or no envp	*/
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
	char	**path;
	char	*tmp_name;

	if (ft_strchr(cmd_name, '/'))
		return (ft_strdup(cmd_name));
	path = get_path(envp);
	if (!path)
		return (NULL);
	if (!ft_strlen(path[0]) && !path[1])
		return (free(path[0]), free(path), ft_strdup(""));
	while (path)
	{
		tmp_name = ft_strjoin(*path, "/");
		tmp_name = strjoin(tmp_name, cmd_name); 
		if (!tmp_name)
	  		return (free_char_matrix(path), NULL);
		if (!access(tmp_name, F_OK))
			return (free_char_matrix(path), tmp_name);
		free(tmp_name);
		path++;
	}
	return (free_char_matrix(path), ft_strdup("")); 
}

int	execute(char *cmd_name, char **cmd_args, char **envp)
{
	char	*full_name;

	full_name = get_full_cmd_name(cmd_name, envp);
	if (!full_name)
		return (MALLOC_FAIL_REDIR);
	if (access(full_name, F_OK))
	{
		if (!ft_strchr(cmd_name, '/'))
			err_msg(cmd_name, ERR_CNF);
		else
			err_msg(cmd_name, ERR_NSFD);
		return (free(full_name), exit(EXIT_FAILURE), -1);
	}
	if (access(full_name, X_OK))
		return (err_msg(cmd_name, ERR_PERMDEN), free(full_name), exit(EXIT_FAILURE), -1);
	cmd_args[0] = full_name;
	execve(full_name, cmd_args, envp);
	perror("minishell: execve:");
	free(full_name);
	//close inf/outfile
	exit(EXIT_FAILURE);
}
