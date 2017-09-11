#include "ft_ls.h"

void			ls_errors(int errnum, char *invalid)
{
	if (errnum == OPT_ERR)
		ft_printf("{fd}ft_ls: illegal option -- %.1s\n%s{eofd}", 2, invalid,
								"usage: ft_ls [-Ralrt] [file ...]\n");
	else if (errnum == MLC_ERR)
		ft_printf("{fd}Error: can't allocate memory\n{eofd}", 2);
	exit(errnum);
}

static void		ls_check_flags(t_ls *ls, int *i, int ac, char **av)
{
	while (++*i < ac && av[*i][0] == '-')
	{
		av[*i] += 1;
		while (*(av[*i]))
		{
			if (*(av[*i]) == 'l')
				ls->flags[0] = 1;
			else if (*(av[*i]) == 'a')
				ls->flags[1] = 1;
			else if (*(av[*i]) == 'r')
				ls->flags[2] = 1;
			else if (*(av[*i]) == 'R')
				ls->flags[3] = 1;
			else if (*(av[*i]) == 't')
				ls->flags[4] = 1;
			else if (*(av[*i]) != '1')
				ls_errors(OPT_ERR, av[*i]);
			av[*i] += 1;
		}
	}
}

static void		ls_init(t_ls *ls)
{
	ls->list = NULL;
	ls->opts[0] = 0;
	ls->opts[1] = 0;
	ls->opts[2] = 0;
	ls->width[0] = 0;
	ls->width[1] = 0;
	ls->width[2] = 0;
	ls->width[3] = 0;
	ls->flags[0] = 0;
	ls->flags[1] = 0;
	ls->flags[2] = 0;
	ls->flags[3] = 0;
	ls->flags[4] = 0;
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