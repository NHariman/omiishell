/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset_parser.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 07:42:49 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/28 22:20:28 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			ft_unset_parser(char *str, int *i, t_shell *shell)
{
	int		start;
	char	*substr;
	t_qts	qts;

	start = *i;
	ft_set_qts(&qts);
	ft_qt_line(str, &qts, i);
	substr = ft_substr(str, start, *i - start);
	ft_unset(substr, shell);
	free(substr);
	shell->exit_code = 0;
	return ;
}
