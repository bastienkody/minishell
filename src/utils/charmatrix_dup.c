/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charmatrix_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:05:58 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/21 19:19:00 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// quid des free_char_matrix(src_matrix) soit envp, en cas de malloc fail ? a ajouter

static char	**get_new_matrix_malloced(char **src_matrix, int offset)
{
	int		i;
	int		len;
	char	**new_matrix;

	len = 0;
	i = -1;
	while (src_matrix && src_matrix[++i])
		len += 1;
	new_matrix = malloc((len + 1 + offset) * sizeof(char *));
	return (new_matrix);
}

/* strdup on src_matrix (not freed)	*/
char	**charmatrix_dup(char **src_matrix)
{
	int		i;
	char	**new_matrix;

	new_matrix = get_new_matrix_malloced(src_matrix, 0);
	if (!new_matrix)
		return (NULL);
	i = -1;
	while (src_matrix && src_matrix[++i])
	{
		new_matrix[i] = ft_strdup(src_matrix[i]);
		if (!new_matrix[i])
			return (free_char_matrix(new_matrix), NULL);
	}
	new_matrix[i] = NULL;
	return (new_matrix);
}

/*	dup src_matrix + 1 entry at end, free the src_matrix	*/
char	**charmatrix_add_one(char **src_matrix, char *entry)
{
	int		i;
	char	**new_matrix;

	new_matrix = get_new_matrix_malloced(src_matrix, 1);
	if (!new_matrix)
		return (NULL);
	i = -1;
	while (src_matrix && src_matrix[++i])
	{
		new_matrix[i] = ft_strdup(src_matrix[i]);
		if (!new_matrix[i])
			return (free_char_matrix(new_matrix), NULL);
	}
	new_matrix[i++] = entry;
	new_matrix[i] = NULL;
	free_char_matrix(src_matrix);
	return (new_matrix);
}

/*	dup src_matrix - 1 entry (key specific), free the src_matrix	*/
char	**charmatrix_del_one(char **src_matrix, char *key)
{
	int		i;
	int		j;
	char	**new_matrix;
	char	*key_comp;

	key_comp = NULL;
	new_matrix = get_new_matrix_malloced(src_matrix, -1);
	if (!new_matrix)
		return (NULL);
	i = -1;
	j = -1;
	while (src_matrix && src_matrix[++i])
	{
		free(key_comp);
		key_comp = get_key_2(src_matrix[i]);
		if (!key_comp)
			return (NULL);
		if (!ft_strcmp(key, key_comp))
			continue ;
		new_matrix[++j] = ft_strdup(src_matrix[i]);
		if (!new_matrix[j])
			return (free_char_matrix(new_matrix), NULL);
	}
	new_matrix[++j] = NULL;
	return (free(key_comp), free_char_matrix(src_matrix), new_matrix);
}
