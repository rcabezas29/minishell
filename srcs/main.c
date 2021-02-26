/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:13:12 by rcabezas          #+#    #+#             */
/*   Updated: 2021/02/26 09:39:27 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
    pid_t   pid;
    char comando[64];
    printf("minishell- ");
    ft_memset(comando, '\0', 64);
    scanf("%s", comando);
    while(ft_strcmp(comando, "exit"))
    {
        pid = fork();
        if (pid == 0)
        {
            execlp(comando, comando, NULL);
            printf("comando no válido\n");
            exit(0);
        }
        else
        {
            if (pid > 0)
            {
                waitpid(pid, 0, 0);
                printf("minishell- ");
                ft_memset(comando, '\0', 64);
                scanf("%s", comando);
            }
            else
                perror("ERROR FORK\n");
        }
    }
    exit(0);
}