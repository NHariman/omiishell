/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 14:38:58 by nhariman      #+#    #+#                 */
/*   Updated: 2020/12/03 18:55:49 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ft_pwd(void)
{
	char	cwd[1024];
	char	*cwd_res;

	cwd_res = getcwd(cwd, sizeof(cwd));
	errno = 0;
	if (cwd_res == NULL)
	{
		ft_printf_err("Error\n%s\n", strerror(errno));
		return (NULL);
	}
	return (cwd_res);
}

void		ft_pwd_main(t_shell *shell)
{
	char	cwd[1024];
	char	*cwd_res;

	errno = 0;
	cwd_res = getcwd(cwd, sizeof(cwd));
	if (cwd_res == NULL)
	{
		ft_printf_err("Error\n%s\n", strerror(errno));
		return ;
	}
	shell->ret = cwd_res;
	shell->exit_code = 0;
	if (errno != 0)
		shell->exit_code = 1;
	ft_printf("%s\n", shell->ret);
	return ;
}
