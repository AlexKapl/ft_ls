#ifndef FT_LS_H
#define FT_LS_H

# include "libft/libft.h"
# include "sys/types.h"
# include "sys/stat.h"
# include "dirent.h"
# include "string.h"
# include "errno.h"
# include "time.h"
# include "pwd.h"
# include "grp.h"

# define OPT_ERR 0

typedef struct stat t_stat;
typedef struct group t_grp;
typedef struct dirent t_dir;
typedef struct passwd t_pass;

typedef struct		s_ls_info
{
	int				err;
	char			*path;
	char			*name;
	mode_t			mode;
	nlink_t			links;
	uid_t			user;
	gid_t			group;
	off_t			size;
	blkcnt_t		blocks;
	time_t			atime;
}					t_info;

typedef struct		s_ls
{
	int				flags[7];
	int				width[4];
	t_list			*list;
}					t_ls;

void				ls_params(t_ls *ls);
void				ls_list(t_info *info, t_ls *ls);
void				ls_clear(t_ls *ls, t_list *dirs);
void				ls_sort(t_list **list, t_ls *ls);
void				ls_readdir(t_list *dirs, t_ls *ls);
void				ls_file_print(t_info *info, t_ls *ls);
void				ls_check_width(t_ls *ls, t_info *info);
void				ls_file_list(t_ls *ls, char *dir, char *name);
t_list				*ls_new_dir(t_info *info);

#endif