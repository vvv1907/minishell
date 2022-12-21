/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcolumbu <hcolumbu@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:53:59 by hcolumbu          #+#    #+#             */
/*   Updated: 2022/06/05 11:40:38 by hcolumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	left_redirect(t_com *com)
{
	int	output;

	output = 0;
	output = open(com->file, O_RDONLY);
	if (output == -1)
	{
		ft_putstr_fd("Myshell 🐚: ", 2);
		ft_putstr_fd(com->file, 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_exit_status = 126;
		return ;
	}
	dup2(output, 0);
	close(output);
}

void	right_redirect(t_com *com)
{
	int	output;

	output = 0;
	while (com->delim == 3 && com->file)
	{
		output = open(com->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (output == -1)
		{
			ft_putstr_fd("Myshell 🐚: ", 2);
			ft_putstr_fd(com->file, 2);
			ft_putendl_fd(": Permission denied", 2);
			g_exit_status = 126;
			return ;
		}
		if (com->next)
			com = com->next;
		else
			break ;
	}
	dup2(output, 1);
	close(output);
}

void	double_right_redirect(t_com *com)
{
	int	output;

	output = 0;
	while (com->delim == 5 && com->file)
	{
		output = open(com->file, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (output == -1)
		{
			ft_putstr_fd("Myshell 🐚: ", 2);
			ft_putstr_fd(com->file, 2);
			ft_putendl_fd(": Permission denied", 2);
			g_exit_status = 126;
			return ;
		}
		if (com->next)
			com = com->next;
		else
			break ;
	}
	dup2(output, 1);
	close(output);
}

void	redirect_handler(t_com *com, int *pipefd)
{
	int	output;

	output = 0;
	if (com->delim == 2)
		left_redirect(com);
	if (com->delim == 3)
		right_redirect(com);
	if (com->delim == 5)
		double_right_redirect(com);
	if (com->delim == 4)
	{
		output = heredoc(com);
		dup2(output, 0);
		close(output);
		if (com->next && com->next->delim == 1)
		{
			close(1);
			dup2(pipefd[1], 1);
			close(pipefd[1]);
			close(pipefd[0]);
		}	
	}
}
