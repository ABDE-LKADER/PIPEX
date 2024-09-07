/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   |||||||||||                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: |||||||||| 19:18:37 by abadouab          #+#    #+#             */
/*   Updated: |||||||||| 09:50:45 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(char **env, char *cmd)
{
	char	**paths;

	if (!cmd || !env)
		return (NULL);
	while (*env && ft_strncmp("PATH", *env, ft_strlen("PATH")))
		env++;
	paths = ft_split(*env, ':');
	while (paths && *paths)
	{
		*paths = ft_strjoin(*paths, "/");
		*paths = ft_strjoin(*paths, cmd);
		if (!access(*paths, X_OK))
			return (*paths);
		paths++;
	}
	return (NULL);
}

static void    execute(char *arg, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(arg, ' ');
	if (!args)
		error_handler(2, "malloc");
	path = get_path(env, *args);
	if (!path)
		error_handler(1, *args);
	if (execve(path, args, env) == -1)
		error_handler(2, "execve");
}

void	first_child(int *pipe, char **av, char **env)
{
	pid_t	pid;
	int		infile;

	pid = fork();
	if (pid == -1)
		error_handler(2, "fork");
	if (pid == 0)
	{
		infile = open(av[1], O_RDONLY, 0444);
		if (infile == -1)
			error_handler(2, av[1]);
		if (dup2(infile, STDIN_FILENO) == -1
			|| dup2(pipe[1], STDOUT_FILENO) == -1)
			error_handler(2, "dup2");
		(close(pipe[0]), close(pipe[1]), close(infile));
		execute(av[2], env);
	}
}

void	second_child(int *pipe, char **av, char **env)
{
	pid_t	pid;
	int		outfile;

	pid = fork();
	if (pid == -1)
		error_handler(2, "fork");
	if (pid == 0)
	{
		outfile = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0666);
		if (outfile == -1)
			error_handler(2, av[4]);
		if (dup2(outfile, STDOUT_FILENO) == -1
			|| dup2(pipe[0], STDIN_FILENO) == -1)
			error_handler(2, "dup2");
		(close(pipe[0]), close(pipe[1]), close(outfile));
		execute(av[3], env);
	}
	(close(pipe[0]), close(pipe[1]));
	while (wait(NULL) != -1)
		;
}
