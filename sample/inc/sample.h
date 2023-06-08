#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <math.h>

# define SUCCESS 1
# define ERROR 0
# define ESC_KEY 53
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define UP_KEY 126
# define SPACE_KEY 49
# define ESC_KEY_M1 65307
# define LEFT_KEY_M1 65361
# define RIGHT_KEY_M1 65363
# define DOWN_KEY_M1 65364
# define UP_KEY_M1 65362

# define MOVE_SPEED 1
# define ROT_SPEED 0.5

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void raycasting(t_vars *vars);
int	key_handle(int keycode, t_vars *vars);