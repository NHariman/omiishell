/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rd_loop.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 15:28:15 by ybakker       #+#    #+#                 */
/*   Updated: 2020/11/21 19:08:36 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

/*
file,rd,file,rd,file,rd;;string
hello too many ' '
*/

void			ft_file_input_string(t_struct_rd *rd, t_shell *shell)
{
	t_struct_m	*echo;

	echo = ft_calloc(1, sizeof(t_struct_m));
	rd->tmp = ft_strdup(echo_main(rd->string, echo, shell));
	rd->string = ft_strdup(ft_strtrim(rd->tmp, "\n"));
	free(rd->tmp);
	free(echo->tmp);
	free(echo->str);
	free(echo);
	rd->cache = ft_strjoin(rd->output, "\n");
	free(rd->output);
	rd->output = ft_strjoin(rd->cache, rd->string);
	free(rd->cache);
	free(rd->string);
}

static void		create_string(t_struct_rd *rd)
{
	rd->tmp = ft_strtrim(rd->file, "\n");
	free(rd->file);
	rd->file = ft_strdup(rd->tmp);
	free(rd->tmp);
	rd->cache = ft_strjoin(rd->output, rd->file);
	free(rd->file);
	free(rd->output);
	rd->tmp = ft_strjoin(rd->cache, "\n");
	free(rd->cache);
	rd->output = ft_itoa(rd->dir);
	rd->cache = ft_strjoin(rd->tmp, rd->output);
	free(rd->tmp);
	free(rd->output);
	rd->output = ft_strjoin(rd->cache, "\n");
	free(rd->cache);
}

static void		loop_if_one(t_struct_rd *rd)
{
	if (rd->str != NULL)
	{
		rd->cache = ft_strjoin(rd->string, " ");
		free(rd->string);
		rd->string = ft_strdup(rd->cache);
		free(rd->cache);
	}
	while (rd->str[rd->i] == ' ')
		rd->i++;
	rd->len = ft_len_string_rd(rd);
	ft_echo_string_rd(rd);
	rd->tmp = ft_strjoin(rd->string, rd->cache);
	free(rd->string);
	free(rd->cache);
	rd->string = ft_strtrim(rd->tmp, " ");
	free(rd->tmp);
}

int				rd_loop(t_struct_rd *rd, t_shell *shell)
{
	int			error;
	t_struct_m	*echo;

	echo = ft_calloc(1, sizeof(t_struct_m));
	rd->i = 0;
	rd->file = ft_strdup("");
	while (rd->str[rd->i] && rd->str[rd->i] != '\n' && error == 0)
	{
		set_value_rd(rd);
		error = rd_check_error_rd(rd);
		if (error != 0)
			return (error);
		cut_string_shell(rd, shell);
		while (rd->str[rd->i] == ' ')
			rd->i++;
		if (rd->str[rd->i] != '>' && rd->str[rd->i] != '\0' &&
		rd->str[rd->i] != '\n' && rd->txt == 0)
			loop_if_one(rd);
		else if (rd->str[rd->i] != '>' && rd->str[rd->i] != '\0' &&
		rd->str[rd->i] != '\n' && rd->txt == 1)
			rd->len = ft_len_string_rd(rd);
		create_string(rd);
	}
	ft_file_input_string(rd, shell);
	return (error);
}
