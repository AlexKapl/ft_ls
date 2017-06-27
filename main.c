#include "ft_ls.h"

void		ls_errors(int errnum, char *invalid)
{
	if (errnum == OPT_ERR)
		ft_printf("ft_ls: illegal option -- %.1s\n%s", invalid,
								"usage: ft_ls [-Ralrt] [file ...]\n");
	exit(errnum);
}

static void	ls_check_flags(t_ls *ls, int *i, int ac, char **av)
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
			else
				ls_errors(OPT_ERR, av[*i]);
			av[*i] += 1;
		}
	}
}

static void	ls_init(t_ls *ls)
{
	ls->list = NULL;
	ls->width[0] = 0;
	ls->width[1] = 0;
	ls->width[2] = 0;
	ls->width[3] = 0;
	ls->flags[0] = 0;
	ls->flags[1] = 0;
	ls->flags[2] = 0;
	ls->flags[3] = 0;
	ls->flags[4] = 0;
	ls->flags[5] = 1;
	ls->flags[6] = 0;
}

int			main(int ac, char **av)
{
	int		i;
	t_ls	ls;

	i = 0;
	ls_init(&ls);
	ls_check_flags(&ls, &i, ac, av);
	if (i == ac)
		ls_readdir(ft_lstnew((void*)".", 2), &ls);
	else
	{
		while (i < ac)
		{
			ls_file_list(&ls, ".", av[i]);
			i++;
		}
		if (ft_lstcount(ls.list) == 1)
			ls.flags[6] = 1;
		ls_params(&ls);
	}
	return (0);
}