/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:40:26 by aguyon            #+#    #+#             */
/*   Updated: 2023/08/25 14:43:10 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_tmp_file(char *pathname, t_minishell *minishell)
{
	t_llist	*new_node;
	int		fd;

	fd = open(pathname, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	if (fd < 0)
		return (perror("open here_doc in w"), BAD_FD);
	new_node = llstnew(pathname);
	if (new_node == NULL)
		return (close(fd), free(pathname), ALLOC_FAIL);
	llstadd_back(&minishell->here_doc_files, new_node);
	return (fd);
}
