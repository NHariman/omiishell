/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 16:08:40 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/28 18:29:46 by nhariman      ########   odam.nl         */
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
	shell->cmd = ft_no_quotes_str(str, i, shell);
	return (shell->cmd);
}

static void		ft_check_case(char *cmd, char *line, int *i, t_shell *shell)
{
	char *tmp;

	tmp = ft_find_case_cmd(cmd);
	if (!ft_strncmp(tmp, "echo", ft_strlen(tmp)))
		ft_echo_parser(line, i, shell);
	else if (!ft_strncmp(tmp, "env", ft_strlen(tmp)))
		ft_env_parser(line, i, shell);
	else if (!ft_strncmp(tmp, "pwd", ft_strlen(tmp)))
		ft_pwd_main(line, i, shell);
	else
		ft_execv_parser(cmd, line, i, shell);
}

static void		ft_wordparser(char *line, int *i, t_shell *shell)
{
	char	*cmd;

	cmd = NULL;
	if (line[*i] == '\n' || line[*i] == '\0')
		return ;
	cmd = get_cmd(line, i, shell);
	if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		exit_minishell(line, i, shell);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		ft_export_parser(line, i, shell);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		ft_unset_parser(line, i, shell);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		ft_cd(line, i, shell);
	else if (ft_strchr("eEpP", cmd[0]))
		ft_check_case(cmd, line, i, shell);
	else if (line[*i] != '\0')
		ft_execv_parser(cmd, line, i, shell);
	cmd = NULL;
	free(cmd);
}

static void		function_dispatcher(char *line, t_shell *shell)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		while (line[i] == ' ')
			i++;
		if (!ft_strchr("><;|\n\0", line[i]))
			ft_wordparser(line, &i, shell);
		if (line[i] == '>')
			ft_rd_parser(line, &i, shell);
		if (line[i] == '<')
			ft_rd_parser(line, &i, shell);
		if (line[i] == '|')
			ft_printf("pipe function here, |, takes the shell struct\n");
		if (line[i] == ';' || line[i] == '\n' || line[i] == '\0')
			ft_clear_shell(shell);
		i++;
	}
	free(line);
}

void			minishell_parser(char *line, t_shell *shell)
{
	t_qts		qts;

	ft_set_qts(&qts);
	ft_qt_start(line, &qts);
	if (qts.dq % 2 != 0 || qts.sq % 2 != 0)
		ft_printf_err("Error\nHanging quotes. Parsing failed.\n");
	else
		function_dispatcher(line, shell);
}
