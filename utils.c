/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 23:50:07 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/08 01:29:29 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	*pmalloc(int bytes)
{
	void	*ptr;
	
	ptr = malloc(bytes);
	if (!ptr == NULL)
		error("malloc error");
	return (ptr);
}
