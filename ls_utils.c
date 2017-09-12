/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 21:17:35 by akaplyar          #+#    #+#             */
/*   Updated: 2017/09/12 21:18:15 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define HALF 15778463
#define DIFF ft_abs(time(NULL) - info->t_time)

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

char				ls_manage_xattr(t_info *info)
{
	acl_t		acl;

	info->xattr = (char*)ft_memalloc(10101);
	info->x_len = 10100;
	acl = acl_get_link_np(info->path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, NULL))
	{
		acl_free(acl);
		acl = NULL;
	}
	if ((info->x_len = listxattr(info->path, info->xattr,
					(size_t)info->x_len, XATTR_NOFOLLOW)) > 0)
		return ('@');
	else
	{
		info->x_len = 0;
		return ((char)(acl ? '+' : ' '));
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
	int				size;
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

void				ls_clear(t_ls *ls, t_list **dirs)
{
	ls->width[0] = 0;
	ls->width[1] = 0;
	ls->width[2] = 0;
	ls->width[3] = 0;
	ls->width[4] = 0;
	ls->width[5] = 0;
	ls->width[6] = 0;
	ls->width[7] = 0;
	if (ls->list)
		ft_lstdel(&ls->list, ls_del);
	if (dirs && (ls->br || ls->opts[0]))
	{
		ls->opts[0] = 0;
		ls_readdir(dirs, ls);
	}
	else
		ft_lstdel(dirs, ls_del);
}
