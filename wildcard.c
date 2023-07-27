/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:58:40 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/27 17:00:44 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "llist/llist.h"

int	matchstar(char *regexp, char *text);

int	match(char *regexp, char *text)
{
	if (regexp[0] == '\0')
		return (*text == '\0');
	if (regexp[0] == '*')
		return(matchstar(regexp+1, text));
	if (*text != '\0' && regexp[0]==*text)
		return (match(regexp+1, text+1));
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
		{
			puts(envp[i] + 4);
			return (envp[i] + 4);
		}
		i++;
	}
	return (NULL);
}

t_llist	*get_matching_files(DIR *dir, char *regexp)
{
	t_llist	*matching_files;
	t_llist	*new;
	struct dirent* info;

	matching_files = NULL;
	info = readdir(dir);
	while (info != NULL)
	{
		if (match(regexp, info->d_name))
		{
			new = llstnew(strdup(info->d_name));
			llstadd_back(&matching_files, new);
		}
		info = readdir(dir);
	}
	return (matching_files);
}

int main(int argc, char **argv, char **envp)
{
	char *const	current_dir = get_pwd(envp);
	DIR* dir;
	t_llist	*matching_files;

	if (argc != 2)
		exit(1);
	matching_files = NULL;
	dir = opendir(current_dir);
	if (dir == NULL)
		exit(1);
	matching_files = get_matching_files(dir, argv[1]);
	llstiter(matching_files, (t_unary_fun)puts);
	if (closedir(dir) == -1)
		exit(1);
	return (0);
}