#include "ft_ls.h"

static void			ls_print_xattr(t_info *info)
{
	ssize_t			i;
	ssize_t			ret;
	char			*str;

	i = 0;
	str = NULL;
	while (i < info->x_len)
	{
		if ((ret = getxattr(info->path, info->xattr + i,
							str, 0, 0, XATTR_NOFOLLOW)) < 0)
			return ;
		str = ft_strnew((size_t)ret);
		ret = getxattr(info->path, info->xattr + i,
					   str, (size_t)ret, 0, XATTR_NOFOLLOW);
		ft_printf("\t%s\t   %i\n", info->xattr + i, ret);
		i += ft_strlen(&info->xattr[i]) + 1;
		ft_memdel((void**)&str);
	}
}

static void			ls_print_info(t_ls *ls, t_info *in)
{
	char			*tmp;

	ft_printf("%s %*d ", in->perm, ls->width[0], in->links);
	ft_printf("%-*s  %-*s  ", ls->width[1], in->user, ls->width[2], in->group);
	if (in->major == -1)
		ft_printf("%*d", ls->width[3], in->size);
	else
		ft_printf("%*d, %*d", ls->width[4], in->major, ls->width[5], in->minor);
	ft_printf(" %s ", in->time);
	if (ls->p)
		ft_printf((*in->perm == 'd' ? "%s/" : "%s"), in->name);
	else
		ft_printf("%s", in->name);
	if (*in->perm == 'l')
	{
		tmp = ft_memalloc(1025);
		readlink(in->path, tmp, 1024);
		ft_printf(" -> %s", tmp);
		free(tmp);
	}
	ft_printf("\n");
	if (ls->dog)
		ls_print_xattr(in);
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
		if (ls->i)
			ft_printf("%*d ", ls->width[7], info->inode);
		if (ls->s)
			ft_printf(" %*d ", ls->width[6], info->blocks);
		if (ls->l)
			ls_print_info(ls, info);
		else
		{
			if (ls->p)
				ft_printf((*info->perm == 'd' ? "%s/\n" : "%s\n"), info->name);
			else
				ft_printf("%s\n", info->name);
		}
	}
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
	if (ls->l || ls->s)
		ls_count_size(ls);
}