/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmayika <kmayika@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 14:13:15 by kmayika           #+#    #+#             */
/*   Updated: 2018/08/27 15:45:46 by kmayika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	render(t_wolf *ren)
{
	ren->x = 0;
		while(ren->x < TILE_WIDTH)
		{
			ren->cam.camera_x = 2 * ren->x / (double)TILE_WIDTH - 1;
			ren->cam.ray_dir_x = ren->dir_x + ren->plane_x * ren->cam.camera_x;
			ren->cam.ray_dir_y = ren->dir_y + ren->plane_y * ren->cam.camera_x;
			//which box of the map we're in
      		ren->map_x = (int)ren->pos_x;
      		ren->map_y = (int)ren->pos_y;

       	//length of ray from one x or y-side to next x or y-side
      		ren->dist.delta_dist_x = fabs(1 / ren->cam.ray_dir_x);
     		ren->dist.delta_dist_y = fabs(1 / ren->cam.ray_dir_y);

      	//what direction to step in x or y-direction (either +1 or -1)
      		ren->hit = 0; //was there a wall hit?
			//calculate step and initial sideDist
			if (ren->cam.ray_dir_x < 0)
     		{
        	ren->step_x = -1;
        	ren->dist.side_dist_x = (ren->pos_x - ren->map_x) * ren->dist.delta_dist_x;
      		}
      		else
      		{
				ren->step_x = 1;
        		ren->dist.side_dist_x = (ren->map_x + 1.0 - ren->pos_x) * ren->dist.delta_dist_x;
      		}
      		if (ren->cam.ray_dir_y < 0)
     		{
        		ren->step_y = -1;
        		ren->dist.side_dist_y = (ren->pos_y - ren->map_y) * ren->dist.delta_dist_y;
      		}
      		else
      		{
        		ren->step_y = 1;
        		ren->dist.side_dist_y = (ren->map_y + 1.0 - ren->pos_y) * ren->dist.delta_dist_y;
      		}
			//perform DDA
      		while (ren->hit == 0)
      		{
        //jump to next map square, OR in x-direction, OR in y-direction
        		if (ren->dist.side_dist_x < ren->dist.side_dist_y)
        		{
          			ren->dist.side_dist_x += ren->dist.delta_dist_x;
          			ren->map_x += ren->step_x;
          			ren->side = 0;
       			}
        		else
        		{
          			ren->dist.side_dist_y += ren->dist.delta_dist_y;
          			ren->map_y += ren->step_y;
          			ren->side = 1;
        		}
        //Check if ray has hit a wall
        		if (worldMap[ren->map_y][ren->map_x] > 0)
					ren->hit = 1;
      		}
			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      		if (ren->side == 0)
			  ren->dist.perp_wall_dist = (ren->map_x - ren->pos_x + (1 - ren->step_x) / 2) / ren->cam.ray_dir_x;
      		else
			  ren->dist.perp_wall_dist = (ren->map_y - ren->pos_y + (1 - ren->step_y) / 2) / ren->cam.ray_dir_y;
			//Calculate height of line to draw on screen
      		ren->draw.line_height = (int)(TILE_HEIGHT / ren->dist.perp_wall_dist);

      //calculate lowest and highest pixel to fillin current stripe
      		ren->draw.draw_start = -ren->draw.line_height / 2 + TILE_HEIGHT / 2;
      		if(ren->draw.draw_start < 0)
			  	ren->draw.draw_start = 0;
      		ren->draw.draw_end = ren->draw.line_height / 2 + TILE_HEIGHT / 2;
      		if(ren->draw.draw_end >= TILE_HEIGHT)
	  			ren->draw.draw_end = TILE_HEIGHT - 1;
			while (ren->draw.draw_start != ren->draw.draw_end)
			{
				if(worldMap[ren->map_x][ren->map_y] == 3)
				{
					ren->color = 0x00FF00;
				}
				else if (worldMap[ren->map_x][ren->map_y] == 4)
				{
					ren->color = 0xff00ff;
				}
				else
				{
					ren->color = 0xFFFFFF;
				}
				mlx_pixel_put(ren->mlx,ren->win,ren->x,ren->draw.draw_start++, ren->color);
			}
			ren->x++;
		}
}

int		exit_prog()
{
	exit(0);
}

int		hooks(int keycode, t_wolf *ren)
{
	double rot_speed = 0.1;
	if (keycode == 53)
		exit_prog();
	else if (keycode == 126)
	{
		if (worldMap[(int)(ren->pos_y)][(int)(ren->pos_x + ren->dir_x)] == 0)
			ren->pos_x += ren->dir_x;
		if (worldMap[(int)(ren->pos_y + ren->dir_y)]
				[(int)(ren->pos_x)] == 0)
			ren->pos_y += ren->dir_y;
	}
	else if (keycode == 125)
	{
		ren->pos_x -= ren->dir_x;
		ren->pos_y -= ren->dir_y;
	}
	else if (keycode == 124)
	{
		ren->old_dir_x = ren->dir_x;
		ren->dir_x = ren->dir_x * cos(-rot_speed) - ren->dir_y * sin(-rot_speed);
		ren->dir_y = ren->old_dir_x * sin(-rot_speed) + ren->dir_y * cos(-rot_speed);
		ren->old_plane_x = ren->plane_x;
		ren->plane_x = ren->plane_x * cos(-rot_speed) - ren->plane_y * sin(-rot_speed);
		ren->plane_y = ren->old_plane_x * sin(-rot_speed) + ren->plane_y * cos(-rot_speed);	
	}
	else if (keycode == 123)
	{
		ren->old_dir_x = ren->dir_x;
		ren->dir_x = ren->dir_x * cos(rot_speed) - ren->dir_y * sin(rot_speed);
		ren->dir_y = ren->old_dir_x * sin(rot_speed) + ren->dir_y * cos(rot_speed);
		ren->old_plane_x = ren->plane_x;
		ren->plane_x = ren->plane_x * cos(rot_speed) - ren->plane_y * sin(rot_speed);
		ren->plane_y = ren->old_plane_x * sin(rot_speed) + ren->plane_y * cos(rot_speed);
	}
	mlx_clear_window(ren->mlx, ren->win);
	render(ren);
	return (0);
}

int		main(/*int ac, char **av*/)
{
	t_wolf *ren;

	ren = (t_wolf *)malloc(sizeof(t_wolf));
	ren->pos_x = 2;
	ren->pos_y = 2;//x and y start positions
	ren->dir_x = -1;
	ren->dir_y = 0;// initial direction vector
	ren->plane_x = 0;
	ren->plane_y = 0.66;//camera plane
//	double time = 0;//time of current frame
//	double old_time = 0; //time of old frame
	ren->x = 0;
	ren->y = 0;
	ren->mlx = mlx_init();
	ren->win = mlx_new_window(ren->mlx, TILE_WIDTH,TILE_HEIGHT, "Wolf3D");
	render(ren);
	mlx_hook(ren->win, 2, 0, hooks, ren);
	mlx_hook(ren->win, 17, 0, exit_prog, 0);
//	mlx_key_hook(ren->win, hooks, ren);
	mlx_loop(ren->mlx);
}
