

#include "ray_caster.h"

#include <math.h>
#include <stdio.h>
#include <string.h> 


void draw_line(t_data *game)
{
    uint32_t color = 0xFF0000FF;
    t_player *player = game->player;
    t_ray *ray = game->ray;
    double x_inc;
    double y_inc;
    double steps;
    double difx = (ray->rx - player->px);
    double dify = (ray->ry - player->py);
    // double slope = difx / dify;
    // if (difx > dify)
    // steps = difx;
    // else
    // steps = dify;
    steps = fmax(fabs(difx), fabs(dify));
    x_inc = difx / steps;
    y_inc = dify / steps;
    // if (steps < 0)
    // steps = -steps;
    // printf("x_inc %f, y_inc %f, steps %f\n", x_inc, y_inc, steps);
    if (game->player->px >= 0 && (int)game->player->px < game->win_width &&
        game->player->py >= 0 && (int)game->player->py < game->win_height &&
        game->ray->rx >= 0 && (int)game->ray->rx< game->win_width &&
        game->ray->ry >= 0 && (int)game->ray->ry < game->win_height)
    {
        int i = 1;
        while(i <= steps)
        {
        mlx_put_pixel(game->img, (int)(game->player->px + i * x_inc), (int)(game->player->py + i * y_inc), color);
            i++;
        }
    }
}

t_ray_dir ray_direction(t_ray *ray, int dir)
{
    if (dir == 1)
    {
    if (ray->ra > 0 && ray->ra < M_PI)
    return(printf("1\n"), DOWN);
    else
    return(printf("2\n"), UP);
    }
    else
    {
    if (ray->ra > M_PI / 2 && ray->ra < 3 * M_PI / 2)
    return(printf("3\n"), LEFT);
    else
    return(printf("4\n"), RIGHT);
    }
}

void draw_rays(t_data *game, t_player *player, t_ray *ray, t_map *map)
{
double ray_angle = player->pa;
int map_x = 0;
int map_y = 0;

ray->rx = player->px;
ray->ry = player->py;
    while (1)
    {
        if (ray_direction(ray, 1) == UP)
            map_y = (int)((ray->ry - 1) / 64);
        else
            map_y = (int)(ray->ry / 64);
        if (ray_direction(ray, 0) == LEFT)
            map_x = (int)((ray->rx - 1) / 64);
        else
            map_x = (int)(ray->rx / 64);
        // int map_x = (int)(ray->rx / 64);
        // int map_y = (int)(ray->ry / 64);
        printf("rx %d ry %d\n", (int)ray->rx, (int)ray->ry);
        printf("mx %d my %d\n", map_x, map_y);
        if (map_x >= 0 && map_y >= 0 && map_x <= map->mx && map_y <= map->my)
        {
        if (map->m[map_y][map_x] == '1')
            break;
        }
        else
        return;
        ray->rx += cos(ray_angle) * 0.5;
        ray->ry += sin(ray_angle) * 0.5;
    }
    draw_line(game);
}
