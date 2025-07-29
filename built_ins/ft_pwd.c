
#include "../includes/built_ins.h"
#include <string.h>

char	*get_pwd()
{
	char	buffer[4097];
	char	*cwd;

    cwd = getcwd(buffer, 4097);
    if (cwd == NULL)
		return (NULL);
	return (ft_strdup(cwd));
}

int	ft_pwd(t_env **env)
{
	char	*pwd;
	char	buffer[4097];

	pwd = get_env(*env, "PWD");
	if (pwd && access(pwd, F_OK) == 0)
		printf("%s\n", pwd);
	else
	{
		if (getcwd(buffer, sizeof(buffer)) == NULL)
			perror("getcwd");
		else
			printf("%s\n", buffer);
	}
	ft_export(env, "EXIT_CODE=0");
	return (0);
}
