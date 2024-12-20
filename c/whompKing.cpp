#include "whompKing.h"
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
#define oWhompKing OBJECT_FIELD_OBJ(0x1b)

void WhompKing::Init()
{
	oWhompKing = obj_nearest_object_with_behavior((const BehaviorScript*) 0x13002BB8);
	oWhompKing->oPosX = -5355;
	oWhompKing->oPosY = 0;
	oWhompKing->oPosZ = 0;
	isWhompKingDead = false;
}

void WhompKing::Step()
{	
	switch(oWhompKing->oHealth){
		case 6:
			oWhompKing->oPosX = 0;
			oWhompKing->oPosY = 0;
			oWhompKing->oPosZ = -5375;
			break;
		case 5:
			oWhompKing->oPosX = 0;
			oWhompKing->oPosY = 0;
			oWhompKing->oPosZ = 5375;
			break;
		case 4:
			oWhompKing->oPosX = -5355;
			oWhompKing->oPosY = 0;
			oWhompKing->oPosZ = 0;
			break;
		case 3:
			oWhompKing->oPosX = 0;
			oWhompKing->oPosY = 0;
			oWhompKing->oPosZ = -5375;
			break;
		case 2:
			oWhompKing->oPosX = 0;
			oWhompKing->oPosY = 0;
			oWhompKing->oPosZ = 5375;
			break;
		case 1:
			oWhompKing->oPosX = -5355;
			oWhompKing->oPosY = 0;
			oWhompKing->oPosZ = 0;
			break;
		case 0:
		if (isWhompKingDead == false){
			auto DimSphereSpawn = spawn_object_abs_with_rot(this, 0,0xF0,((const BehaviorScript*) 0x130056BC), 0,150,0,0,0,0);
			isWhompKingDead = true;
		}
			break;
	}
}
// This is really simple behavior script, for behavior script documentation you may check hack64
uintptr_t WhompKing::Behavior[] = 
{
	0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};