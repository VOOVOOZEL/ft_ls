# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <limits.h>
# include <sys/ioctl.h>
#include "./ft_printf/printf/libftprintf.h" 
#define ALF "-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1"

typedef struct dirent	t_dir;
typedef struct winsize	t_win;
typedef struct stat		t_stat;
typedef struct dirent	t_dir;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct          s_ls
{
	int					one;
    int                 R;
    int                 l;
    int                 a;
    int                 r;
    int                 t;
	int					l_f;
    int                 dash;
    char                **path;
    char                **files;
	char				***table;
	char				**times;
	char				**acc_right;
	char				**sizes;
	char				**owner;
	char				**group;
	char				**hd_links;
	char				**r_path;
	int					block;
}                       t_ls;

typedef struct 			s_date
{
	char		month[4];
	char		day[3];
	char		time[6];
}						t_date;

