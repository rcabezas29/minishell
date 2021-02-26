/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:50:16 by rcabezas          #+#    #+#             */
/*   Updated: 2021/02/26 13:53:51 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **parse_comand()
{
    char *line;
    char **args;
    
    ft_printf("minishell- ");
    line = read_line();
    args = ft_split(line, ' ');
    return (args);
}

char *read_line(void)
{
    char *line;
    
    line = NULL;
    get_next_line(1, &line);
    return (line);
}