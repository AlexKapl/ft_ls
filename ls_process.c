#include "ft_ls.h"

void		ls_file_list(t_ls *ls, char *dir, char *name)
{
	char	*tmp;
	t_stat	stat;
	t_info	*info;

	if (!(info = (t_info*)malloc(sizeof(t_info))))
		exit(123);
	info->err = 0;
	if (!(info->path = ft_strdup(dir)) || !(info->name = ft_strdup(name)))
		exit(123);
	tmp = ft_dir_path(dir, name);
	if (!lstat(tmp, &stat))
	{
		info->mode = stat.st_mode;
		info->links = stat.st_nlink;
		info->user = stat.st_uid;
		info->group = stat.st_gid;
		info->size = stat.st_size;
		info->blocks = stat.st_blocks;
		info->atime = stat.st_mtimespec.tv_sec;
		ls_check_width(ls, info);
	}
	else
		info->err = errno;
	free(tmp);
	ls_list(info, ls);
}

static void		ls_print_dir(t_ls *ls, char *dir, int size)
{
	char	*tmp;
	t_info	*info;
	t_list	*list;

	if (strcmp(dir, "."))
	{
		if (!strncmp(dir, "./..", 4))
		{
			ft_printf("\n%s:\n", (tmp = ft_strsub(dir, 2, ft_strlen(dir))));
			free(tmp);
		}
		else
			ft_printf("\n%s:\n", dir);
	}
	if (ls->flags[0])
	{
		list = ls->list;
		while (list)
		{
			info = (t_info *)list->content;
			size += info->blocks;
			list = list->next;
		}
		ft_printf("total %d\n", size);
	}
}

static void	ls_iterate(t_ls *ls)
{
	t_info	*info;
	t_list	*dirs;
	t_list	*list;

	dirs = NULL;
	ls_sort(&ls->list, ls);
	list = ls->list;
	while (list)
	{
		info = (t_info *)list->content;
		ls_file_print(info, ls);
		if (info->err == 0 && S_ISDIR(info->mode) &&
			strcmp(info->name, ".") && strcmp(info->name, ".."))
		{
			ft_lst_push_back(&dirs, ls_new_dir(info));
		}
		list = list->next;
	}
	ls_clear(ls, dirs);
}

void		ls_readdir(t_list *dirs, t_ls *ls)
{
	DIR		*dir;
	t_dir	*file;

	while (dirs)
	{
		if ((dir = opendir((char*)dirs->content)))
		{
			while ((file = readdir(dir)))
			{
				if (file->d_name[0] == '.')
				{
					if (ls->flags[1])
						ls_file_list(ls, dirs->content, file->d_name);
				}
				else
					ls_file_list(ls, dirs->content, file->d_name);
			}
			ls_print_dir(ls, dirs->content, 0);
			ls_iterate(ls);
		}
		else
			ft_printf("ft_ls: %s: %s\n", dirs->content, strerror(errno));
		dirs = dirs->next;
	}
}

void		ls_params(t_ls *ls)
{
	t_info	*info;
	t_list	*dirs;
	t_list	*list;
	char	*tmp;

	dirs = NULL;
	ls_sort(&ls->list, ls);
	list = ls->list;
	while (list)
	{
		info = (t_info *)list->content;
		if (info->err || !S_ISDIR(info->mode))
			ls_file_print(info, ls);
		else if (info->err == 0 && S_ISDIR(info->mode))
		{
			tmp = ft_dir_path(info->path, info->name);
			ft_lst_push_back(&dirs, ft_lstnew((void *)tmp, ft_strlen(tmp) + 1));
			free(tmp);
		}
		list = list->next;
	}
	ls_clear(ls, dirs);
}