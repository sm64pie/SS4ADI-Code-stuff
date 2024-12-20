; devwizard's Mirror Patch

; The default values for these variables match the original values in SM64, so
; assembling this to a ROM will result in no change, or will undo a previous
; application of this patch.

; Command to add for the mirror: 18 00 0000 80277B14

; MIRROR_AXIS
;   This sets the axis that is mirrored across.
; MIRROR_ORIGIN
;   This sets the position of the mirror on the mirror axis.
; MIRROR_CHECK_ENABLE
;   This enables or disables a checks with Mario's X/Y/Z position against 
;   MIRROR_CHECK_POS
; MIRROR_CHECK_TYPE
;   This sets the type of check against Mario's X/Y/Z position
;   LT: mario_x < MIRROR_CHECK_POS
;   GT: mario_x > MIRROR_CHECK_POS
;   GE: mario_x >= MIRROR_CHECK_POS
;   LE: mario_x <= MIRROR_CHECK_POS
; MIRROR_CHECK_POS
;   This is what Mario's X/Y/Z position is checked against if
;   MIRROR_CHECK_ENABLE is not 0

MIRROR_AXIS             equ MIRROR_AXIS_Z
MIRROR_ORIGIN           equ -750
MIRROR_CHECK_ENABLE     equ 0
MIRROR_CHECK_TYPE       equ MIRROR_CHECK_GT
MIRROR_CHECK_POS        equ 7211

; ==============================================================================
; DO NOT MODIFY ANYTHING BELOW THESE LINES
; THE SETTINGS FOR THIS PATCH ARE RIGHT ABOVE THIS
; ==============================================================================

.definelabel MIRROR_AXIS_X, 0x00
.definelabel MIRROR_AXIS_Y, 0x04
.definelabel MIRROR_AXIS_Z, 0x08
.definelabel MIRROR_CHECK_LT, 0x00
.definelabel MIRROR_CHECK_GT, 0x01
.definelabel MIRROR_CHECK_GE, 0x02
.definelabel MIRROR_CHECK_LE, 0x03
.org 0x00032BEC
    .if MIRROR_CHECK_ENABLE
        .if (MIRROR_CHECK_TYPE & 0x01)
            c.lt.s  f6, f4
            nop
        .else
            c.lt.s  f4, f6
            nop
        .endif
        .if (MIRROR_CHECK_TYPE & 0x02)
            bc1t    0x00032D28
            nop
        .else
            bc1f    0x00032D28
            nop
        .endif
    .else
        nop
        nop
        nop
        nop
    .endif
.org 0x00032CA0
    lwc1    f10, (0x20+MIRROR_AXIS)(t0)
.org 0x00032CDC
    swc1    f18, (0x20+MIRROR_AXIS)(t1)
.org 0x00032CE0
    .if (MIRROR_AXIS == MIRROR_AXIS_Y)
        nop
        nop
        nop
        nop
        nop
    .endif
.org 0x00032D04
    lwc1    f4, (0x2C+MIRROR_AXIS)(t8)
.org 0x00032D0C
    swc1    f10, (0x2C+MIRROR_AXIS)(t8)
.org 0x000F1F58
    .float MIRROR_CHECK_POS
.org 0x000F1F60
    .double MIRROR_ORIGIN
.org 0x000F1F68
    .double MIRROR_ORIGIN
