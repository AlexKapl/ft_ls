#include "ft_ls.h"

void		ls_list(t_info **info, t_ls *ls)
{
	t_list	*node;

	if (!(node = (t_list*)malloc(sizeof(t_list))))
		ls_errors(MLC_ERR, NULL);
	if (!ls->l)
	{
		(*info)->time = NULL;
		(*info)->perm = NULL;
	}
	node->content = (void*)*info;
	node->content_size = 0;
	node->next = NULL;
	ft_lst_push_back(&ls->list, node);
}

t_list		*ls_new_dir(t_info *info)
{
	t_list	*node;

	if (!(node = (t_list*)malloc(sizeof(t_list))))
		ls_errors(MLC_ERR, NULL);
	node->content = (void*)ft_strdup(info->path);
	node->content_size = 0;
	node->next = NULL;
	return (node);
}

void			ls_del_dirs(void *data, size_t size)
{
	char		*name;

	(void)size;
	name = (char*)data;
	if (name)
		free(name);
}

static void	ls_del(void *data, size_t size)
{
	t_info	*info;

	info = (t_info*)data;
	(void)size;
	if (info)
	{
		free(info->path);
		free(info->name);
		free(info);
	}
}

void		ls_clear(t_ls *ls, t_list **dirs)
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
		ft_lstdel(dirs, ls_del_dirs);
}
