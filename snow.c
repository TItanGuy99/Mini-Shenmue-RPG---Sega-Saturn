#include <jo/jo.h>
#include "snow.h"
#define SNOW 10

snow_t snow;

int sprite_id;
int sprite_id2;
int save_y[SNOW];
int save_x[SNOW];
int save_speed[SNOW];

int random_x_snow(void)
{
	if (jo_random(10)>5)
	{
		return jo_random_using_multiple(160, 2);
	}
	else
	{
		return jo_random_using_multiple(160, 2)*-1;
	}
}

int random_y_snow(void)
{
	return jo_random_using_multiple(400, 2)*-1;
}

void fill_array_x_y_speed_snow(void)
{
	int i = 0;

	for (i = 0; i < SNOW; i++)
	{
		save_x[i] = random_x_snow();
		save_y[i] = random_y_snow();

		save_speed[i] = 1;
	}
}

void			draw_snow(void)
{
	int i = 0;

	for (i = 0; i < SNOW; i++)
	{
		save_y[i] += save_speed[i];

		/*if (jo_random(10) > 5)
		{
			if (jo_random(10) > 5)
			{
				if (jo_random(10) > 5 && save_y[i] % 2)
				{
					save_x[i] -= 1;
				}
				else if (save_y[i] % 2)
				{
					save_x[i] += 1;
				}
			}
		}*/

		if (i % 2)
		{
			jo_sprite_draw3D_and_rotate(sprite_id, save_x[i], save_y[i], 500, 0);
		}
		else
		{
			jo_sprite_draw3D_and_rotate(sprite_id2, save_x[i], save_y[i], 500, 0);
		}


		if (save_y[i] > 250)
		{
			save_speed[i] = 1;
			save_y[i] = -200;
			save_x[i] = random_x_snow();
		}
	}
}

void            remove_snow(void)
{
	jo_core_remove_callback(draw_snow);
}

void			load_snow(void)
{
	sprite_id = NULL;
	sprite_id2 = NULL;
	sprite_id = jo_sprite_add_tga("EFFECTS", "SNOW.TGA", JO_COLOR_Black);
	sprite_id2 = jo_sprite_add_tga("EFFECTS", "SNOW2.TGA", JO_COLOR_Black);
	fill_array_x_y_speed_snow();
	jo_core_add_callback(draw_snow);
}