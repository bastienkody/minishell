/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:26:00 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/31 16:28:55 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_type	get_redirection_type(t_ntree *redirection_node)
{
	t_ntree *const	operator_node = redirection_node->children->content;
	t_ntree *const	type_node = operator_node->children->content;

	return (get_token(type_node)->type);
}

char	*get_redirection_filename(t_ntree *redirection_node)
{
	t_ntree *const	filename_node = redirection_node->children->next->content;
	t_ntree *const	word_node = filename_node->children->content;

	return (get_token(word_node)->data);
}

char	*get_here_end(t_ntree *here_doc_node)
{
	t_ntree *const	here_end_node = here_doc_node->children->content;
	t_ntree *const	word_node = here_end_node->children->content;

	return (get_token(word_node)->data);
}

int	open_redirections(t_type type, const char *filename)
{
	int	fd;

	if (type == great)
		fd = open(filename, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	else if (type == dgreat)
		fd = open(filename, O_APPEND | O_WRONLY | O_CREAT, 00644);
	else if (type == less)
		fd = open(filename, O_RDONLY);
	else
		return (-1);
	if (fd < 0)
		perror("open outfile");
	return (fd);
}
