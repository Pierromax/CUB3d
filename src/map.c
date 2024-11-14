/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:52:04 by ple-guya          #+#    #+#             */
/*   Updated: 2024/11/14 17:14:35 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

char	**get_map(t_cub *cub, char *line)
{
	if (!line)
		return (NULL);
	if (!cub->no || !cub->ne || !cub->se || cub->so)
		return (NULL);
	return(NULL);
}