// int	handle_exact_hit(t_ray *ray, int yx)
// {
// 	if (yx == 0)
// 	{
// 		if (ray->rdy < 0)
// 			return (int)((ray->ry - 1) / 64);
// 		else
// 			return (int)(ray->ry / 64);
// 	}
// 	else
// 	{
// 		if (ray->rdx < 0)
// 			return (int)((ray->rx - 1) / 64);
// 		else
// 			return (int)(ray->rx / 64);
// 	}
// }

// we keep going further along direction x and y until we hit wall
// adds check for vertical/horizontal hit depending on prev
// void	draw_rays(t_ray *ray, t_map *map)
// {
// 	int		map_x;
// 	int		map_y;
// 	double	prev_rx;
// 	double	prev_ry;

// 	while (1)
// 	{
// 		prev_rx = ray->rx;
// 		prev_ry = ray->ry;
// 		ray->rx += ray->rdx * 0.005;
// 		ray->ry += ray->rdy * 0.005;
// 		map_x = handle_exact_hit(ray, 1);
// 		map_y = handle_exact_hit(ray, 0);
// 		if (map_x < 0 || map_y < 0 || map_x >= map->mx || map_y >= map->my)
// 			break ;
// 		if (map->m[map_y][map_x] == '1')
// 		{
// 			if ((int)(prev_rx / 64) != map_x)
// 				ray->vert = 1;
// 			else if ((int)(prev_ry / 64) != map_y)
// 				ray->vert = 0;
// 			break ;
// 		}
// 	}
// }