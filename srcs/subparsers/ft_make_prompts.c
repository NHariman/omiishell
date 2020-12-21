/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_make_prompts.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 20:18:42 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/22 00:09:01 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		ft_not_valid_prompt(char *str)
{
	int len;

	len = ft_strlen(str) - 1;
	while (str[len] == ' ')
		len--;
	if (ft_strchr("<>|", str[len]))
		return (ft_printf_err(
				"omiishell: syntax error near unexpected token `;'\n"));
	else
		return (0);
}

static int		ft_valid_prompt(char **prompts, t_shell *shell)
{
	int i;

	i = 0;
	while (prompts[i] != (char *)0)
	{
		if (ft_not_valid_prompt(prompts[i]) ||
		ft_invalid_line(prompts[i], shell, '|'))
			return (0);
		i++;
	}
	return (1);
}

static int		ft_has_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' && ft_backslash_check(str, i) % 2 == 0)
			return (1);
		if (ft_strchr("\'\"", str[i]) && ft_backslash_check(str, i) % 2 == 0)
			ft_skip_quotes(str, &i, str[i]);
		else if (str[i] == '\\')
			i = i + 2;
		else
			i = i + 1;
	}
	return (0);
}

static char		*ft_rm_spaces(char *str)
{
	int			len;
	char		*trim;

	len = ft_strlen(str) - 1;
	while (str[len] == ' ' && str[len - 1] != '\\' && len >= 0)
		len--;
	trim = ft_substr(str, 0, len + 1);
	return (trim);
}

void			ft_make_prompts(char *str, t_shell *shell)
{
	int		i;
	char	**prompts;
	char	*newstr;

	i = 0;
	newstr = ft_rm_spaces(str);
	prompts = ft_get_prompts(newstr);
	free(newstr);
	if (!ft_valid_prompt(prompts, shell))
	{
		shell->exit_code = 258;
		ft_free_array(prompts, ft_arrlen(prompts));
		return ;
	}
	int k = 0;
	while (prompts[k] != (char *)0)
	{
		ft_printf("prompts[%i]: {%s}\n", k, prompts[k]);
		k++;
	}
	while (prompts[i] != (char *)0)
	{
		if (ft_has_pipe(prompts[i]))
			ft_pipe_splitter(prompts[i], shell);
		else
			function_dispatcher(prompts[i], shell);
		ft_clear_shell(shell);
		i++;
	}
	ft_free_array(prompts, ft_arrlen(prompts));
	return ;
}

// void			ft_make_prompts(char *str, t_shell *shell)
// {
// 	int		i;
// 	char	**prompts;

// 	i = 0;
// 	prompts = ft_get_prompts(str);
// 	int k = 0;
// 	while (prompts[k] != (char *)0)
// 	{
// 		ft_printf("prompts[%i]: {%s}\n", k, prompts[k]);
// 		k++;
// 	}
// 	if (!ft_valid_prompt(prompts, shell))
// 	{
// 		shell->exit_code = 258;
// 		ft_free_array(prompts, ft_arrlen(prompts));
// 		return ;
// 	}
// 	while (prompts[i] != (char *)0)
// 	{
// 		if (ft_has_pipe(prompts[i]))
// 			ft_pipe_splitter(prompts[i], shell);
// 		else
// 			function_dispatcher(prompts[i], shell);
// 		ft_clear_shell(shell);
// 		i++;
// 	}
// 	ft_free_array(prompts, ft_arrlen(prompts));
// 	return ;
// }