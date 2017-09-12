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

static void			ls_file_info(mode_t mode, t_info *info)
{
	info->perm[0] = (char)(S_ISREG(mode) ? '-' : info->perm[0]);
	info->perm[0] = (char)(S_ISDIR(mode) ? 'd' : info->perm[0]);
	info->perm[0] = (char)(S_ISLNK(mode) ? 'l' : info->perm[0]);
	info->perm[0] = (char)(S_ISCHR(mode) ? 'c' : info->perm[0]);
	info->perm[0] = (char)(S_ISBLK(mode) ? 'b' : info->perm[0]);
	info->perm[0] = (char)(S_ISFIFO(mode) ? 'p' : info->perm[0]);
	info->perm[0] = (char)(S_ISSOCK(mode) ? 's' : info->perm[0]);
	info->perm[1] = (char)(mode & S_IRUSR ? 'r' : '-');
	info->perm[2] = (char)(mode & S_IWUSR ? 'w' : '-');
	info->perm[3] = ls_ex_perm(mode, 0);
	info->perm[4] = (char)(mode & S_IRGRP ? 'r' : '-');
	info->perm[5] = (char)(mode & S_IWGRP ? 'w' : '-');
	info->perm[6] = ls_ex_perm(mode, 1);
	info->perm[7] = (char)(mode & S_IROTH ? 'r' : '-');
	info->perm[8] = (char)(mode & S_IWOTH ? 'w' : '-');
	info->perm[9] = ls_ex_perm(mode, 2);
}

static void		ls_check_blocks_width(t_ls *ls, t_info *info)
{
	int			i;

	if (info->major == -1)
	{
		i = ft_intlen(info->size);
		ls->width[3] = (ls->width[3] < i ? i : ls->width[3]);
	}
	else
	{
		i = ft_intlen(info->major);
		ls->width[4] = (ls->width[4] < i ? i : ls->width[4]);
		i = ft_intlen(info->minor);
		ls->width[5] = (ls->width[5] < i ? i : ls->width[5]);
		i = ft_intlen(info->major) + ft_intlen(info->minor) + 2;
		ls->width[3] = (ls->width[3] < i ? i : ls->width[3]);
	}
}

static void		ls_check_width(t_ls *ls, t_info *info)
{
	int			i;

	if (ls->i)
	{
		i = ft_intlen(info->inode);
		ls->width[7] = (ls->width[7] < i ? i : ls->width[7]);
	}
	if (ls->s)
	{
		i = ft_intlen(info->blocks);
		ls->width[6] = (ls->width[6] < i ? i : ls->width[6]);
	}
	if (!ls->l)
		return ;
	i = ft_intlen(info->links);
	ls->width[0] = (ls->width[0] < i ? i : ls->width[0]);
	i = (int)ft_strlen(info->user);
	ls->width[1] = (ls->width[1] < i ? i : ls->width[1]);
	i = (int)ft_strlen(info->group);
	ls->width[2] = (ls->width[2] < i ? i : ls->width[2]);
	ls_check_blocks_width(ls, info);
}

void			ls_long_info(t_ls *ls, t_info *info, t_stat *stat)
{
	if (ls-> k)
		info->blocks = ls_find_kb(info->size);
	if (!ls->l)
	{
		ls_check_width(ls, info);
		return ;
	}
	info->perm = ft_strnew(11);
	ls_file_info(info->mode, info);
	if (*info->perm == 'b' || *info->perm == 'c')
	{
		info->major = major(stat->st_rdev);
		info->minor = minor(stat->st_rdev);
	}
	else
	{
		info->major = -1;
		info->minor = -1;
	}
	ls_check_width(ls, info);
}

