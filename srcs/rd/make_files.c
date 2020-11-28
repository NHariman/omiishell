/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_files.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/21 19:23:37 by ybakker       #+#    #+#                 */
/*   Updated: 2020/11/26 15:11:38 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
//what happened if you go back and make a file in someone elses folder on Codam, what happens?
//echo "hi" > /exam/file1

static int		ft_c_atot(char c)
{
	char	*str;
	int		nb;

	str = (char *)malloc((2) * sizeof(char));
	str[0] = c;
	str[1] = '\0';
	nb = ft_atoi(str);
	return (nb);
}

static int		open_close_file(char *str, int nb, t_shell *shell)
{
	int		fd;

	errno = 0;
	ft_printf("open closee\n");
	fd = open(str, O_EXCL | O_CREAT, 0666);
	if (fd < 0)
	{
		ft_printf_err("Error\n%s\n", strerror(errno));
		shell->exit_code = 1;
		return (1);
	}
	close(fd);
	nb = 0;
	return (0);
}

static int		open_fill_close_file(char *file, char *string,
int nb, t_shell *shell)
{
	int		fd;

	errno = 0;
	fd = 0;
	if (nb == 1)
	{
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
		{
			ft_printf_err("Error\n%s\n", strerror(errno));
			shell->exit_code = 1;
			return (1);
		}
		write(fd, string, ft_strlen(string));
		write(fd, "\n", 1);
		return (0);
	}
	if (nb == 2)
	{
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd < 0)
		{
			ft_printf_err("Error\n%s\n", strerror(errno));
			shell->exit_code = 1;
			return (1);
		}
		write(fd, string, ft_strlen(string));
		write(fd, "\n", 1);
		return (0);
	}
	nb = 0;
	// if (shell->check.shell == 1)
	// {
	// 	dup2(fd, 255);
	//	dup(fd, 1);
	// 	//shell;
	// 	close(fd);
	// }
	close(fd);//if shell is on, do this after shell is done
	return (0);
}

void	ft_rd_output(char *str, t_shell *shell)
{
	int		i;
	int		nb;
	char	*file;
	char	*string;

	i = 0;
	while (str[i])
	{
		while (str[i] == '\n')
			i++;
		file = ft_strcpystr(i, str, '\n');
		while (str[i] != '\n')
			i++;
		i++;
		nb = ft_c_atot(str[i]);//get dir
		i++;
		if (str[i] == '\n' && str[i + 1] == '\n')
		{
			i += 2;
			string = ft_strcpystr(i, str, '\0');
			open_fill_close_file(file, string, nb, shell);
			free(file);
			free(string);
			return ;
		}
		else
		{
			if (open_close_file(file, nb, shell) == 1)
			{
				free(file);
				return ;
			}
			i++;
		}
		free(file);
	}
}
