/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 15:07:26 by ybakker       #+#    #+#                 */
/*   Updated: 2020/11/26 19:57:34 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/minishell.h"
#include <stdio.h>

int		main(int argc, char *argv[], char *envp[])
{
	int		i;
	char	*line;
	char	**hold;
	t_shell	*shell;

	i = argc;
	hold = argv;
	shell = calloc(1, sizeof(t_shell));
	shell->env = envp;
	shell->fd = -1;
	shell->oldnb = 0;
	line = NULL;
	while (i > 0)
	{
		ft_printf("\033[1;36m");
		ft_printf("minishell> ");
		ft_printf("\033[0m");
		i = get_next_line(0, &line);
		minishell_parser(line, shell);
		line = NULL;
		free(line);
	}
	return (0);
}
