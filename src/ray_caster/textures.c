/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:31:41 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/22 15:25:58 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

int	get_texture_color(mlx_texture_t *tex, int x, int y)
{
	int			color;
	uint32_t	*pixels;
	int			agbr[4];

	if (!tex || x < 0 || y < 0 || x >= (int)tex->width || y >= (int)tex->height)
		return (0);
	pixels = (uint32_t *)tex->pixels;
	color = pixels[y * tex->width + x];
	agbr[0] = (color >> 24) & 0xFF;
	agbr[1] = (color >> 16) & 0xFF;
	agbr[2] = (color >> 8) & 0xFF;
	agbr[3] = (color)&0xFF;
	return (agbr[3] << 24 | agbr[2] << 16 | agbr[1] << 8 | agbr[0]);
}

double	get_tx(t_data *game, t_ray *ray, mlx_texture_t *tex)
{
	double	tx;

	tx = 0;
	if (ray->vert)
		return (fmodf(ray->ry * (tex->width / game->tile), tex->width));
	else
		tx = fmodf(ray->rx * (tex->width / game->tile), tex->width);
	if (game->tss == 1)
		tx = tex->width - tx;
	return (tx);
}

int	get_ty(int y, int start, int wall_height, mlx_texture_t *tex)
{
	int	tex_y;

	if (wall_height <= 0 || !tex)
		return (0);
	tex_y = (int)(((double)(y - start) / (double)wall_height) * tex->height);
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
		if (game->ray->rdx < 0)
			return (game->tw);
		else
			return (game->te);
	}
	else
	{
		if (game->ray->rdy < 0)
			return (game->tn);
		else
			return (game->tss = 1, game->ts);
	}
}

int	get_tex_px(t_data *game, int start, int wallheight, int y)
{
	int				tex_x;
	int				tex_y;
	int				color;
	mlx_texture_t	*tex;

	tex = choose_tex(game);
	tex_x = get_tx(game, game->ray, tex);
	tex_y = get_ty(y, start, wallheight, tex);
	color = get_texture_color(tex, tex_x, tex_y);
	return (color);
}
