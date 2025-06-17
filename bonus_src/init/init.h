# ifndef INIT_H
# define INIT_H

#include "../cub3d.h"

typedef struct s_player
{
    double             px;
    double             py;
    double             pdx;
    double             pdy;
    double             pa;
    int                xo;
    int                yo;
    double             speed;
}               t_player;

typedef struct s_ray
{
    double             rx;
    double             ry;
    double             ra;
    double             rdx;
    double             rdy;
    int                vert;
    double             mm_rx;
    double             mm_ry;

}               t_ray;

typedef struct s_map
{
    char               **m;
    double             mx;
    double             my;
}               t_map;

// typedef struct s_assets
// {
//     mlx_image_t     *s1;
//     mlx_image_t     *s2;
//     mlx_image_t     *s3;
//     mlx_image_t     *s4;
// }               t_assets;

// typedef struct s_sprite
// {
//     int             id;
//     t_assets        *ass;
//     double          sx;
//     double          sy;
// }               t_sprite;

typedef struct s_data
{
    mlx_t           *mlx;
    t_player        *player;
    t_ray           *ray;
    t_map           *map;
    char            **m;
    mlx_image_t     *img;
    mlx_texture_t   *tn;
    mlx_texture_t   *ts;
    mlx_texture_t   *te;
    mlx_texture_t   *tw;
    mlx_texture_t   *d;
    int             door;
    int             sky_color;
    int             floor;
    int             win_width;
    int             win_height;
    int             check_list[6];
    // t_sprite        *sprites[50];
}               t_data;

t_data *init_game(t_data *game);

#endif