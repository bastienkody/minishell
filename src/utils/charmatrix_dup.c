/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charmatrix_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:05:58 by bguillau          #+#    #+#             */
/*   Updated: 2023/07/18 18:06:07 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* strdup on src_matrix (not freed)	*/
char	**charmatrix_dup(char **src_matrix)
{
	int		len;
	int		i;
	char	**new_matrix;

	len = 0;
	i = -1;
	while (src_matrix && src_matrix[++i])
		len++;
	new_matrix = malloc((len + 1) * sizeof(char *));
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
	int		len;
	int		i;
	char	**new_matrix;

	len = 0;
	i = -1;
	while (src_matrix && src_matrix[++i])
		len++;
	new_matrix = malloc((len + 1 + 1) * sizeof(char *));
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
//NOT DONE YET
/*char	**charmatrix_del_one(char **src_matrix, char *key)
{
	int		len;
	int		i;
	char	**new_matrix;

	len = 0;
	i = -1;
	while (src_matrix && src_matrix[++i])
		len++;
	new_matrix = malloc((len - 1) * sizeof(char *));
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
	free_char_matrix(src_matrix);
	return (new_matrix);
}*/
