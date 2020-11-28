/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 15:07:26 by ybakker       #+#    #+#                 */
/*   Updated: 2020/11/13 18:27:31 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/minishell.h"
#include <stdio.h>

int		main(int argc, char *argv[], char *envp[])
{
	int		i;
	int		j;
	char	*line;
	char	**hold;
	t_shell	*shell;

	i = argc;
	j = 0;
	hold = argv;
	shell = ft_calloc(1, sizeof(t_shell));
	shell->env = envp;
	while (i > 0)
	{
		j = 0;
		ft_printf("minishell> ");
		i = get_next_line(0, &line);
		if (!ft_strncmp(line, "exit\n", ft_strlen("exit\n")))
			exit_minishell();
		ft_doublequotes_str(line, &j, shell);
		//minishell_parser(line, envp);
		free(line);
	}
	return (0);
}


// int		main(int argc, char *argv[], char *envp[])
// {
// 	int		i;
// 	char	*line;
// 	char	**hold;

// 	i = argc;
// 	hold = argv;
// 	while (i > 0)
// 	{
// 		ft_printf("minishell> ");
// 		i = get_next_line(0, &line);
// 		if (!ft_strncmp(line, "exit\n", ft_strlen("exit\n")))
// 			exit_minishell();
// 		minishell_parser(line, envp);
// 		free(line);
// 	}
// 	return (0);
// }
