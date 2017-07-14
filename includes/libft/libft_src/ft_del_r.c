/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:53:01 by kmurray           #+#    #+#             */
/*   Updated: 2017/07/05 01:21:42 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_r(char **arr)
{
	int		i;
	char	**tmp;

	if (arr)
	{
		tmp = arr;
		i = -1;
		while (arr[++i])
			ft_strdel(&arr[i]);
		free(arr[i]);
		free(tmp);
	}
}