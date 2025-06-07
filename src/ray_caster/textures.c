/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:31:41 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/07 16:04:24 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

int	get_texture_color(mlx_texture_t *tex, int x, int y)
{
	int32_t	*pixels;
	int		color;
	int		a;
	int		b;
	int		g;
	int		r;

	if (!tex || x < 0 || y < 0 || x >= (int)tex->width || y >= (int)tex->height)
		return (0);
	pixels = (int32_t *)tex->pixels;
	color = pixels[y * tex->width + x];
	a = (color >> 24) & 0xFF;
	b = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	r = (color)&0xFF;
	return (r << 24 | g << 16 | b << 8 | a);
}

double	get_tx(t_ray *ray, mlx_texture_t *tex)
{
	if (ray->vert)
		return (fmodf(ray->ry * (tex->width / 64), tex->width));
	return (fmodf(ray->rx * (tex->width / 64), tex->width));
}

int	get_ty(int y, int wall_top, int wall_height, mlx_texture_t *tex)
{
	int	tex_y;

	if (wall_height <= 0 || !tex)
		return (0);
	tex_y = (int)(((double)(y - wall_top) / (double)wall_height) * tex->height);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)tex->height)
		tex_y = tex->height - 1;
	return (tex_y);
}

mlx_texture_t	*choose_tex(t_data *game)
{
	if (game->ray->vert == 1)
	{
		if (game->ray->rdx > 0)
			return (game->tw);
		else
			return (game->te);
	}
	else
	{
		if (game->ray->rdy > 0)
			return (game->tn);
		else
			return (game->ts);
	}
}
