/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*subst_dollar(char *com, t_envp *envp_list)
{
	while (envp_list)
	{
		if (!ft_strncmp(com, envp_list->key, 1000))
			return (envp_list->value);
		envp_list = envp_list->next;
	}
	return ("");
}

void	change_dollar1(t_dollar *doll, char *str)
{
	char	*tmp_str;

	doll->rez = ft_strjoin(doll->head, doll->com);
	tmp_str = doll->rez;
	doll->rez = ft_strjoin(doll->rez, doll->tail);
	str = doll->rez;
	ft_free(tmp_str);
	ft_free(doll->head);
	ft_free(doll->tail);
}

char	*chng_doll(t_dollar *doll, char *str, int *num, t_envp *envp_list)
{
	int		n;
	int		i;
	t_envp	*tmp;
	char	*tmp_str;

	n = *num;
	doll->rez = ft_substr(str, 0, ft_strlen(str));
	tmp = envp_list;
	tmp_str = doll->rez;
	doll->head = ft_substr(doll->rez, 0, n);
	ft_free(tmp_str);
	i = n;
	while (str[i] && ft_isalnum(str[i + 2]))
		i++;
	doll->com = ft_substr(str, n + 1, i - n + 1);
	doll->tail = ft_substr(str, i + 2, ft_strlen(str));
	tmp_str = doll->com;
	doll->com = subst_dollar(doll->com, envp_list);
	ft_free(tmp_str);
	envp_list = tmp;
	change_dollar1(doll, str);
	*num = 0;
	return (doll->rez);
}

void	repl_doll(t_dollar *doll, int *ind, char **str, t_envp *envp_list)
{
	int	i;

	i = *ind;
	if ((*str)[i + 1] && (*str)[i + 1] != '?')
	{
		doll->tmp = *str;
		*str = chng_doll(doll, *str, &i, envp_list);
		ft_free(doll->tmp);
		doll->count_one = 0;
		doll->count_double = 0;
	}
}

int	replace_dollar(char **str, t_envp *envp_list)
{
	t_dollar	*doll;
	int			i;

	i = 0;
	doll = init_doll();
	while ((*str)[i])
	{
		if ((*str)[i] == '<' && ((*str)[i + 1] && (*str)[i + 1] == '<'))
			dollar_redirect(*str, &i);
		if ((*str)[i] == '$' && doll->count_one % 2 == 0)
			repl_doll(doll, &i, str, envp_list);
		if ((*str)[i] == '\'' && doll->count_double % 2 == 0)
			doll->count_one++;
		if ((*str)[i] == '\"' && doll->count_one % 2 == 0)
			doll->count_double++;
		i++;
	}
	free(doll);
	return (0);
}
