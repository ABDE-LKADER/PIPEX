/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:37:35 by abadouab          #+#    #+#             */
/*   Updated: 2024/05/26 22:39:05 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

static t_allocate	**block_loc(void)
{
	static t_allocate	*collec = NULL;

	return (&collec);
}

void	*allocate(size_t count, size_t size)
{
	t_allocate **collec;
	t_allocate	*new;

	collec = block_loc();
	new = malloc(sizeof(t_allocate));
	if (!new)
		return (NULL);
	new->block = ft_calloc(count, size);
	if (!new->block)
		return (free(new), NULL);
	(TRUE) && (new->next = *collec, *collec = new);
	return (new->block);
}

void	cleanup(void)
{
	t_allocate	*set;
	t_allocate	*next;
	t_allocate	**collec;

	collec = block_loc();
	set = *collec;
	while (set)
	{
		next = set->next;
		if (set->block)
			free(set->block);
		(free(set), set = next);
	}
	*collec = NULL;
}
