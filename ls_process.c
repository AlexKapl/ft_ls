/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 21:17:00 by akaplyar          #+#    #+#             */
/*   Updated: 2017/09/12 21:17:00 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_file_list(t_ls *ls, char *dir, char *name)
{
	t_stat	stat;
	t_info	*info;

	if (!(info = (t_info*)malloc(sizeof(t_info))) ||
		(!(info->path = ls_dir_path(dir, name)) ||
			!(info->name = ft_strdup(name))))
		ls_errors(MLC_ERR, NULL);
	if (!lstat(info->path, &stat))
	{
		info->err = 0;
		info->r = ls->r;
		info->mode = stat.st_mode;
		info->inode = stat.st_ino;
		info->size = stat.st_size;
		info->links = stat.st_nlink;
		info->blocks = stat.st_blocks;
		ls_parse_time(ls, info, &stat);
		ls_long_info(ls, info, &stat);
	}
	else
		info->err = errno;
	ls_list(&info, ls);
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
			ft_strcmp(info->name, ".") && ft_strcmp(info->name, ".."))
			ft_lst_push_back(&dirs, ls_new_dir(info));
		list = list->next;
	}
	ls_clear(ls, &dirs);
}

static void	ls_readfile(t_ls *ls, DIR *dir, char *path)
{
	t_dir	*file;

	while ((file = readdir(dir)))
	{
		if (file->d_name[0] == '.')
		{
			if (ft_strequ(file->d_name, ".") || ft_strequ(file->d_name, ".."))
			{
				if (ls->a == 1)
					ls_file_list(ls, path, file->d_name);
			}
			else if (ls->a)
				ls_file_list(ls, path, file->d_name);
		}
		else
			ls_file_list(ls, path, file->d_name);
	}
}

void		ls_readdir(t_list **dir_list, t_ls *ls)
{
	DIR		*dir;
	t_list	*dirs;

	dirs = *dir_list;
	while (dirs)
	{
		if ((dir = opendir((char*)dirs->content)))
		{
			ls_readfile(ls, dir, dirs->content);
			ls_print_dir(ls, dirs->content);
			ls_iterate(ls);
			closedir(dir);
		}
		else
			ft_printf("ft_ls: %s: %s\n", dirs->content, strerror(errno));
		dirs = dirs->next;
	}
	ft_lstdel(dir_list, ls_del);
}

void		ls_params(t_ls *ls)
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
		if (info->err || !S_ISDIR(info->mode))
			ls_file_print(info, ls);
		else if (info->err == 0 && S_ISDIR(info->mode))
			ft_lst_push_back(&dirs, ls_new_dir(info));
		list = list->next;
	}
	ls_clear(ls, &dirs);
}
