/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:48:59 by cviegas           #+#    #+#             */
/*   Updated: 2025/01/07 15:44:43 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	is_pressed(int key, t_cub *c)
{
	if (c->keys[key])
		return (1);
	return (0);
}

int	k_press(int keysym, t_cub *c)
{
	c->keys[keysym] = true;
	return (0);
}

int	k_release(int keysym, t_cub *c)
{
	c->keys[keysym] = false;
	return (0);
}

int	m_press(int button, t_cub *c)
{
	c->keys[button] = true;
	return (0);
}

int	m_release(int button, t_cub *c)
{
	c->keys[button] = false;
	return (0);
}
