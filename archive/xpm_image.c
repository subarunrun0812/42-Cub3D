#include <mlx.h>
#include <stdio.h>
#include <unistd.h>

typedef struct	s_vars	t_vars;
typedef struct	s_data	t_data;

struct	s_data {
	void			*img;
	unsigned int	*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
};

struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	data;
};

# define X_SIZE 640
# define Y_SIZE 480

int	main(void)
{
	t_vars	vars;
	t_data	image;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, X_SIZE, Y_SIZE, "xpm image");
	vars.data.img = mlx_new_image(vars.mlx, X_SIZE, Y_SIZE);
	vars.data.addr = (unsigned int *)mlx_get_data_addr(vars.data.img, &vars.data.bits_per_pixel, &vars.data.line_length, &vars.data.endian);

	char	*img_path00 = "./srcs/raycasting/xpm/greystone.xpm";
	int		img_width00;
	int		img_height00;

	image.img = mlx_xpm_file_to_image(vars.mlx, img_path00, &img_width00, &img_height00);
	image.addr = (unsigned int *)mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	int	y;
	int	x;
	int	texture_y;
	int	texture_x;

	x = 0;
	texture_x = 0;
	while (x < X_SIZE)
	{
		y = 0;
		texture_y = 0;
		while (texture_y < img_height00)
		{
			// vars.data.addr[(y * vars.data.line_length) + x] = image.addr[(texture_y * image.line_length) + texture_x];
			vars.data.addr[(y * X_SIZE) + x] = image.addr[(texture_y * img_width00) + texture_x];
			y += 1;
			texture_y += 1;
		}
		texture_x += 1;
		if (texture_x == img_height00)
		{
			texture_x = 0;
		}
		x += 1;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
