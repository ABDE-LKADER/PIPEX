/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   |||||||.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: |||||||||| 19:18:37 by abadouab          #+#    #+#             */
/*   Updated: |||||||||| 09:50:45 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "mylib.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# define GRN "\033[1;32m"
# define YEL "\033[0;33m"
# define YLW "\033[1;33m"
# define RED "\033[1;31m"
# define RST "\033[0m"

void	error_handler(int set, char *ex);
void	first_child(int *pipe, char **av, char **env);
void	second_child(int *pipe, char **av, char **env);

#endif
