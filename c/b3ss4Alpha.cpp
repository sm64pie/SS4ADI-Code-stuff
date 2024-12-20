#include "b3ss4Alpha.h"
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

void b3ss4ControlA::Init()
{
	oBowser = obj_nearest_object_with_behavior((const BehaviorScript*) 0x13001850);
	isBowserDed = false;
	
}

void b3ss4ControlA::Step()
{	
	if (gCamera->cutscene == CUTSCENE_ENTER_BOWSER_ARENA){
		oBowser->oAction = 0x12;
		oBowser->oHealth = 3;
	}
	else if (oBowser->oHealth == 0){
		oBowser->oPosX = -990;
		oBowser->oPosZ = -60;
		oBowser->oAction = 0x04;
		if (isBowserDed == false){
			auto DimSphereSpawn = spawn_object_abs_with_rot(this, 0,0xF0,((const BehaviorScript*) 0x130056BC), -1140,2200,-60,0,0,0);
			isBowserDed = true;
		}
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
		else if (oTimer >= 150){
			oTimer = 0;
		}
	}
}

void b3ss4ControlA::bowserActions()
{
	f32 rand = RandomFloat();
	if (rand < 0.15){
		oBowser->oAction = 0x08;
	}
	else if (rand < 0.4 && dist_between_objects(oBowser, gMarioObject) < 400.f && rand > 0.14){
		oBowser->oMoveAngleYaw = oBowser->oAngleToMario;
		oBowser->oFaceAngleYaw = oBowser->oAngleToMario;
		oBowser->oAction = 0x03;
	}
	else if (rand < 0.4 && dist_between_objects(oBowser, gMarioObject) >= 400.f && rand > 0.14){
		oBowser->oAction = 0x11;
	}
	else if (rand < 0.5 && rand > 0.39){
		oBowser->oMoveAngleYaw = oBowser->oAngleToMario;
		oBowser->oFaceAngleYaw = oBowser->oAngleToMario;
		oBowser->oAction = 0x07;
	}
	else if (rand < 0.7 && rand > 0.49){
		oBowser->oMoveAngleYaw = oBowser->oAngleToMario;
		oBowser->oFaceAngleYaw = oBowser->oAngleToMario;
		oBowser->oAction = 0x0F;
	} 
	else{
		oBowser->oAction = 0x09;
	}
}
// This is really simple behavior script, for behavior script documentation you may check hack64
uintptr_t b3ss4ControlA::Behavior[] = 
{
	0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};