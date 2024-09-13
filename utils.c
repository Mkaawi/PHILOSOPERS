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
	if (!ptr)
		error("malloc error");
	return (ptr);
}

size_t	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
