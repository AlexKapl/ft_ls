#include "ft_ls.h"

static int	ls_error_cmp(t_info *cur, t_info *next)
{
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
		return (ls_error_cmp(cur, next));
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
		return (ls_error_cmp(cur, next));
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
		return (ls_error_cmp(cur, next));
	else
	{
		if (cur->atime == next->atime)
			return (ft_strcmp(cur->name, next->name) < 0 ? 1 : 0);
		else
			return (cur->atime > next->atime ? 0 : 1);
	}
}

void		ls_sort(t_list **list, t_ls *ls)
{
	if (ls->flags[2])
		ft_lst_sort(list, ls_reverse_cmp, 0, (int)ft_lstcount(*list));
	else if (ls->flags[4])
		ft_lst_sort(list, ls_time_cmp, 0, (int)ft_lstcount(*list));
	else
		ft_lst_sort(list, ls_alpha_cmp, 0, (int)ft_lstcount(*list));
}
