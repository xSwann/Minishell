
#include "../includes/built_ins.h"
#include <string.h>

int    ft_pwd(t_env **env)
{
    char buffer[4097];
    char *cwd;

    cwd = getcwd(buffer, 4097);
    if (cwd == NULL)
        perror("getcwd");
    else
        printf("%s\n", buffer);
    ft_export(env, "EXIT_CODE=0");
    return (0);
}
