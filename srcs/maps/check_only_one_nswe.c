# include "../../include/cub3d.h"

void check_only_one_nswe(t_map *map)
{
    int i;
    int j;
    int count;

    i = 0;
    count = 0;
    while (i < map->height)
    {
        j = 0;
        // printf("map->map_data[%d] = %s\n",i,map->map_data[i]);
        while (map->map_data[i][j])
        {
            if (map->map_data[i][j] == 'N' || map->map_data[i][j] == 'S'
            || map->map_data[i][j] == 'W' || map->map_data[i][j] == 'E')
            {
                count++;
            }
            // printf("map->map_data[%d][%d] = %c\n",i,j,map->map_data[i][j]);
            j++;
        }
        i++;
    }
    if (count > 1)
    {
        print_error("Not only one of NSWE");
        exit (1);
    }
    return ;
}
