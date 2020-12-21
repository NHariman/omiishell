/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 16:08:40 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/20 19:35:40 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** " " preserves literal value of all characters within the quotes
** with the exception of $, ` and \.
** ` and $ retain special meaning
** \ only retains meaning if followed by ` $ " \.
** ^ backslacshes that are followed by one of these characters are removed.
** backslash preceeding characters without a special meaning are left
** unmodified.
*/

static char		*get_cmd(char *str, int *i, t_shell *shell)
{
	char	*cmd;

	*i = *i + ft_iswhitespaces(str + *i);
	cmd = ft_no_quotes_str(str, i, shell, " ");
	if (cmd == NULL)
		return (NULL);
	while (cmd != NULL && ft_strchr(cmd, '=') != NULL)
	{
		free(cmd);
		cmd = NULL;
		while (str[*i] == ' ')
			*i = *i + 1;
		if (str[*i] != '\0')
			cmd = ft_no_quotes_str(str, i, shell, " ");
	}
	return (cmd);
}

static void		ft_check_case(t_shell *shell)
{
	if (!ft_strcmp(shell->argv[0], "echo"))
		ft_echo(shell);
	else if (!ft_strcmp(shell->argv[0], "env"))
		ft_env(shell);
	else if (!ft_strcmp(shell->argv[0], "pwd"))
		ft_pwd_main(shell);
	else
		ft_execute(shell->argv[0], shell);
}

static void		ft_wordparser(t_shell *shell)
{
	if (shell->argv[0] == NULL)
		return ;
	if (!ft_strcmp(shell->argv[0], "exit"))
		ft_exit_minishell(shell->argv, ft_arrlen(shell->argv), shell);
	else if (!ft_strcmp(shell->argv[0], "export"))
		ft_export(shell);
	else if (!ft_strcmp(shell->argv[0], "unset"))
		ft_unset(shell);
	else if (!ft_strcmp(shell->argv[0], "cd"))
		ft_cd(shell);
	else if (ft_strchr("eEpP", shell->argv[0][0]))
		ft_check_case(shell);
	else
		ft_execute(shell->argv[0], shell);
}

void			function_dispatcher(char *line, t_shell *shell)
{
	int		i;
	char	*cmd;
	char	**tmp;

	i = 0;
	cmd = get_cmd(line, &i, shell);
	tmp = ft_argv(line + i +
		ft_iswhitespaces(line + i + 1), shell);
	if (!tmp)
		shell->argv = empty_array(cmd);
	else
		shell->argv = ft_add_arr_front(tmp, cmd);
	int k = 0;
	while (shell->argv[k] != (char *)0)
	{
		ft_printf("shell->argv[%i]: {%s}\n", k, shell->argv[k]);
		k++;
	}
	shell->rds = ft_get_rdin(line);
	ft_printf("shell->rds: {%s}\n", shell->rds);
	if (!shell->rds)
		ft_wordparser(shell);
	else if (shell->rds)
	{	
		rd_main(shell->rds, shell);
		free(shell->rds);
	}
}

void			minishell_parser(char *line, t_shell *shell)
{
	t_qts		qts;

	if (line[0] == '\0' || ft_invalid_line(line, shell, ';') ||
	ft_invalid_line(line, shell, '|'))
		return ;
	ft_set_qts(&qts);
	ft_qt_start(line, &qts);
	if (qts.dq % 2 != 0 || qts.sq % 2 != 0)
		ft_printf_err("Error\nHanging quotes. Parsing failed.\n");
	else
		ft_make_prompts(line, shell);
}
