/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>

# define WHITE_SPACES " \t\v\r\f"
# define PIPE 1
# define LEF_SIN_REDIR 2
# define RIGH_SIN_REDIR 3
# define LEF_DOUB_REDIR 4
# define RIGH_DOUB_REDIT 5
# define SIN_Q 1
# define DOUB_Q 2

int	g_exit_status;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_command
{
	char				*name;
	char				**arg;
	int					delim;
	char				*file;
	struct s_command	*next;
}	t_com;

typedef struct s_words
{
	char	*res;
	int		len;
	int		i;
	int		j;
	int		count_one;
	int		count_double;
}	t_words;

typedef struct s_split
{
	char	**split_by_words;
	int		words;
}	t_split;

typedef struct s_dollar
{
	char	*tmp;
	int		count_one;
	int		count_double;
	char	*rez;
	char	*head;
	char	*com;
	char	*tail;
}	t_dollar;

typedef struct s_exec
{
	char	*path;
	char	**path_cmd;
	char	**cmd_full;
	char	*cmd_exec;
	char	**env;
	int		pipe_num;
	int		infile;
	int		outfile;
}	t_exec;

// list_utils.c
char		*read_the_line(void);
void		read_envp(char **env, t_envp **envp_list);
t_envp		*envp_new(char *content);
void		envp_add_front(t_envp **lst, t_envp *new);
void		com_add_back(t_com **lst, t_com *new);

// signal_handler.c
void		ctrl_c_handler(int signum);
int			signal_handler(void);

// count_words.c
int			ft_separator(char c);
void		count_redirects(char *str, int *ind, int *num_words);
void		count_rest(char *str, int *ind, int *num_words);
int			count_words(char *str, int i, int words);

// split_by_words.c
char		*write_redir(char *str, int *ind);
int			count_space(char *str);
char		*write_words(char *str, int *ind);
char		**write_split_words(char **split_by_words, char *str);
char		**split_by_words(char *str);

// utils_parse.c
int			ft_isdelim(char *s);
int			delimetr(char *s);
void		dollar_redirect(char *str, int *num);
void		make_struct1(char **arr, int *ind, t_com **new_com);

// check_sytax.c
int			ft_check_eve_quotes(char *str);
int			t_check_first_end(char *str);
int			check_syntax(char *str);
int			check_double_delim(char **arr);

// replace_dollar.c
void		change_dollar1(t_dollar *doll, char *str);
char		*subst_dollar(char *com, t_envp *envp_list);
char		*chng_doll(t_dollar *doll, char *str, int *num, t_envp *envp_list);
void		repl_doll(t_dollar *doll, int *ind, char **str, t_envp *envp_list);
int			replace_dollar(char **str, t_envp *envp_list);

// init_struct.c
t_split		*init_split(char *str);
t_words		*init_write_w(char *str);
t_com		*init_com(void);
t_dollar	*init_doll(void);

// make_struct.c
t_com		*com_new1(char *name, char **arr, int delim, char *file);
int			make_arg(char ***arg, char **arr, int i);
int			make_new_com(int i, char **arr, t_com **new_com);
void		make_struct(char **arr, t_com **com);

// make_struct_utils.c
void		ft_copy_arr(char **arr_in, char **arr_out);
void		ft_one_name(t_com **com);
int			ft_n_words(char **arr, int i);
void		ft_empty_arr(char ***tmp, char *str);
void		add_first_str_in_arr(char ***arr, char *str);

// utils_free
void		free_envp_list(t_envp *envp_list);
void		free_com_list(t_com *com);
void		ft_free_com_list(t_com **com);
void		free_array(char **array);
void		ft_free(char *str);
void		free_pipe_struct(t_exec *exec);

// utils_builtin
int			print_env_declare(t_envp *envp_list);
int			var_position_in_envp(t_envp *envp_list, char *str);
int			put_value_to_envp(t_envp *envp_list, char *key, char *new_value);
char		*get_value_from_envp(t_envp *envp_list, char *str);
void		add_var_to_envp_list(t_envp **envp_list, char **array, char *str);

// builtins
int			builtin_export(t_com *com, t_envp **envp_list);
int			builtin_unset(t_com *com, t_envp **envp_list);
void		builtin_exit(t_com *com, t_envp *envp_list);
int			builtin_cd(t_com *com, t_envp *envp_list);
int			builtin_pwd(t_envp *envp_list);
int			builtin_env(t_envp *envp_list);
int			builtin_echo(t_com *com);

// Executor
int			heredoc(t_com *com);
void		execute(t_com *com, t_envp **envp_list);
void		executor(t_com *com, t_envp **envp_list, t_exec *exec);
void		pipe_handler(t_com *com, t_envp **envp_list, t_exec *exec);
void		pipex(t_com *com, t_envp **envp_list, t_exec *exec);
void		get_env(t_envp *envp_list, t_exec *exec);
void		make_full_com(t_com *com, t_exec *exec);
void		check_cmd(t_com *com, t_exec *exec);
void		find_args(t_com *com, t_exec *exec);
char		*make_cmd(t_com *com, t_exec *exec);
void		redirect_handler(t_com *com, int *pipefd);

int			envsize(t_envp *lst);
int			lstsize(t_com *lst);
void		show_error(char *error);
int			count_array(t_com *com);
int			count_pipes(t_com *com);
void		std_out_close(int save_stdout);
void		pipe_close(t_com *com, int fd0, int fd1);

#endif
