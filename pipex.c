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

void	error_handler(int set, char *ex)
{
	if (set == 0)
	{
		ft_putstr_fd(YLW"Usage: "RST, 2);
		ft_putendl_fd("./pipex infile cmd1 cmd2 outfile", 2);
	}
	if (set != 0)
		ft_putstr_fd(RED"Error: "RST, 2);
	if (set == 1)
	{
		ft_putstr_fd(ex, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else if (set == 2)
		perror(ex);
	return (cleanup(), exit(EXIT_FAILURE));
}

int	main(int ac, char **av, char **env)
{
	int		tube[2];

	if (ac != 5)
		error_handler(0, NULL);
	if (pipe(tube) == -1)
		error_handler(2, NULL);
	first_child(tube, av, env);
	second_child(tube, av, env);
	return (cleanup(), EXIT_SUCCESS);
}
