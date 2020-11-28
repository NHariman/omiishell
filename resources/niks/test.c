#include <stdio.h>

int		main(int argc, char **argv, char **envp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	printf("Print argv:\n");
	while (argv[i] != (char *)0)
	{
		printf("argv[%i]: %s\n", i, argv[i]);
		i++;
	}
	printf("===========================\n");
	printf("Print envp:\n");
	while (envp[j] != (char *)0)
	{
		printf("envp[%i]: %s\n", j, envp[j]);
		j++;
	}
	return (0);
}
