/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_parser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 18:26:39 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/18 14:04:08 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fake_rd_main(char *str, t_shell *shell)
{
	t_shell *sholl;

	sholl = shell;
	ft_printf("redirect str: {%s}\n", str);
}

void		ft_rd_parser(char *str, int *i, t_shell *shell)
{
	int		start;
	char	*rd_str;

	start = *i;
	while (str[*i] != '\n' && str[*i] != '\0' && !ft_strchr("|;", str[*i]))
		*i = *i + 1;
	if (start == *i || *i == 0)
		rd_str = ft_strdup("\n");
	else
		rd_str = ft_substr(str, start, *i - start);
	fake_rd_main(rd_str, shell);
}
