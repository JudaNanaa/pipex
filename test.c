#include "./includes/pipex.h"

int ft_nb_pipes(char **argv)
{
	int nb_args;
	int i;

	i = 0;
	nb_args = ft_double_tab_strlen(argv);
	nb_args -= 2;
	while (argv[i])
	{
		if (!strcmp(argv[i], "here_doc"))
		{
			nb_args -=2;
			i++;
		}
		i++;
	}
	if (strcmp(argv[1], "here_doc") != 0)
		nb_args--;
	nb_args--;
	return (nb_args);
}

int main(int argc, char **argv, char **envp)
{
	int i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}
