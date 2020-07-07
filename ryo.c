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

ryo_t player;
extern jo_sidescroller_physics_params  physics;

static const jo_tile WalkingRyoTiles[] =
{
    {RYO_WIDTH * 0, 0, RYO_WIDTH, RYO_HEIGHT},
    {RYO_WIDTH * 1, 0, RYO_WIDTH, RYO_HEIGHT},
    {RYO_WIDTH * 2, 0, RYO_WIDTH, RYO_HEIGHT},
};

static const jo_tile UpRyoTiles[] =
{
    {RYO_WIDTH * 0, 0, RYO_WIDTH, RYO_HEIGHT},
    {RYO_WIDTH * 1, 0, RYO_WIDTH, RYO_HEIGHT},
    {RYO_WIDTH * 2, 0, RYO_WIDTH, RYO_HEIGHT},
};

static const jo_tile DownRyoTiles[] =
{
    {RYO_WIDTH * 0, 0, RYO_WIDTH, RYO_HEIGHT},
    {RYO_WIDTH * 1, 0, RYO_WIDTH, RYO_HEIGHT},
    {RYO_WIDTH * 2, 0, RYO_WIDTH, RYO_HEIGHT},
};

inline void     ryo_running_animation_handling(void)
{			
	jo_start_sprite_anim_loop(player.walking_anim_id);
	//jo_set_sprite_anim_frame_rate(player.walking_anim_id, 1);
}

inline void     ryo_up_animation_handling(void)
{			
	jo_start_sprite_anim_loop(player.up_anim_id);
	//jo_set_sprite_anim_frame_rate(player.up_anim_id, 1);
}

inline void     ryo_down_animation_handling(void)
{			
	jo_start_sprite_anim_loop(player.down_anim_id);
	//jo_set_sprite_anim_frame_rate(player.down_anim_id, 1);
}

inline void     display_ryo(void)
{
    if (!physics.is_in_air)
    {
        player.spin = false;
        player.angle = 0;
    }
    if (player.flip_ryo)
        jo_sprite_enable_horizontal_flip();

    if (player.get_direction==0 || player.get_direction==1)
	{
		if(!player.verify_stand)
			ryo_running_animation_handling();
		else
			jo_reset_sprite_anim(player.walking_anim_id);
			
		
		jo_sprite_draw3D2(jo_get_anim_sprite(player.walking_anim_id), player.x, player.y, 450);
	}
    else if (player.get_direction==2)
	{
		if(!player.verify_stand)
			ryo_up_animation_handling();
		else
			jo_reset_sprite_anim(player.up_anim_id);
			
		
		jo_sprite_draw3D2(jo_get_anim_sprite(player.up_anim_id), player.x, player.y, 450);
	}
		
	else if (player.get_direction==3)
	{
		if(!player.verify_stand)
			ryo_down_animation_handling();
		else
			jo_reset_sprite_anim(player.down_anim_id);
		
		jo_sprite_draw3D2(jo_get_anim_sprite(player.down_anim_id), player.x, player.y, 450);
	}
	
	if (player.flip_ryo)
        jo_sprite_disable_horizontal_flip();
}

void            load_ryo(void)
{
	int sprite_id;
	
	sprite_id = jo_sprite_add_image_pack("RYO", "RIGHT.TEX", JO_COLOR_Green);
	player.walking_anim_id = jo_create_sprite_anim(sprite_id, JO_TILE_COUNT(WalkingRyoTiles), 4);
	
	sprite_id = jo_sprite_add_image_pack("RYO", "UP.TEX", JO_COLOR_Green);
	player.up_anim_id = jo_create_sprite_anim(sprite_id, JO_TILE_COUNT(UpRyoTiles), 4);
	
	sprite_id = jo_sprite_add_image_pack("RYO", "DOWN.TEX", JO_COLOR_Green);
	player.down_anim_id = jo_create_sprite_anim(sprite_id, JO_TILE_COUNT(DownRyoTiles), 4);
}

/*
** END OF FILE
*/
