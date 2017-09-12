/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 21:17:22 by akaplyar          #+#    #+#             */
/*   Updated: 2017/09/12 21:17:23 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ls_error_cmp(void *data1, void *data2)
{
	t_info	*cur;
	t_info	*next;

	cur = (t_info*)data1;
	next = (t_info*)data2;
	if (cur->err && next->err)
		return (ft_strcmp(cur->name, next->name) > 0 ? 1 : 0);
	else
		return (cur->err ? 0 : 1);
}

static int	ls_alpha_cmp(void *data1, void *data2)
{
	t_info	*cur;
	t_info	*next;

	cur = (t_info*)data1;
	next = (t_info*)data2;
	if (cur->err || next->err)
		return (ls_error_cmp(data1, data2));
	else
		return (ft_strcmp(cur->name, next->name) > 0 ? 1 : 0);
}

static int	ls_reverse_cmp(void *data1, void *data2)
{
	t_info	*cur;
	t_info	*next;

	cur = (t_info*)data1;
	next = (t_info*)data2;
	if (cur->err || next->err)
		return (ls_error_cmp(data1, data2));
	else
		return (ft_strcmp(cur->name, next->name) < 0 ? 1 : 0);
}

static int	ls_time_cmp(void *data1, void *data2)
{
	t_info	*cur;
	t_info	*next;

	cur = (t_info*)data1;
	next = (t_info*)data2;
	if (cur->err || next->err)
		return (ls_error_cmp(data1, data2));
	else
	{
		if (cur->t_time == next->t_time)
		{
			if (cur->sec == next->sec)
				return (ft_strcmp(cur->name, next->name) < 0 ? 1 : 0);
			else
				return (cur->sec > next->sec ? 0 : 1);
		}
		else
			return (cur->t_time > next->t_time ? 0 : 1);
	}
}

void		ls_sort(t_list **list, t_ls *ls)
{
	if (ls->r)
		ft_lst_sort(list, ls_reverse_cmp, 0, (int)ft_lstcount(*list));
	else if (ls->t)
		ft_lst_sort(list, ls_time_cmp, 0, (int)ft_lstcount(*list));
	else if (ls->f)
		ft_lst_sort(list, ls_error_cmp, 0, (int)ft_lstcount(*list));
	else
		ft_lst_sort(list, ls_alpha_cmp, 0, (int)ft_lstcount(*list));
}
