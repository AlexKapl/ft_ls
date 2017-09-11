#include "ft_ls.h"

static char			ls_ex_perm(mode_t mode, int type) {
	if (!type)
	{
		if (S_IXUSR & mode)
			return (char)(S_ISUID & mode ? 's' : 'x');
		else
			return (char)(S_ISUID & mode ? 'S' : '-');
	}
	else if (type == 1)
	{
		if (S_IXGRP & mode)
			return (char)(S_ISGID & mode ? 's' : 'x');
		else
			return (char)(S_ISGID & mode ? 'S' : '-');
	}
	else
	{
		if (S_IXOTH & mode)
			return (char)(S_ISVTX & mode ? 't' : 'x');
		else
			return (char)(S_ISVTX & mode ? 'T' : '-');
	}
}

static void			ls_file_info(mode_t mode, char *str)
{
	str[0] = (char)(S_ISREG(mode) ? '-' : str[0]);
	str[0] = (char)(S_ISDIR(mode) ? 'd' : str[0]);
	str[0] = (char)(S_ISLNK(mode) ? 'l' : str[0]);
	str[0] = (char)(S_ISCHR(mode) ? 'c' : str[0]);
	str[0] = (char)(S_ISBLK(mode) ? 'b' : str[0]);
	str[0] = (char)(S_ISFIFO(mode) ? 'p' : str[0]);
	str[0] = (char)(S_ISSOCK(mode) ? 's' : str[0]);
	str[1] = (char)(mode & S_IRUSR ? 'r' : '-');
	str[2] = (char)(mode & S_IWUSR ? 'w' : '-');
	str[3] = ls_ex_perm(mode, 0);
	str[4] = (char)(mode & S_IRGRP ? 'r' : '-');
	str[5] = (char)(mode & S_IWGRP ? 'w' : '-');
	str[6] = ls_ex_perm(mode, 1);
	str[7] = (char)(mode & S_IROTH ? 'r' : '-');
	str[8] = (char)(mode & S_IWOTH ? 'w' : '-');
	str[9] = ls_ex_perm(mode, 2);
}

static void			ls_print_info(t_info *info, t_ls *ls, char *str)
{
	t_pass			*pass;
	t_grp			*group;
	char			*tmp;

	pass = getpwuid(info->user);
	group = getgrgid(info->group);
	tmp = ft_strsub(ctime(&info->atime), 4, 12);
	ft_printf("%s  %*d ", str, ls->width[0], info->links);
	ft_printf("%*s  %*s  %*jd %s ", ls->width[1], pass->pw_name, ls->width[2],
			group->gr_name, ls->width[3], info->size, tmp);
	free(tmp);
	if (*str == 'l')
	{
		tmp = ft_memalloc(1025);
		readlink(info->path, tmp, 1024);
		ft_printf("%s -> %s\n", info->name, tmp);
		free(tmp);
	}
	else
		ft_printf("%s\n", info->name);
}

void				ls_file_print(t_info *info, t_ls *ls)
{
	char			*str;

	if (info->err)
	{
		ft_printf("ft_ls: %s: %s\n", info->name, (str = strerror(info->err)));
		free(str);
	}
	else
	{
		if (ls->flags[0])
		{
			str = ft_strnew(10);
			ls_file_info(info->mode, str);
			ls_print_info(info, ls, str);
			free(str);
		}
		else
			ft_printf("%s\n", info->name);
	}
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
		size += info->blocks;
		list = list->next;
	}
	ft_printf("total %d\n", size);
}

void				ls_print_dir(t_ls *ls, char *dir)
{
	if (ls->opts[1])
	{
		if (ls->opts[2])
			ft_printf("\n");
		else
			ls->opts[2] = 1;
		ft_printf("%s:\n", dir);
	}
	else
	{
		ls->opts[1] = 1;
		ls->opts[2] = 1;
	}
	if (ls->flags[0])
		ls_count_size(ls);
}