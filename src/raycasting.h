#ifndef RAYCASTING_H
# define RAYCASTING_H	

# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# define WIDTH 450
# define HEIGHT 300
# define PLAYER_SIZE 10
# define WALL_SIZE 30

# define PI 3.14159265359

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

typedef struct s_player
{
    float x;
    float y;
    float angle;

    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;

    bool left_rotate;
    bool right_rotate;
}   t_player;

typedef struct s_game
{
	void *mlx;
	void *win;
	void *img;

	char *data;
	int bpp;
	int size_line;
	int endian;

	char **map;
	t_player player;

}	t_game;

void init_player(t_player *player);
int	key_press(int keycode, t_player *player);
int	key_release(int keycode, t_player *player);
void move_player(t_player *player);
#endif