/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   re_direct.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 15:28:15 by ybakker       #+#    #+#                 */
/*   Updated: 2020/11/26 15:09:20 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int			rd_check_error_rd(t_struct_rd *rd)
{
	int		error;

	error = 0;
	if (rd->str[rd->i] == '>')
	{
		rd->dir++;
		rd->i++;
	}
	if (rd->str[rd->i] == '>')
	{
		rd->dir++;
		rd->i++;
	}
	if (rd->str[rd->i] == '>' && rd->str[rd->i + 1] == '>')
		return (4);
	else if (rd->str[rd->i] == '>')
		return (3);
	return (0);
}

char		*rd_save_echo(t_struct_rd *rd)
{
	int		len;
	int		i;
	char	*str;

	len = rd->i;
	i = 0;
	while (rd->str[len] == '\n' || rd->str[len] || rd->str[len] == '>')
		len++;
	str = (char *)malloc((len + 1) * sizeof(char));
	while (rd->i <= len)
	{
		str[i] = rd->str[rd->i];
		i++;
		rd->i++;
	}
	str[i] = '\0';
	return (str);
}

int		start_rd(t_struct_rd *rd, t_shell *shell)
{
	int		error;

	rd->i = 0;
	error = 0;
	// cut_string_shell(rd->s_str, rd, shell);//use to get the string out
	rd->string = ft_strdup("");
	error = ft_check_rd(rd, shell);
	if (error == 0)
		error = rd_loop(rd, shell);
	return (error);
}

char		*rd_main(char *str, t_shell *shell)
{
	int				error;
	t_struct_rd		*rd;

	rd = calloc(1, sizeof(t_struct_rd));
	rd->output = ft_strdup("");
	set_value_rd(rd);
	rd->tmp = ft_strtrim(str, "\n");
	free(str);
	str = ft_strdup(rd->tmp);
	rd->i = 0;
	rd->str = ft_strdup(str);
	ft_printf("in == [%s][%i]\n", rd->str, rd->i);
	error = start_rd(rd, shell);
	str = ft_strdup(rd->output);
	free(rd->output);
	return (str);
}
