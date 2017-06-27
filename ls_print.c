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
	str[0] = (char)(S_ISFIFO(mode) ? 'p' : str[0]);
	str[0] = (char)(S_ISCHR(mode) ? 'c' : str[0]);
	str[0] = (char)(S_ISDIR(mode) ? 'd' : str[0]);
	str[0] = (char)(S_ISBLK(mode) ? 'b' : str[0]);
	str[0] = (char)(S_ISREG(mode) ? '-' : str[0]);
	str[0] = (char)(S_ISLNK(mode) ? 'l' : str[0]);
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

static void			ls_user_info(t_info *info, t_ls *ls)
{
	t_pass			*pass;
	t_grp			*group;
	char			*time;

	pass = getpwuid(info->user);
	group = getgrgid(info->group);
	time = ft_strsub(ctime(&info->atime), 4, 12);
	ft_printf("%*s  %*s  %*jd %s ", ls->width[1], pass->pw_name, ls->width[2],
			group->gr_name, ls->width[3], info->size, time);
	free(time);
}

void				ls_file_print(t_info *info, t_ls *ls)
{
	char			*str;

	if (info->err)
		ft_printf("ft_ls: %s: %s\n", info->name, strerror(info->err));
	else
	{
		if (ls->flags[0])
		{
			str = ft_strnew(10);
			ls_file_info(info->mode, str);
			ft_printf("%s  %*d ", str, ls->width[0], info->links);
			free(str);
			ls_user_info(info, ls);
		}
		ft_printf("%s\n", info->name);
	}
}