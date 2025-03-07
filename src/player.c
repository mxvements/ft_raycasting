#include "raycasting.h"

void init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;

	player->left_rotate = false;
	player->right_rotate = false;
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void move_player(t_player *player)
{
	int speed = 5;
	float angle_speed = PI/16;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);

	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle > 2*PI)
		player->angle = 2 * PI;

	if (player->key_up)
	{
		player->x -= speed * cos_angle;
		player->y -= speed * sin_angle;
	}
	if (player->key_down)
	{
		player->x += speed * cos_angle;
		player->y += speed * sin_angle;
	}
	if (player->key_left)
	{
		player->x += speed * cos(player->angle + PI / 2);
		player->y += speed * sin(player->angle + PI / 2);
	}
	if (player->key_right)
	{
		player->x -= speed * cos(player->angle + PI / 2);
		player->y -= speed * sin(player->angle + PI / 2);
	}
}