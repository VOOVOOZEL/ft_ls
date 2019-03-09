#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "./ft_printf/printf/libftprintf.h" 
#define ALF "-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1"
typedef struct  dirent	t_dir;

typedef struct winsize	t_win;

typedef struct          s_ls
{
    int                 R;
    int                 l;
    int                 a;
    int                 r;
    int                 t;
    int                 dash;
    char                **path;
    char                **files;
	char				***table;
}                       t_ls;