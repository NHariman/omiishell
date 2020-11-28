/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_parser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 18:26:39 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/26 13:21:34 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_qt_rd(char *line, t_qts *qts, int *i)
{
	while (line[*i] != '\0')
	{
		if (line[*i] == ';')
			return ;
		else if ((line[*i] == '\'' && line[*i - 1] != '\\') ||
		(line[*i] == '\'' && ft_backslash_check(line, *i) % 2 == 0))
		{
			qts->sq = ft_qt_check(line, i, SQ, qts);
			*i = *i + 1;
		}
		else if ((line[*i] == '\"' && line[*i - 1] != '\\') ||
		(line[*i] == '\"' && ft_backslash_check(line, *i) % 2 == 0))
		{
			qts->dq = ft_qt_check(line, i, DQ, qts);
			*i = *i + 1;
		}
		else
			*i = *i + 1;
	}
}

void		ft_rd_parser(char *str, int *i, t_shell *shell)
{
	int		start;
	char	*rd_str;
	t_qts	qts;

	start = *i;
	ft_set_qts(&qts);
	ft_qt_rd(str, &qts, i);
	if (start == *i || *i == 0)
		rd_str = ft_strdup("\n");
	else
		rd_str = ft_substr(str, start, *i - start);
	shell->rd_r = ft_strdup(rd_main(rd_str, shell));
	shell->check.rd = 1;
	if (ft_strchr("\n;\0", str[*i]))
		ft_rd_output(shell->rd_r, shell);
}
