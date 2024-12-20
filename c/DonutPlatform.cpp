#include "DonutPlatform.h"
/*
 Notice that all headers that you need must be exported via 'extern "C"' or linker will fail 
 */
extern "C"
{
    #include "game/object_helpers.h"
	#include "game/object_helpers2.h"
	#include "game/obj_behaviors_2.h"
	#include "game/mario.h"
	#include "engine/surface_load.h"
}
#include "object_fields.h"
#include "object_constants.h"
#include "behavior_data.h"
void DonutPlatform::Init()
{

}


void DonutPlatform::Step()
{
	if (this->oGravity == 0.0f){
		if (gMarioObject->platform == this){
			obj_shake_y(40.0f);
			if (this->oTimer > 150){
				this->oGravity = -0.5f;
				this->oTimer = 0;
			}
		}
	}
	else{			
		if (this->oTimer > 300){
			spawn_object(this, 0xCD, (const BehaviorScript*) 0x13003510);
			mark_object_for_deletion(this);
		}
		else{
			obj_update_floor_and_walls();
			obj_move_standard(78);
		}
	}

	load_object_collision_model();
}

// This is really simple behavior script, for behavior script documentation you may check hack64
uintptr_t DonutPlatform::Behavior[] = 
{
	0x2A000000, 0x00000000,
	0x11010041,
	0x2D000000,
	0x08000000,
    0x0C000000, (uintptr_t) sStep,
	0x0C000000, 0x803839CC,
	0x09000000
};