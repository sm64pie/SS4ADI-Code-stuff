/*
 This file is contains the entry point for linker
 Linker will take _start and put it at the very beginning at 1208000 (or any other address you prefer)
*/
#include "fail_warp.h"


// This is trampoline to behavior script that will just define the list and jump to Behavior in object
#define REGISTER_BEHAVIOR(list, obj) list, 0x04000000, (uintptr_t) VIRTUAL_TO_PHYSICAL2(obj::Behavior)

/* 
 I know I defined the same object multiple times, it is made just for the showcase purposes.
 Delete them if you dont need it.

 Every time you define an object, you need to add up '+0xC' to address get its behavior script address
 Generally lists 0x00090000 and 0x00040000 are used
 */
//int _start[] = {
	//REGISTER_BEHAVIOR(0x00040000, b3ss4Control)
    //REGISTER_BEHAVIOR(0x00090000, DonutPlatform) // 408000
	//REGISTER_BEHAVIOR(0x00040000, WhompKing)
//};

/*
 Dont forget to register new cpp files in Makefile.
 Generally linker will say it cant fine objectName::Behavior if you forget to add the file

 If you want to relocate the compiled asm files, you need to change _2_ variables
 In Makefile change ROM_OFFSET (in dec) where to put files
 In ldscript change sm64 0x80408000 to where in RAM data will be put
 Currently data is put at 0x1208000=0x80408000
 */
 uintptr_t _start[] =
 {
    (uintptr_t) marioSetSafePos,
    (uintptr_t) areaGetWarpNode,
    (uintptr_t) preLevelTriggerWarp,
	(uintptr_t) initMarioAfterQuickWarp,
	(uintptr_t) initMarioAfterQuickWarpResetCamera,
 };