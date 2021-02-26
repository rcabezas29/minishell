/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:13:12 by rcabezas          #+#    #+#             */
/*   Updated: 2021/02/26 13:56:16 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
    pid_t   pid;
    char **comando;

    comando = NULL;
    printf("minishell- ");
    ft_memset(*comando, '\0', 64);
    comando = parse_comand();
    while(ft_strcmp(*comando, "exit"))
    {
        pid = fork();
        if (pid == 0)
        {
            execlp(*comando, *comando, NULL);
            printf("comando no válido\n");
            exit(0);
        }
        else
        {
            if (pid > 0)
            {
                waitpid(pid, 0, 0);
                printf("minishell- ");
                ft_memset(*comando, '\0', 64);
                comando = parse_comand();
            }
            else
                perror("ERROR FORK\n");
        }
    }
    exit(0);
}
