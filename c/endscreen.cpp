#include "endscreen.h"

extern "C"
{
    #include "game/camera.h"
    #include "game/display.h"
    #include "game/game.h"
    #include "game/mario.h"
    #include "game/object_helpers.h"
	#include "game/object_helpers2.h"
    #include "game/level_update.h"
    #include "game/print.h"
    #include "engine/math_util.h"
	#include "game/mario_actions_cutscene.h"
	#include "game/ingame_menu.h"
    
    void set_camera_mode_8_directions(struct Camera *c);
}
#define isDialogOver OBJECT_FIELD_S32(0x1b)
#define isThankYouActive OBJECT_FIELD_S32(0x1c)
#define SHOW_TEXT_TIME 40
#define ALLOW_L_PRESS 145
#define FRAMES_PER_LETTER 2

void Endscreen::Init()
{
    auto o = gCurrentObject;
    set_cam_angle(2); // lakitu cam
    gHudDisplay.flags = HUD_DISPLAY_NONE;
    o->oHealth = 0;
	isDialogOver = false;
	isThankYouActive = false;
}

static void printFancy(int yoff, const char* str, int renderLimit)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }

    int symbolLen = 11;
    int halfLen = len / 2;
    int x = 160 - halfLen * symbolLen;
    for (int i = 0; i < len; i++)
    {
        if ((renderLimit -= FRAMES_PER_LETTER) < 0)
            break;

        int yoff2 = sins(gGlobalTimer * 0x400 + i * 0x700) * 5;

        if (' ' == str[i])
        {
            continue;
        }

        char strProcessed[2] = { str[i], '\0' };
        print_text_centered(x + i * symbolLen, 30 - 20 * yoff + yoff2, strProcessed);
    }
}

void Endscreen::Step()
{
    auto m = gMarioStates;
    auto o = gCurrentObject;
    o->oHealth++;
	if (isDialogOver == false){
		create_dialog_box(0x7A);
		isDialogOver = true;
		o->oTimer = 0;
	}
	else{
		if (o->oTimer > 600){
			printFancy(0, "THE END", o->oHealth - SHOW_TEXT_TIME);
			printFancy(1, "THANKS FOR PLAYING", o->oHealth - SHOW_TEXT_TIME);
		}
	}

    set_mario_action(m, 0, 0);
    gMarioObject->header.gfx.sharedChild = gLoadedGraphNodes[0];
    gPlayer1Controller->buttonDown = 0;
    gPlayer1Controller->buttonPressed = 0;
    gPlayer1Controller->stickX = 0;
    gPlayer1Controller->stickY = 0;
    gPlayer1Controller->rawStickX = 0;
    gPlayer1Controller->rawStickY = 0;
    auto camera = gCurrentArea->camera;
    set_camera_mode_8_directions(camera);
    reset_camera(camera);
}

uintptr_t Endscreen::Behavior[] = 
{
	0x0C000000, (uintptr_t) sInit,
    0x08000000,
    0x0C000000, (uintptr_t) sStep,
    0x09000000,
};