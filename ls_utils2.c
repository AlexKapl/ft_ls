#include "ft_ls.h"

# define HALF 15778463
# define DIFF ft_abs(time(NULL) - info->t_time)

void			ls_errors(int errnum, char *invalid)
{
	if (errnum == OPT_ERR)
		ft_printf("{fd}ft_ls: illegal option -- %.1s\n%s{eofd}", 2, invalid,
				  "usage: ft_ls [-ARacfilrstu1] [file ...]\n");
	else if (errnum == MLC_ERR)
		ft_printf("{fd}Error: can't allocate memory\n{eofd}", 2);
	exit(errnum);
}

char			*ls_dir_path(char *dir, char *name)
{
	char		*tmp;

	if (ft_strequ(dir, ".") || ft_strequ(name, "/"))
		return (ft_strdup(name));
	else
	{
		tmp = ft_strjoin(dir, "/");
		tmp = ft_strmake(&tmp, &name, 1);
		return (tmp);
	}
}

void				ls_parse_time(t_ls *ls, t_info *info, t_stat *stat)
{
	char			*tmp;

	if (!ls->cu)
		info->t_time = stat->st_mtime;
	else
		info->t_time = (ls->cu == 1 ? stat->st_ctime : stat->st_atime);
	if (!ls->cu)
		info->sec = stat->st_mtimespec.tv_nsec;
	else
		info->sec = (ls->cu == 1 ?
					 stat->st_ctimespec.tv_nsec : stat->st_atimespec.tv_nsec);
	if (ls->l)
	{
		tmp = ctime(&info->t_time);
		if (DIFF > HALF)
		{
			info->time = ft_strsub(tmp, 4, 7);
			tmp = ft_strsub(tmp, 19, 5);
			info->time = ft_strmake(&info->time, &tmp, 3);
		}
		else
			info->time = ft_strsub(tmp, 4, 12);
	}
}

int					ls_find_kb(off_t size)
{
	int				i;
	int				s;

	i = 0;
	s = 0;
	while (s < size)
	{
		s += 1024;
		i++;
	}
	return (i);
}

void				ls_count_size(t_ls *ls)
{
	int 			size;
	t_info			*info;
	t_list			*list;

	size = 0;
	list = ls->list;
	while (list)
	{
		info = (t_info *)list->content;
		size += (ls->k ? info->size : info->blocks);
		list = list->next;
	}
	if (ls->k)
		size = ls_find_kb(size);
	ft_printf("total %d\n", size);
}
