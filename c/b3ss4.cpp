#include "b3ss4.h"
/*
 Notice that all headers that you need must be exported via 'extern "C"' or linker will fail 
 */
extern "C"
{
    #include "game/object_helpers.h"
	#include "game/camera.h"
	#include "game/mario.h"
	#include "game/level_update.h"
	#include "engine/behavior_script.h"
	#include "audio/external.h"
}
#include "object_fields.h"
#define oBowser OBJECT_FIELD_OBJ(0x1b)
#define CUTSCENE_ENTER_BOWSER_ARENA   144

void b3ss4Control::Init()
{
	oBowser = obj_nearest_object_with_behavior((const BehaviorScript*) 0x13001850);
	oBowser->oPosX = 0;
	oBowser->oPosY = 3043;
	oBowser->oPosZ = 0;
	oBowser->oHealth = 3;
}

void b3ss4Control::Step()
{	

	if (gCamera->cutscene == CUTSCENE_ENTER_BOWSER_ARENA){
		oBowser->oAction = 0x05;
	}
	else if (oBowser->oHealth == 0){
		oBowser->oPosX = 0;
		oBowser->oPosZ = 0;
		oBowser->oAction = 0x04;
	}
	else if (oBowser->oAction == 0x0C){
		oBowser->oPosX = 0;
		oBowser->oPosZ = 0;
	}
	else {
		if (oTimer < 2 && oBowser->oAction != 0x0C && oBowser->oAction != 0x01 && oBowser->oAction != 0x02){
			if (oBowser->oAction != 0x0C){
				if (oBowser->oAction != 0x01){
					if (oBowser->oAction != 0x02){
						bowserActions();
					}
				}
			}	
		}
		else if (oTimer > 105 && oTimer < 150){
			if (oBowser->oAction != 0x0C){
				if (oBowser->oAction != 0x01){
					if (oBowser->oAction != 0x02){
						oBowser->oAction = 0x0E;
					}
				}
			}	
		}
		else if (oTimer >= 120){
			oTimer = 0;
		}
	}
}

void b3ss4Control::bowserActions()
{
	f32 rand = RandomFloat();
	if (rand < 0.2){
		oBowser->oAction = 0x08;
	}
	else if (rand < 0.4 && dist_between_objects(oBowser, gMarioObject) < 400.f){
		oBowser->oMoveAngleYaw = oBowser->oAngleToMario;
		oBowser->oFaceAngleYaw = oBowser->oAngleToMario;
		oBowser->oAction = 0x03;
	}
	else if (rand < 0.4 && dist_between_objects(oBowser, gMarioObject) >= 400.f){
		oBowser->oAction = 0x11;
	}
	else if (rand < 0.5){
		oBowser->oMoveAngleYaw = oBowser->oAngleToMario;
		oBowser->oFaceAngleYaw = oBowser->oAngleToMario;
		oBowser->oAction = 0x10;
	}
	else if (rand < 0.7){
		oBowser->oMoveAngleYaw = oBowser->oAngleToMario;
		oBowser->oFaceAngleYaw = oBowser->oAngleToMario;
		oBowser->oAction = 0x0D;
	} 
	else{
		oBowser->oAction = 0x09;
	}
}

// This is really simple behavior script, for behavior script documentation you may check hack64
uintptr_t b3ss4Control::Behavior[] = 
{
	0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};