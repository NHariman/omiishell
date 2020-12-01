/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_check.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 15:28:15 by ybakker       #+#    #+#                 */
/*   Updated: 2020/12/01 23:09:37 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int			ft_check_rd_echo(t_struct_rd *rd, t_shell *shell)
{
    int     len;
    int     i;

    len = 0;
    rd->txt = 0;
    free(rd->string);
    while (shell->ret[len] != '\n' && shell->ret[len])
        len++;
    rd->string = (char *)malloc((len + 1) * sizeof(char));
    i = 0;
    while (len > 0)
    {
        rd->string[i] = shell->ret[i];
        i++;
        len--;
    }
    rd->string[i] = '\0';
    return (0);
}

int			ft_check_rd(t_struct_rd *rd, t_shell *shell)
{
    if (shell->ret)
        ft_check_rd_echo(rd, shell);
    else
        return (1);
    return (0);
}