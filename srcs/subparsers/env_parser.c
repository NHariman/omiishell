/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/18 13:20:43 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/26 17:21:25 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_env_parser(char *str, int *i, t_shell *shell)
{
	int		start;
	int		check;
	char	*env_str;
	t_qts	qts;

	start = *i;
	ft_set_qts(&qts);
	ft_qt_line(str, &qts, i);
	env_str = ft_substr(str, start, *i - start);
	check = env_main(env_str, shell);
	if (ft_strchr("\n;\0", str[*i]) && check == 1)
		ft_printf("%s\n", shell->env_s);
	env_str = NULL;
	free(env_str);
}
