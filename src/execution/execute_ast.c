/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguyon <aguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:58:45 by aguyon            #+#    #+#             */
/*   Updated: 2023/07/25 17:35:03 by aguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_complete_command(t_ntree *ast, char **envp)
{
	/*
	executer pipeline
	ou
	executer compound
	ou
	executer logical_operator
	*/
}

int	execute_pipeline(t_ntree *ntree, char **envp)
{
	/*
	executer chaque commande
	retourner le code erreur de la derniere commande
	*/
}

int	execute_logical_operator(t_ntree *ast, char **envp)
{
	/*
	executer fils gauche et garder en memoire le code erreur
	si type du noeud == && et code erreur == 0 alors
		executer fils droit
	si type du noeud == || et code erreur != 0 alors
		executer fils droit
	*/
}

// int	execute_simple_command(t_ast *ast, char **envp)
// {
// 	/*
// 	transformer la liste chainee en commande
// 	executer la commande
// 	*/
// }