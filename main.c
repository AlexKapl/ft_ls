#include "ft_ls.h"

static void		ls_bonus_flags(t_ls *ls, char c)
{
	if (c == 'c')
		ls->cu = 1;
	else if (c == 'u')
		ls->cu = 2;
	else if (c == 'f')
	{
		ls->f = 1;
		ls->a = 1;
	}
	else if (c == 'A')
		ls->a = 2;
	else if (c == 's')
		ls->s = 1;
	else if (c == 'i')
		ls->i = 1;
	else if (c == 'p')
		ls->p = 1;
	else if (c == 'k')
		ls->k = 1;
}

static void		ls_check_flags(t_ls *ls, int *i, int ac, char **av)
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
			else if (*(av[*i]) == 'r')
				ls->r = 1;
			else if (*(av[*i]) == 'R')
				ls->br = 1;
			else if (*(av[*i]) == 't')
				ls->t = 1;
			else
				ls_bonus_flags(ls, *(av[*i]));
			av[*i] += 1;
		}
	}
}
/// k? | c?+ | @? | u?+
/// p+ | f+ | A+ | i+ | s+

static void		ls_init(t_ls *ls)
{
	ls->list = NULL;
	ls->l = 0;
	ls->a = 0;
	ls->cu = 0;
	ls->f = 0;
	ls->i = 0;
	ls->k = 0;
	ls->p = 0;
	ls->r = 0;
	ls->s = 0;
	ls->t = 0;
	ls->br = 0;
	ls->opts[0] = 0;
	ls->opts[1] = 0;
	ls->opts[2] = 0;
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
			list = ft_lstnew(av[i - 1], ft_strlen(av[i - 1]));
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
	ls_check_flags(&ls, &i, ac, av);
	ls_check_params(&ls, i, ac, av);
	return (0);
}