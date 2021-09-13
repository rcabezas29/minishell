/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:24:55 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/13 14:47:13 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	echo(char *command)
{
	printf("%s\n", command);
}

void	cd(char *command)
{
	printf("%s\n", command);
}

void	pwd(char *command)
{
	printf("%s\n", command);
}

void	export(char *command)
{
	printf("%s\n", command);
}

void	unset(char *command)
{
	printf("%s\n", command);
}

void	env_function(char *command)
{
	printf("%s\n", command);
}