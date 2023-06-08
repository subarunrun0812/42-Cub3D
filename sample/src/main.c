#include "sample.h"

void	window_reflesh(t_vars *vars, int width, int height)
{
	t_data	black_img;

	black_img.img = mlx_new_image(vars->mlx, width, height);
	black_img.addr = mlx_get_data_addr(black_img.img, \
	&black_img.bits_per_pixel, &black_img.line_length, &black_img.endian);
	mlx_put_image_to_window(vars->mlx, \
	vars->win, black_img.img, 0, 0);
}

int	render_next_frame(t_vars *vars)
{
  window_reflesh(vars, screenWidth, screenHeight);
  raycasting(vars);
  return (SUCCESS);
}

int main(void)
{
  t_vars *vars;
	vars = (t_vars *)malloc(sizeof(t_vars));

  vars->mlx = mlx_init();
  vars->win = mlx_new_window(vars->mlx, screenWidth, screenHeight, "so_long");
  raycasting(vars);
	mlx_loop_hook(vars->mlx, render_next_frame, vars);
  mlx_hook(vars->win, 2, 1L << 0, key_handle, vars);
	// mlx_hook(vars->win, 17, 0L, x_click_handle, vars);
	mlx_loop(vars->mlx);
}