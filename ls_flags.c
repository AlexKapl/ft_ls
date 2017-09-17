/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 14:13:34 by akaplyar          #+#    #+#             */
/*   Updated: 2017/09/17 14:13:35 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void				ls_sort_flags(t_ls *ls, char c)
{
	if (c == 'r')
		ls->r = 1;
	else
	{
		ls->f = 0;
		ls->t = 0;
		ls->bs = 0;
		if (c == 'f')
		{
			ls->a = 1;
			ls->f = 1;
		}
		else if (c == 't')
			ls->t = 1;
		else
			ls->bs = 1;
	}
}

static void		ls_bonus_flags(t_ls *ls, char c, char *str)
{
	if (c == 'c')
		ls->cu = 1;
	else if (c == 'u')
		ls->cu = 2;
	else if (c == 'f' || c == 'S' || c == 'r' || c == 't')
		ls_sort_flags(ls, c);
	else if (c == 'p')
		ls->p = 1;
	else if (c == 'k')
		ls->k = 1;
	else if (c == '@')
		ls->dog = 1;
	else if (c == 'n')
		ls->n = 1;
	else
		ls_errors(OPT_ERR, str);
}

void			ls_check_flags(t_ls *ls, int *i, int ac, char **av)
{
	while (++*i < ac && av[*i][0] == '-')
	{
		av[*i] += 1;
		while (*(av[*i]))
		{
			if (*(av[*i]) == 'l')
				ls->l = 1;
			else if (*(av[*i]) == '1')
				ls->l = 0;
			else if (*(av[*i]) == 'a')
				ls->a = 1;
			else if (*(av[*i]) == 'R')
				ls->br = 1;
			else if (*(av[*i]) == 'A')
				ls->a = 2;
			else if (*(av[*i]) == 's')
				ls->s = 1;
			else if (*(av[*i]) == 'i')
				ls->i = 1;
			else
				ls_bonus_flags(ls, *(av[*i]), av[*i]);
			av[*i] += 1;
		}
	}
}
