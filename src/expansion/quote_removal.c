/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:36:22 by bguillau          #+#    #+#             */
/*   Updated: 2023/06/28 10:36:26 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*	no quote rm on here_doc data	*/
char	*rm_peer_s_quotes(char *str)
{
	if (!str)
		return (NULL);
	
	return (str);
}
