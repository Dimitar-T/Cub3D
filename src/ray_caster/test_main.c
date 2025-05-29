
#include "ray_caster.h"

#include <math.h>
#include <stdio.h>
#include <string.h> 

void draw_player(t_data *game)
{
    uint32_t color = 0xFF0000FF;
    if (game->player->px >= 0 && (int)game->player->px < game->win_width &&
        game->player->py >= 0 && (int)game->player->py < game->win_height)
    {
        mlx_put_pixel(game->img, (int)game->player->px, (int)game->player->py , color);
        mlx_put_pixel(game->img, ((int)game->player->px) + 1, (int)game->player->py, color);
        mlx_put_pixel(game->img, ((int)game->player->px) - 1, (int)game->player->py, color);
        mlx_put_pixel(game->img, (int)game->player->px, (int)game->player->py + 1, color);
        mlx_put_pixel(game->img, (int)game->player->px, (int)game->player->py - 1, color);
    }
}

void move_player(mlx_key_data_t data, t_player *player)
{
    if (data.key == MLX_KEY_W)
    {
    player->px += player->pdx * player->speed;
    player->py += player->pdy * player->speed;
    }
    else if (data.key == MLX_KEY_S)
    {
    player->px -= player->pdx * player->speed;
    player->py -= player->pdy * player->speed;
    }
    else if (data.key == MLX_KEY_A)
    {
    player->px += cos(player->pa - M_PI / 2) * player->speed;
    player->py += sin(player->pa - M_PI / 2) * player->speed;
    }
    else if (data.key == MLX_KEY_D)
    {
    player->px += cos(player->pa + M_PI / 2) * player->speed;
    player->py += sin(player->pa + M_PI / 2) * player->speed;
    }
}

void change_direction(mlx_key_data_t data, t_player *player)
{
    if (data.key == MLX_KEY_RIGHT)
    {
        player->pa +=  player->speed / 10;
        if (player->pa < 0)
        player->pa += 2 * M_PI;
        if (player->pa >= 2 * M_PI)
        player->pa -= 2 * M_PI;
        player->pdx = cos(player->pa);
        player->pdy = sin(player->pa);
    }
    else if (data.key == MLX_KEY_LEFT)
    {
        player->pa -= player->speed / 10;
        if (player->pa < 0)
        player->pa += 2 * M_PI;
        if (player->pa >= 2 * M_PI)
        player->pa -= 2 * M_PI;
        player->pdx = cos(player->pa);
        player->pdy = sin(player->pa);
    }
}

void key_callback(mlx_key_data_t data, void *param)
{
    t_data  *game = (t_data*)param;
    t_player *player = game->player;
    
    if (data.action == MLX_PRESS || data.action == MLX_REPEAT)
    {
        if (data.key == MLX_KEY_ESCAPE)
        mlx_close_window(game->mlx);
        else if (data.key == MLX_KEY_W || data.key == MLX_KEY_S
                || data.key == MLX_KEY_A || data.key == MLX_KEY_D)
        move_player(data, player);
        else if (data.key == MLX_KEY_RIGHT || data.key == MLX_KEY_LEFT)
        change_direction(data, player);
        draw_player(game);
        // draw_rays(game, player, game->ray, game->map);
    }
}

void put_img(t_data *game)
{
    mlx_texture_t *walls;
    mlx_image_t *wallss;
    int imgx = game->win_width / game->map->mx;
    int imgy = game->win_height / game->map->my;
    
    walls = mlx_load_png("../../textures/greendragon.png");
    wallss = mlx_texture_to_image(game->mlx, walls);
    mlx_delete_texture(walls);
    mlx_resize_image(wallss, game->win_width / game->map->mx, game->win_height / game->map->my);
    int i = 0;
    while(i < game->map->my)
    {
        int j = 0;
        while(game->map->m[i][j] != '\0')
        {
        if (game->map->m[i][j] == '1')
        mlx_image_to_window(game->mlx, wallss, j * imgx, i * imgy);
        j++;
        }
        i++;
    }   
}

int main(int argc, char *argv[])
{
    t_data  *game = init_game(argv[1]);
    put_img(game);
    draw_player(game);
    mlx_key_hook(game->mlx, key_callback, game);
	mlx_loop(game->mlx);
    free(game->ray);
    free(game->map->m);
    free(game->map);
    free(game->player);
    free(game);
    return(0);
}