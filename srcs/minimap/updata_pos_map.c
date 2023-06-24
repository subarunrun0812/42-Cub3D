# include "../../include/cub3d.h"

void updata_pos_map(t_vars *vars,t_info *info)
{
	//map情報を更新
	if (info->map->map_data[(int)(vars->x_position_vector)][(int)(vars->y_position_vector)] == '0')
    {
        info->map->map_data[(int)(vars->x_position_vector - (vars->x_direction * MOVE_DISTANCE))][(int)(vars->y_position_vector - (vars->y_direction * MOVE_DISTANCE))] = '0';
        info->map->map_data[(int)(vars->x_position_vector)][(int)(vars->y_position_vector)] = 'N';
    }
    else if (info->map->map_data[(int)(vars->x_position_vector)][(int)(vars->y_position_vector)] == '1')
    {
        vars->x_position_vector -= vars->x_direction * MOVE_DISTANCE;
        vars->y_position_vector -= vars->y_direction * MOVE_DISTANCE;
    }
	// debug_print_mapdata(info);
	
}