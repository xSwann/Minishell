
#include "built_ins.h"
#include <string.h>

t_env    *ft_pwd(t_env *env, int *count)
{
    char buffer[4097];
    char *cwd;

    cwd = getcwd(buffer, 4097);
    if (cwd == NULL)
        perror("getcwd");
    else
        printf("%s\n", buffer);
    return (ft_export(env, count, "EXIT_CODE=0"));
}
