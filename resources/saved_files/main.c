/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 15:07:26 by ybakker       #+#    #+#                 */
/*   Updated: 2020/11/11 09:52:51 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/minishell.h"
#include <stdio.h>

int		main(int argc, char *argv[], char *envp[])
{
	int			i;
	char		*line;
	char		**hold;
	char		*str;
	t_shell		*shell;
	t_struct_m	*echo;

	i = argc;
	hold = argv;
	shell = calloc(1, sizeof(t_shell));
	echo = calloc(1, sizeof(t_struct_m));
	shell->env = envp;
	while (i > 0)
	{
		ft_printf("minishell> ");
		i = get_next_line(0, &line);
		if (!ft_strncmp(line, "exit\n", ft_strlen("exit\n")))
			exit(0);
		str = echo_main(line, echo, shell);
		//minishell_parser(line, envp);
		// free(line);//double free???
		free(str);
	}
	return (0);
}
