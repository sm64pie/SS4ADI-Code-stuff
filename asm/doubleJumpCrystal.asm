.orga 0x01202A50

; --Function-wrapper-start--
addiu sp, sp, 0xFFE8
sw ra, 0x14(sp)
sw s0, 0x10(sp)
sw s1, 0x0C(sp)
; --------------------------

; s0: Address of the Mario Object struct
; &marioState.marioObj = 0x8033B170 + 0x88 = 0x8033B1F8
lui s0, 0x8034
lw s0, 0xB1F8(s0)
; s1: Address of the current Object struct
; stored at 0x80361160
lui s1, 0x8036
lw s1, 0x1160(s1)

; Rotate object model
; Load current faceYaw
; oFaceAngleYaw offset relative to curObj = 0x0D4
lw t0, 0x0D4(s1)
; Add a constant angle
ori t1, r0, 0x0200
addu t0, t0, t1
; Store back the value
sw t0, 0x0D4(s1)

; Add sine wave offset in the Y position
; Load oTimer (offset 0x154) and convert into a float
lw t0, 0x154(s1)
mtc1 t0, f12
cvt.s.w f12, f12
; Multiply by the pulsation of the oscillation
; pulsation = 2 pi / period
ori t0, r0, 15 ; 1 / pulsation
mtc1 t0, f1
cvt.s.w f1, f1
; Compute the sine
; Call to sinf (0x80325480)
; arg0 into f12 and result into f0
jal 0x80325480
div.s f12, f12, f1 ; sine input = pulsation * t
; Multiply by the amplitude
ori t0, r0, 10 ; Amplitude
mtc1 t0, f1
cvt.s.w f1, f1
mul.s f0, f0, f1
; Store to oGraphYOffset (offset 0x0DC)
swc1 f0, 0x0DC(s1)

; Check if object is active (counter strored in curObj.unused2 == 0)
; unused2 field has offset 0x210
lw t0, 0x210(s1)
beq t0, r0, active

; Spawn particles every 4 frames
; spawn_sparkle_particles(1, 2, 70, -100)
andi t1, t0, 0x0003
bne t1, r0, noParticles
ori a0, r0, 1
ori a1, r0, 2
ori a2, r0, 70
jal 0x802B2BC8
ori a3, r0, -100

noParticles:

; Decrement counter stored in curObj.usused2 (offset 0x210)
lw t0, 0x210(s1)
addi t0, t0, 0xFFFF
bne t0, r0, noCollision
sw t0, 0x210(s1)

; Enable object rendering if object becomes active
; curObj.header.gfx.node.flags |= GRAPH_RENDER_ACTIVE
; flags offset relative to curObj = 0x02
; GRAPH_RENDER_ACTIVE = 0x0001
lh t0, 0x02(s1)
ori t0, t0, 0x0001
sh t0, 0x02(s1)

beq r0, r0, noCollision

active:

; Check for collision
; arg1 is a pointer to the Mario Object struct
; arg2 is a pointer to the current object (stored at 0x80361160)
; Call to obj_check_if_collided_with_object (0x802A1424)
ori a0, s1, 0
jal 0x802A1424
ori a1, s0, 0
beq v0, r0, noCollision
nop

; Save 1 to marioObj.unused2 (offset 0x210)
; to give back the double jump ability
ori t1, r0, 1
sb t1, 0x210(s0)

; Set Mario in the freefall state
; arg0 is a pointer to the Mario struct (0x8033B170)
; arg1 is the state ACT_FREEFALL (0x0100088C)
; arg2 isn't necessery
; call to set_mario_action (0x80252CF4)
lui a0, 0x8034
addiu a0, a0, 0xB170
lui a1, 0x0100
jal 0x80252CF4
addiu a1, a1, 0x088C

; Set Mario's animation to falling
; arg0 is a pointer to the Mario struct (0x8033B170)
; arg1 is the annimation ID (MARIO_ANIM_GENERAL_FALL = 0x56)
lui a0, 0x8034
addiu a0, a0, 0xB170
jal 0x802509B8
ori a1, r0, 0x56

; Disable object rendering
; curObj.header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE
; flags offset relative to curObj = 0x02
; GRAPH_RENDER_ACTIVE = 0x0001
lh t0, 0x02(s1)
andi t0, t0, 0xFFFE
sh t0, 0x02(s1)

; Set cooldown counter
; Counter is stored in curObj.unused2 (offset 0x210)
ori t0, r0, 60 ; 60 frames = 2s
sw t0, 0x210(s1)

; Play sound effect
; arg0 is the sound ID (SOUND_MENU_STAR_SOUND = 0x701EFF80)
; arg1 is a pointer to the sound source position (&gGlobalSoundSource = 0x803331F0)
; Call to play_sound (0x8031EB00)
lui a0, 0x701E
ori a0, a0, 0xFF81
lui a1, 0x8033
jal 0x8031EB00
addiu a1, a1, 0x31F0

noCollision:

; --Function-wrapper-end----
lw s1, 0x0C(sp)
lw s0, 0x10(sp)
lw ra, 0x14(sp)
jr ra
addiu sp, sp, 0x18
; --------------------------