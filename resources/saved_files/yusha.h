/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   yusha.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ybakker <ybakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 16:35:31 by ybakker       #+#    #+#                 */
/*   Updated: 2020/11/07 18:19:08 by ybakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_struct_e
{
	int			begin;
	int			end;
	int			single;
	int			doubble;
	char*		str;
	char*		s_begin;
	char*		s_end;
	char*		s_cache;
}				t_struct_e;

typedef struct	s_struct_m
{
	char		*cache;
	char		*str;
	char		*store;
	int			i;
	int			path;
	int			single;
	int			doubble;
	int			beg;
	int			end;
	int			len;
	int			stat;
	int			n;
	int			error;
	int			start;
	int			t_begin;
	int			t_split;
	char*		t_cache;
	char*		t_tmp;
}				t_struct_m;

typedef struct	s_struct_em
{
	int			begin;
	int			end;
	int			single;
	int			doubble;
	char*		str;
	char*		s_begin;
	char*		s_end;
	char*		s_cache;
}				t_struct_em;

char		*echo_main(char *str, t_struct_m *echo);
int			check_flag_n(char *str);
void		echo_no_str(t_struct_m *echo);
void		echo_str_single(t_struct_m *echo);
void		echo_str_double(t_struct_m *echo);
int			skip_character(char *str, int i, char c);

//multiple uses
int			echo_check(t_struct_m *echo, char c);

//tripple trim
void   		ft_tripple_trim(t_struct_m *echo);
void   		ft_split_begin(t_struct_em *trim, char *str);
void   		ft_split_end(t_struct_em *trim, char *str);
int			ft_stop_split(t_struct_em *trim, char *str);
void		ft_variable(t_struct_em *trim, char *str);

//variable
int    ft_search_variable(t_struct_em *trim, char *str);

//empty line
char*			ft_echo_empty_line(char* str);

//single use functions
int			ft_strncmp_echo(int i, char *s1, char *s2, int n);
void		check_empty_beg(t_struct_m *echo);
char*		ft_fillstr(char *str1, char	c, int len);
