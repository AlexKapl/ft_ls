/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 21:18:24 by akaplyar          #+#    #+#             */
/*   Updated: 2017/09/12 21:19:02 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_init(t_ls *ls)
{
	ls->list = NULL;
	ls->a = 0;
	ls->cu = 0;
	ls->f = 0;
	ls->i = 0;
	ls->k = 0;
	ls->l = 0;
	ls->n = 0;
	ls->p = 0;
	ls->r = 0;
	ls->s = 0;
	ls->t = 0;
	ls->br = 0;
	ls->bs = 0;
	ls->dog = 0;
	ls->width[0] = 0;
	ls->width[1] = 0;
	ls->width[2] = 0;
	ls->width[3] = 0;
	ls->width[4] = 0;
	ls->width[5] = 0;
	ls->width[6] = 0;
	ls->width[7] = 0;
}

static void		ls_check_params(t_ls *ls, int i, int ac, char **av)
{
	t_list		*list;

	if (i == ac)
	{
		list = (ft_lstnew(".", 2));
		ls_readdir(&list, ls);
	}
	else
	{
		ls->opts[0] = 1;
		ls->opts[1] = 1;
		while (i < ac)
		{
			ls_file_list(ls, ".", av[i]);
			i++;
		}
		if (ft_lstcount(ls->list) == 1)
		{
			ls->opts[1] = 0;
			list = ft_lstnew(av[i - 1], ft_strlen(av[i - 1]) + 1);
			ls_clear(ls, &list);
		}
		else
			ls_params(ls);
	}
}

int				main(int ac, char **av)
{
	int			i;
	t_ls		ls;

	i = 0;
	ls_init(&ls);
	ls.opts[0] = 0;
	ls.opts[1] = 0;
	ls.opts[2] = 0;
	ls_check_flags(&ls, &i, ac, av);
	ls_check_params(&ls, i, ac, av);
	return (0);
}
