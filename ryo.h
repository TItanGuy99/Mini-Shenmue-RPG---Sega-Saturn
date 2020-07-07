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

#ifndef __RYO_H__
# define __RYO_H__

# define WORLD_MAP_ID		            (0)
# define WORLD_DEFAULT_X                (540)
# define WORLD_DEFAULT_Y                (120)

# define MAP_TILE_BLOCK_ATTR            (1)

# define RYO_WIDTH                    (16)
# define RYO_WIDTH_2                  (16)
# define RYO_HEIGHT                   (24)
# define RYO_SPIN_SPEED               (20)

/* If ryo almost touch the ground we allow the user to jump */
# define RYO_JUMP_PER_PIXEL_TOLERANCE (20)

typedef struct
{
	bool        verify_stand;
	int         get_direction;
    int         walking_anim_id;
	int         up_anim_id;
	int         down_anim_id;
    int         spin_sprite_id;
    int         x;
    int         y;
    bool        flip_ryo;
    bool        spin;
    bool        can_jump;
    int         angle;
}               ryo_t;

extern ryo_t player;

void            ryo_running_animation_handling();
void            ryo_up_animation_handling();
void            ryo_down_animation_handling();
void            display_ryo(void);
void            load_ryo(void);

#endif /* !__RYO_H__ */

/*
** END OF FILE
*/
