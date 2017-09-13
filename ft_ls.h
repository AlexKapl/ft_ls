/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 21:12:21 by akaplyar          #+#    #+#             */
/*   Updated: 2017/09/12 21:13:21 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <sys/acl.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

# define OPT_ERR 0
# define MLC_ERR 1

typedef struct stat		t_stat;
typedef struct dirent	t_dir;

typedef struct		s_ls_info
{
	int				err;
	int				major;
	int				minor;
	long			sec;
	char			*path;
	char			*name;
	char			*time;
	char			*perm;
	char			*user;
	char			*group;
	char			*xattr;
	ssize_t			x_len;
	mode_t			mode;
	off_t			size;
	ino_t			inode;
	nlink_t			links;
	blkcnt_t		blocks;
	time_t			t_time;
}					t_info;

typedef struct		s_ls
{
	int				br;
	int				a;
	int				cu;
	int				f;
	int				i;
	int				k;
	int				l;
	int				n;
	int				p;
	int				r;
	int				s;
	int				t;
	int				dog;
	int				width[8];
	int				opts[3];
	t_list			*list;
}					t_ls;

int					ls_find_kb(off_t size);
void				ls_params(t_ls *ls);
void				ls_count_size(t_ls *ls);
void				ls_del(void *data, size_t size);
void				ls_list(t_info **info, t_ls *ls);
void				ls_sort(t_list **list, t_ls *ls);
void				ls_clear(t_ls *ls, t_list **dirs);
void				ls_print_dir(t_ls *ls, char *dir);
void				ls_errors(int errnum, char *invalid);
void				ls_file_print(t_info *info, t_ls *ls);
void				ls_readdir(t_list **dir_list, t_ls *ls);
void				ls_file_list(t_ls *ls, char *dir, char *name);
void				ls_long_info(t_ls *ls, t_info *info, t_stat *stat);
void				ls_parse_time(t_ls *ls, t_info *info, t_stat *stat);
char				ls_manage_xattr(t_info *info);
char				*ls_dir_path(char *dir, char *name);
t_list				*ls_new_dir(t_info *info);

#endif
