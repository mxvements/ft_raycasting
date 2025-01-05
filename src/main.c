#include "raycasting.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = (y * game->size_line) + (x * game->bpp / 8);
	game->data[index] = color & 0xFF; //blue channel
	game->data[index + 1] = (color >> 8) & 0xFF; //green channel
	game->data[index + 2] = (color >> 16) & 0xFF; //red channel
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			put_pixel(x + i, y + j, color, game);
	}
}

static void draw_map(t_game *game)
{
	char **map = game->map;
	int color = 0x0000FF;
	for (int i = 0; map[i]; i++)
		for (int j = 0; map[i][j]; j++)
			if (map[i][j] == '1')
				draw_square(j * WALL_SIZE, i * WALL_SIZE, WALL_SIZE, color, game);

}

static char **init_map(void)
{
	char **map = calloc(10 + 1, sizeof(char *));
	map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
	map[10] =  NULL;
	return (map);

}

static void	init_game(t_game *game)
{
	init_player(&game->player);
	game->map = init_map();
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		fprintf(stderr, "Error: Failed to initialize MLX\n");
		exit(EXIT_FAILURE);
	}

	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "game");
	if (!game->win)
	{
		fprintf(stderr, "Error: Failed to create window\n");
		exit(EXIT_FAILURE);
	}

	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		fprintf(stderr, "Error: Failed to create image\n");
		exit(EXIT_FAILURE);
	}

	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	if (!game->data)
	{
		fprintf(stderr, "Error: Failed to get image data address\n");
		exit(EXIT_FAILURE);
	}
}

static void clean_img(t_game *game)
{
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			put_pixel(j, i, 0x00, game);
}

//raycasting on the minimap
bool touch_wall(float px, float py, t_game *game)
{
	int j = px / WALL_SIZE;
	int i = py / WALL_SIZE;

	if (game->map[i][j] == '1')
		return (true);
	return (false);
}

static void draw_axis(t_game *game, int color)
{
	t_player *player = &game->player;

	float ray_x = player->x + PLAYER_SIZE / 2;
	float ray_y = player->y + PLAYER_SIZE / 2;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);
	while (!touch_wall(ray_x, ray_y, game))
	{
		put_pixel(ray_x, ray_y, color, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
}

static void draw_line(t_player *player, t_game *game, float start_x, int color)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x + PLAYER_SIZE / 2;
	float ray_y = player->y + PLAYER_SIZE / 2;
	while (!touch_wall(ray_x, ray_y, game))
	{
		put_pixel(ray_x, ray_y, color, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
}

static void draw_camera(t_game *game)
{
	t_player *player = &game->player;
	
	float fraction = PI / 3 / WIDTH;
	float start_x = player->angle - PI / 6;
	int i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, 0x772200);
		start_x += fraction;
		i++;
	}
}

static int draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(player);
	clean_img(game);
	draw_square(player->x, player->y, PLAYER_SIZE, 0x00FF00, game);
	draw_map(game);

	draw_camera(game);
	draw_axis(game, 0xFF1100);

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);

}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_game game;

	init_game(&game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}