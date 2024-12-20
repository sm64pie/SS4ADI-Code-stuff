#include "DimSphereMusicPrev.h"
/*
 Notice that all headers that you need must be exported via 'extern "C"' or linker will fail 
 */
extern "C"
{
    #include "game/object_helpers.h"
	#include "game/camera.h"
	#include "game/mario.h"
	#include "audio/external.h"
}
#include "object_fields.h"
void DimSphereMusicPrev::Init(){
	isMarioInRadius = false;
}
void DimSphereMusicPrev::Step()
{	
	if(this->oDistanceToMario < 750.f && isMarioInRadius == false){
		isMarioInRadius = true;
		play_secondary_music(this->oBehParams2ndByte, 10, 40, 200);
	}
	else if(this->oDistanceToMario >749.f && isMarioInRadius == true){
		isMarioInRadius = false;
		func_80321080(300);
	}
}

// This is really simple behavior script, for behavior script documentation you may check hack64
uintptr_t DimSphereMusicPrev::Behavior[] = 
{
	0x11010041,
	0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};