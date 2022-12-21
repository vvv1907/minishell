/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split	*init_split(char *str)
{
	t_split	*split_w;

	split_w = malloc(sizeof(t_split));
	split_w->words = count_words(str, 0, 0);
	split_w->split_by_words = (char **)malloc((split_w->words + 1) * \
															sizeof(char *));
	if (!split_w->split_by_words)
		exit(1);
	return (split_w);
}

t_words	*init_write_w(char *str)
{
	t_words	*write_w;

	write_w = malloc(sizeof(t_words));
	write_w->count_one = 0;
	write_w->count_double = 0;
	write_w->j = 0;
	write_w->i = 0;
	write_w->len = count_space(str);
	write_w->res = malloc(sizeof(char *) * (write_w->len + 1));
	write_w->res[write_w->len] = '\0';
	if (!write_w->res)
		exit(1);
	return (write_w);
}

t_com	*init_com(void)
{
	t_com	*com;

	com = malloc(sizeof(t_com));
	com->name = NULL;
	com->arg = NULL;
	com->delim = 0;
	com->file = NULL;
	com->next = NULL;
	return (com);
}

t_dollar	*init_doll(void)
{
	t_dollar	*doll;

	doll = malloc(sizeof(t_dollar));
	doll->tmp = NULL;
	doll->count_one = 0;
	doll->count_double = 0;
	doll->rez = NULL;
	doll->head = NULL;
	doll->com = NULL;
	doll->tail = NULL;
	return (doll);
}
