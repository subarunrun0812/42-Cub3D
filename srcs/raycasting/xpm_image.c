#include <mlx.h>
#include <stdio.h>
#include <unistd.h>

typedef struct	s_vars	t_vars;
typedef struct	s_data	t_data;

struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	data;
};

int	main(void)
{
	t_vars	vars;
	t_data	image;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "xpm image");

	char	*img_path00 = "./hnoguchi/lodev/sample/xpm/greystone.xpm";
	int		img_width00;
	int		img_height00;

	image.img = mlx_xpm_file_to_image(vars.mlx, img_path00, &img_width00, &img_height00);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
