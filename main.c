/*
** Jo Sega Saturn Engine
** Copyright (c) 2012-2016, Johannes Fetz (johannesfetz@gmail.com)
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the Johannes Fetz nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL Johannes Fetz BE LIABLE FOR ANY
** DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <jo/jo.h>
#include "ryo.h"
#include "snow.h"

/*
** SPECIAL NOTE: It's not the ryo that I'm working on, but you can now write your own :)
*/

jo_sidescroller_physics_params  physics;
static int map_pos_x = 0;
static int map_pos_y = 0;
bool collided = false;
bool vertical_collision = false;
bool horizontal_collision = false;
int sprite1;
int sprite2;
int sprite3;
int sprite4;
int sprite5;
int sprite6;
int sprite7;
//int sprite8;

int count_time;
jo_img      img1;
jo_img      img2;
jo_img      img3;
jo_img      img4;
jo_img      img5;
jo_img      img6;
jo_img      img7;
//jo_img      img8;
jo_img      bg;
int aux;
bool is_loading=false;


void            reset_demo(void)
{
    map_pos_x = 0;
    map_pos_y = 0;
    player.x = 160;
    player.y = 70;
    player.angle = 0;
    player.flip_ryo = false;
    player.spin = false;
    player.can_jump = true;
}

void            my_async_read(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    //bg.data = JO_NULL;
    if (jo_tga_loader_from_stream(&bg, contents, JO_COLOR_Transparent) == JO_TGA_OK)
        jo_set_background_sprite(&bg, 0, 0);
    jo_free(contents);

}

inline bool          has_vertical_collision(void)
{
	vertical_collision = false;
	
    if (physics.speed_y < 0.0f)
    {
        return false;
    }
    int dist = jo_map_per_pixel_vertical_collision(WORLD_MAP_ID, map_pos_x + player.x + RYO_WIDTH_2, map_pos_y + player.y + RYO_HEIGHT, JO_NULL);
    if (dist == JO_MAP_NO_COLLISION || dist > 0)
    {
        return false;
    }
	
	if(!collided)
	{
		collided=true;
		jo_audio_stop_cd();
		jo_clear_background(JO_COLOR_Black);
		load_snow();
		jo_audio_play_cd_track(3, 3, 0);
	}
	
	vertical_collision = true;
	return true;
}

inline bool      has_horizontal_collision(void)
{
    int         next_pixel;
	horizontal_collision = false;

    next_pixel = jo_physics_is_going_on_the_right(&physics) ? player.x + 8 :
                 jo_physics_is_going_on_the_left(&physics) ? player.x - 4 :
                 player.x;
    int attr = jo_map_hitbox_detection_custom_boundaries(WORLD_MAP_ID, map_pos_x + next_pixel + RYO_WIDTH_2, map_pos_y + player.y, 4, 20);
    if (attr == JO_MAP_NO_COLLISION)
        return false;
    if (attr != MAP_TILE_BLOCK_ATTR)
        return false;
	
	if(!collided)
	{
		collided=true;
		jo_audio_stop_cd();
		jo_clear_background(JO_COLOR_Black);
		load_snow();
		jo_audio_play_cd_track(3, 3, 0);
	}
	
	horizontal_collision = true;
    return true;
}

inline void     ryo_collision_handling(void)
{
	has_vertical_collision();
	has_horizontal_collision();
}

inline void     camera_handling(int prev_y)
{
    int         delta;

    delta = JO_ABS(player.y - prev_y);
    if (player.y > 100)
    {
        map_pos_y += delta;
        player.y -= delta;
    }
    else if (player.y < 50)
    {
        map_pos_y -= delta;
        player.y += delta;
    }
}







void            my_async_read35(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img7, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img7, sprite7);
    jo_free(contents);
}

void            my_async_read34(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img6, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img6, sprite6);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE40.TGA", my_async_read35, 0);
}

void            my_async_read33(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img5, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img5, sprite5);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE39.TGA", my_async_read34, 0);
}

void            my_async_read32(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img4, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img4, sprite4);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE38.TGA", my_async_read33, 0);
}

void            my_async_read31(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img3, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img3, sprite3);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE37.TGA", my_async_read32, 0);
}

void            my_async_read30(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img2, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img2, sprite2);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE36.TGA", my_async_read31, 0);
}

void            my_async_read29(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img1, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img1, sprite1);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE35.TGA", my_async_read30, 0);
	is_loading=false;
}


























void            my_async_read28(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img7, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img7, sprite7);
    jo_free(contents);
}

void            my_async_read27(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img6, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img6, sprite6);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE33.TGA", my_async_read28, 0);
}

void            my_async_read26(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img5, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img5, sprite5);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE32.TGA", my_async_read27, 0);
}

void            my_async_read25(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img4, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img4, sprite4);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE31.TGA", my_async_read26, 0);
}

void            my_async_read24(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img3, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img3, sprite3);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE30.TGA", my_async_read25, 0);
}

void            my_async_read23(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img2, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img2, sprite2);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE29.TGA", my_async_read24, 0);
}

void            my_async_read22(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img1, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img1, sprite1);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE28.TGA", my_async_read23, 0);
	is_loading=false;
}













void            my_async_read21(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img7, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img7, sprite7);
    jo_free(contents);
}

void            my_async_read20(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img6, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img6, sprite6);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE26.TGA", my_async_read21, 0);
}

void            my_async_read19(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img5, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img5, sprite5);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE25.TGA", my_async_read20, 0);
}

void            my_async_read18(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img4, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img4, sprite4);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE24.TGA", my_async_read19, 0);
}

void            my_async_read17(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img3, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img3, sprite3);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE23.TGA", my_async_read18, 0);
}

void            my_async_read16(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img2, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img2, sprite2);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE22.TGA", my_async_read17, 0);
}

void            my_async_read15(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img1, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img1, sprite1);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE21.TGA", my_async_read16, 0);
	is_loading=false;
}














void            my_async_read14(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img7, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img7, sprite7);
    jo_free(contents);
}

void            my_async_read13(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img6, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img6, sprite6);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE20.TGA", my_async_read14, 0);
}

void            my_async_read12(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img5, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img5, sprite5);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE19.TGA", my_async_read13, 0);
}

void            my_async_read11(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img4, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img4, sprite4);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE18.TGA", my_async_read12, 0);
}

void            my_async_read10(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img3, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img3, sprite3);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE17.TGA", my_async_read11, 0);
}

void            my_async_read9(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img2, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img2, sprite2);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE16.TGA", my_async_read10, 0);
}

void            my_async_read8(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img1, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img1, sprite1);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE15.TGA", my_async_read9, 0);
	is_loading=false;
}







void            my_async_read7(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img7, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img7, sprite7);
    jo_free(contents);
}

void            my_async_read6(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img6, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img6, sprite6);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE13.TGA", my_async_read7, 0);
}

void            my_async_read5(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img5, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img5, sprite5);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE12.TGA", my_async_read6, 0);
}

void            my_async_read4(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img4, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img4, sprite4);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE11.TGA", my_async_read5, 0);
}

void            my_async_read3(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img3, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img3, sprite3);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE10.TGA", my_async_read4, 0);
}

void            my_async_read2(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img2, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img2, sprite2);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE9.TGA", my_async_read3, 0);
}

void            my_async_read1(char *contents, int length, int optional_token)
{
    JO_UNUSED_ARG(length); // Avoid unused parameter warning
    JO_UNUSED_ARG(optional_token);
    if (jo_tga_loader_from_stream(&img1, contents, JO_COLOR_Transparent) == JO_TGA_OK)
		jo_sprite_replace(&img1, sprite1);
    jo_free(contents);
	jo_fs_read_file_async("IMAGE8.TGA", my_async_read2, 0);
	is_loading=false;
}

inline void     my_draw(void)
{		
    int         prev_y;

	if(collided)
	{
		count_time++;
		if(!is_loading)
		jo_sprite_draw3D_and_rotate(sprite1,0,0, 500, 0);
	}
	
	if(count_time==500)
	{		
        aux=sprite1;
		sprite1 = sprite2;
	}
	
	
	if(count_time==1500)
	{
		sprite1 = sprite3;
	}
	
	if(count_time==2500)
	{
		sprite1 = sprite4;
	}
	
	if(count_time==3500)
	{
		sprite1 = sprite5;
	}
	
	if(count_time==4500)
	{
		sprite1 = sprite6;
	}
	
	if(count_time==5500)
	{
		sprite1 = sprite7;
	}
	
	/*if(count_time==6500)
	{
		sprite1 = sprite8;
		
	}*/
		
	if(count_time==7400)
	{
		jo_audio_stop_cd();
	}
	
	if(count_time==7800)
	{
		sprite1=aux;
		is_loading=true;
		jo_fs_read_file_async("IMAGE7.TGA", my_async_read1, 0);
	}
	
	if(count_time==8300)
	{
		jo_audio_play_cd_track(4, 4, 0);
	}
	
	if(count_time==9300)
	{
		aux = sprite1;
		sprite1 = sprite2;
	}
	
	if(count_time==10500)
	{
		sprite1 = sprite3;
	}
	
	if(count_time==11500)
	{
		sprite1 = sprite4;
	}
	
	if(count_time==12000)
	{
		sprite1 = sprite5;
	}
	
	if(count_time==13500)
	{
		sprite1 = sprite6;
	}
	
	if(count_time==15500)
	{
		sprite1 = sprite7;
	}
	
	/*if(count_time==17500)
	{
		sprite1 = sprite8;
	}*/
	
	if(count_time==19000)
	{
		jo_audio_stop_cd();
	}
	
	if(count_time==19300)
	{
		sprite1 = aux;
		is_loading=true;
		jo_fs_read_file_async("IMAGE14.TGA", my_async_read8, 0);
	}
	
	if(count_time==19500)
	{
		jo_audio_play_cd_track(5, 5, 0);
	}
	
	if(count_time==19800)
	{
		aux = sprite1;
		sprite1 = sprite2;
	}
	
	if(count_time==21500)
	{
		sprite1 = sprite3;
	}
	
	if(count_time==22500)
	{
		sprite1 = sprite4;
	}
	
	if(count_time==23500)
	{
		sprite1 = sprite5;
	}
	
	if(count_time==24500)
	{
		sprite1 = sprite6;
	}
	
	if(count_time==25500)
	{
		sprite1 = sprite7;
	}
	
	/*if(count_time==26500)
	{
		sprite1 = sprite8;
	}*/
	

	
	if(count_time==28900)
	{
		sprite1 = aux;
		is_loading=true;
		jo_fs_read_file_async("IMAGE21.TGA", my_async_read15, 0);
	}

	if(count_time==29200)
	{
		jo_audio_play_cd_track(6, 6, 0);
	}	
	
	if(count_time==30000)
	{
		aux = sprite1;
		sprite1 = sprite2;
	}
	
	if(count_time==31000)
	{
		sprite1 = sprite3;
	}
	
	if(count_time==32000)
	{
		sprite1 = sprite4;
	}
	
	if(count_time==33000)
	{
		sprite1 = sprite5;
	}
	
	if(count_time==34000)
	{
		sprite1 = sprite6;
	}
	
	if(count_time==35000)
	{
		sprite1 = sprite7;
	}
		
	if(count_time==36500)
	{
		sprite1=aux;
		is_loading=true;
		jo_fs_read_file_async("IMAGE27.TGA", my_async_read22, 0);
	}
	
	
	if(count_time==36800)
	{
		jo_audio_play_cd_track(7, 7, 0);
	}	
	
	if(count_time==37000)
	{
		aux = sprite1;
		sprite1 = sprite2;
	}
	
	if(count_time==37500)
	{
		sprite1 = sprite3;
	}
	
	if(count_time==38000)
	{
		sprite1 = sprite4;
	}
	
	if(count_time==38500)
	{
		sprite1 = sprite5;
	}
	
	if(count_time==39000)
	{
		sprite1 = sprite6;
	}
	
	if(count_time==39500)
	{
		sprite1 = sprite7;
	}
	
	if(count_time==40500)
	{
		sprite1=aux;
		is_loading=true;
		jo_fs_read_file_async("IMAGE34.TGA", my_async_read29, 0);
	}
	
	if(count_time==40800)
	{
		jo_audio_play_cd_track(8, 8, 0);
	}	
	
	if(count_time==42000)
	{
		aux = sprite1;
		sprite1 = sprite2;
	}
	
	if(count_time==43500)
	{
		sprite1 = sprite3;
	}
	
	if(count_time==45000)
	{
		sprite1 = sprite4;
	}
	
	if(count_time==47500)
	{
		sprite1 = sprite5;
	}
	
	if(count_time==49000)
	{
		sprite1 = sprite6;
	}
	
	if(count_time==50500)
	{
		sprite1 = sprite7;
	}
	
	if(count_time==71000)
	{
		jo_goto_boot_menu();
	}
	
	jo_map_draw(WORLD_MAP_ID, map_pos_x, map_pos_y);
    prev_y = player.y;
    ryo_collision_handling();
    camera_handling(prev_y);

    display_ryo();
}

inline void     make_ryo_jump(void)
{
    player.can_jump = false;
    player.spin = true;
    jo_physics_jump(&physics);
}

inline void     my_input(void)
{
	    player.verify_stand=true;
	
        if (jo_is_pad1_key_pressed(JO_KEY_LEFT))
        {
			if(player.x>0)
			{
				player.verify_stand=false;
				player.flip_ryo=1;
				player.get_direction=0;
				player.x-=1;	
			}
        }
        else if (jo_is_pad1_key_pressed(JO_KEY_RIGHT))
        {
			if(player.x<300 && !vertical_collision)
			{
				player.verify_stand=false;
				player.flip_ryo=0;
				player.get_direction=1;
				player.x+=1;	
			}
        }
		else if (jo_is_pad1_key_pressed(JO_KEY_UP))
		{
			if(player.y>55 && !horizontal_collision)
			{
				player.verify_stand=false;
				player.get_direction=2;
				player.y-=1;
			}
		}
		else if (jo_is_pad1_key_pressed(JO_KEY_DOWN))
		{
			if(player.y<210)
			{
				player.verify_stand=false;
				player.get_direction=3;
				player.y+=1;
			}
		}

    //if (jo_is_pad1_key_down(JO_KEY_START))
        //reset_demo();
}

void			load_map(void)
{
    jo_sprite_add_image_pack("BLK", "BLK.TEX", JO_COLOR_Black);
	jo_map_load_from_file(WORLD_MAP_ID, 500, "MAP", "DEMO2.MAP");
}

void			load_background(void)
{
    bg.data = JO_NULL;
    jo_tga_loader(&bg, "BG", "BG.TGA", JO_COLOR_Transparent);
    jo_set_background_sprite(&bg, 0, 0);
    jo_free_img(&bg);
}


void			jo_main(void)
{
	jo_core_init(JO_COLOR_Black);
	load_background();
	jo_sprite_init(1);
	
	img1.data = NULL;
	jo_tga_loader(&img1, "END", "IMAGE0.TGA", JO_COLOR_Transparent);
	sprite1 = jo_sprite_add(&img1);
	
	img2.data = NULL;
	jo_tga_loader(&img2, "END", "IMAGE1.TGA", JO_COLOR_Transparent);
	sprite2 = jo_sprite_add(&img2);
	
	img3.data = NULL;
	jo_tga_loader(&img3, "END", "IMAGE2.TGA", JO_COLOR_Transparent);
	sprite3 = jo_sprite_add(&img3);
	
	img4.data = NULL;
	jo_tga_loader(&img4, "END", "IMAGE3.TGA", JO_COLOR_Transparent);
	sprite4 = jo_sprite_add(&img4);
	
	img5.data = NULL;
	jo_tga_loader(&img5, "END", "IMAGE4.TGA", JO_COLOR_Transparent);
	sprite5 = jo_sprite_add(&img5);
	
	img6.data = NULL;
	jo_tga_loader(&img6, "END", "IMAGE5.TGA", JO_COLOR_Transparent);
	sprite6 = jo_sprite_add(&img6);
	
	img7.data = NULL;
	jo_tga_loader(&img7, "END", "IMAGE6.TGA", JO_COLOR_Transparent);
	sprite7 = jo_sprite_add(&img7);
	
	/*img8.data = NULL;
	jo_tga_loader(&img8, "END", "IMAGE7.TGA", JO_COLOR_Transparent);
	sprite8 = jo_sprite_add(&img8);*/
		
	load_map();
    load_ryo();
	
    reset_demo();
	jo_core_add_callback(my_draw);
	jo_core_add_callback(my_input);
	jo_audio_play_cd_track(2, 2, 1);
	jo_core_run();
}

/*
** END OF FILE
*/
