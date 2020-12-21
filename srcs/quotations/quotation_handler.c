/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotation_handler.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 20:28:01 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/28 19:46:46 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				ft_set_qts(t_qts *qts)
{
	qts->dq = 0;
	qts->sq = 0;
}

int					ft_backslash_check(char *line, int i)
{
	int	backslash;

	backslash = 0;
	while (i > 0)
	{
		i--;
		if (line[i] != '\\')
			break ;
		else if (line[i] == '\\')
			backslash++;
	}
	return (backslash);
}

int					ft_qt_check(char *line, int *i, int type, t_qts *qts)
{
	int backslash;

	backslash = 0;
	ft_set_qts(qts);
	*i = *i + 1;
	while (line[*i] != '\0')
	{
		if ((line[*i] == '\'' && type == SQ) ||
		(line[*i] == '\"' && type == DQ))
		{
			if (type == DQ)
			{
				backslash = ft_backslash_check(line, *i);
				if (backslash % 2 == 0)
					return (0);
			}
			else
				return (0);
		}
		*i = *i + 1;
	}
	return (1);
}

void				ft_qt_line(char *line, t_qts *qts, int *i)
{
	while (line[*i] != '\0')
	{
		if (ft_strchr(";", line[*i]))
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

void				ft_qt_start(char *line, t_qts *qts)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\'' && line[i - 1] != '\\') ||
		(line[i] == '\'' && ft_backslash_check(line, i) % 2 == 0))
			qts->sq = ft_qt_check(line, &i, SQ, qts);
		else if ((line[i] == '\"' && line[i - 1] != '\\') ||
		(line[i] == '\"' && ft_backslash_check(line, i) % 2 == 0))
			qts->dq = ft_qt_check(line, &i, DQ, qts);
		i++;
	}
}
