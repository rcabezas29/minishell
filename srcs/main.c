/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:13:12 by rcabezas          #+#    #+#             */
/*   Updated: 2021/03/01 13:49:35 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
    pid_t   pid;
    char **comando;

    comando = NULL;
    ft_putstr_fd("minishell- ", 1);
    comando = parse_comand();
    while(ft_strcmp(*comando, "exit"))
    {
        pid = fork();
        if (pid == 0)
        {
            if (check_args(comando))
                execute(comando);
            else
            {
                ft_putstr_fd("comando no válido\n", 1);
                exit(0);
            }
        }
        else
        {
            if (pid > 0)
            {
                waitpid(pid, 0, 0);
                ft_putstr_fd("minishell- ", 1);
                comando = NULL;
                comando = parse_comand();
            }
            else
                perror("ERROR FORK\n");
        }
    }
    exit(0);
}
