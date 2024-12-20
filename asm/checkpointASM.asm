.headersize 0x80245000

; notes about the spaces to put code in
; there is space in rom from 0x7cc6c0 to 0x800000
; there is space in ram from 0x80367500 to 0x80378700 (can fit in 17536 lines)

.definelabel code_rom, 0x7cc6c0; where your code goes in the rom
.definelabel code_ram, 0x80367500; where your code goes in the ram

.orga 0x396c; here it copies code into the ram at start up
li a0, code_ram
li a1, code_rom
li.u a2, code_end_copy
jal 0x80278504
li.l a2, code_end_copy
jal execonce
nop

.orga 0xfd354
jal execeveryframe
nop

.orga 0x15f4
jal execeveryframe2
nop

.orga 0x21aeb8
.dw 0x00040000
.dw 0x11010041
.dw 0x102A0040
.dw 0x08000000
.dw 0x0C000000
.dw customMop3Objasm
.dw 0x09000000

.orga 0xde270; responsible for running every VI frames
b 0x803232a4
sw t4, 0x7110(at)
.skip 28
lw ra, 0x1c(sp)
lw s0, 0x18(sp)
jr ra
addiu sp, sp, 0x38
lb s7, code_ram
nop
beqz s7, @@skip_vi_frames
nop
add s5, r0, ra
jal execviframes
nop
@@skip_vi_frames:
b 0x80323278
lui at, 0x8036

.headersize (code_ram - code_rom)

.orga code_rom
execonce:
addiu sp, sp, 0xffec; don't get rid of those extra things. they are needed
sw ra, 0xc(sp)

; executes once here at start up


or a0, r0, r0; don't get rid of those extra things. they are needed
jal 0x80277ee0
lui a1, 0x8000
lui a0, 0x8034
lui a1, 0x8034
addiu a1, a1, 0xb044
addiu a0, a0, 0xb028
jal 0x803225a0
addiu a2, r0, 0x1
lw ra, 0xc(sp)
jr ra
addiu sp, sp, 0x14

execeveryframe:
addiu sp, sp, 0xffe8; don't get rid of those extra things. they are needed
sw ra, 0x14(sp)

; your code that runs every frame here
; this "execeveryframe" allows you to operate with floats but might be slightly inaccurate with running every frame

addiu t6, r0, 0x1; don't get rid of those extra things. they are needed
lui at, 0x8039
lw ra, 0x14(sp)
jr ra
addiu sp, sp, 0x18

execeveryframe2:
addiu sp, sp, 0xffe8
sw ra, 0x14(sp)

; runs every frame here
; can't use floats here (don't ask why u just can't)
; but more accurate on running every frame than execeveryframe

lui t6, 0x8033
lw ra, 0x14(sp)
jr ra
addiu sp, sp, 0x18

execviframes:
addiu sp, sp, 0xffe8
sw ra, 0x18(sp)
sw s5, 0x14(sp)

; your code that runs every vi frame here

lw ra, 0x18(sp)
addiu sp, sp, 0x18
jr ra
lw ra, 0x14(sp)

customMop3Objasm:
ADDIU SP, SP, 0xFFE8
SW RA, 0x14(SP)

LUI A0, 0x8036
LW A1, 0x1158(A0)
JAL 0x802A1424
LW A0, 0x1160(A0)
BEQZ V0, Branch1 ;0x7CC80C ;checks if collided with object
NOP

LUI A0, 0x8036
LW A0, 0x1160(A0)
LW T2, 0x144(A0)
BNEZ T2, Branch2 ;0x7CC7DC ;checks if subtype is 0
NOP

LUI AT, 0x8040
ADDIU T3, R0, 1
LW A3, 0x10(AT) ;loads checkpoint state for later use
SW T3, 0x10(AT) ;sets checkpoint to enabled state

LWC1 F2, 0xA0(A0)
SWC1 F2, 0x14(AT)
LWC1 F2, 0xA4(A0) ;stores checkpoint XYZ position in RAM
SWC1 F2, 0x18(AT)
LWC1 F2, 0xA8(A0)
SWC1 F2, 0x1C(AT)

LUI T3, 0x8034
LUI T4, 0x8036
LB T5, 0xB249(T3)
SB T5, 0x7750(T4) ;stores current level and area
LB T5, 0xB24A(T3)
SB T5, 0x7751(T4)

LUI T1, 0x8060
LUI AT, 0xB886
ORI AT, AT, 0xBFF
SW AT, 0x4400(T1) ;no idea what any of this does
LUI AT, 0x4818
ORI AT, AT, 0x1FF
SW AT, 0x4408(T1)

BNEZ A3, Branch1 ;0x7CC80C checks if checkpoint is enabled
NOP

LUI A0, 0x306A
JAL 0x802CA144
ORI A0, A0, 0x81 ;makes checkpoint sound
B Branch1 ;0x7CC80C
NOP

Branch2:
LUI AT, 0x8040
SW R0, 0x14(AT)
SW R0, 0x18(AT)
SW R0, 0x1C(AT)
SW R0, 0x10(AT)
LUI T1, 0x8060 ;resets checkpoint state and positions
LUI AT, 0xFFFF
ORI AT, AT, 0xFFFF
SW AT, 0x4400(T1)
LUI AT, 0x7F7F
ORI AT, AT, 0x7FFF
SW AT, 0x4408(T1)

LUI T4, 0x8036
SH R0, 0x7750(T4) ;resets stored level and area

Branch1:
LUI A0, 0x8036
LW A0, 0x1160(A0)
LW T2, 0x144(A0)
SW R0, 0x9C(A0)
SW R0, 0x134(A0)
LUI AT, 0x42C8
SW AT, 0x1F8(A0)
LUI AT, 0x441C
SW AT, 0x1FC(A0)
BEQZ T2, Branch3 ;0x7CC84C ;check if subtype is 0
NOP

LUI AT, 0x441C
SW AT, 0x1F8(A0)
LUI AT, 0x8000 ;no idea what any of this does
SW AT, 0x130(A0)
SW R0, 0x14(A0)

Branch3:
BNEZ T2, Branch4 ;0x7CC898 ;check if subtype is 0
NOP

LW T2, 0x154(A0)
BNEZ T2, Branch4 ;0x7CC898 ;check if obj timer is 0 so it only happens once
NOP

LUI AT, 0x8040
LW T2, 0x10(AT) ;check if checkpoint is in active state
BEQZ T2, Branch4 ;0x7CC898

LUI T3, 0x8034
LUI T4, 0x8036
LB T5, 0xB249(T3)
LB T6, 0x7750(T4) ;checks current level and area
BNE T5, T6, Branch4
NOP
LB T5, 0xB24A(T3)
LB T6, 0x7751(T4)
BNE T5, T6, Branch4
NOP

LUI T4, 0x8034
LWC1 F2, 0x14(AT)
LUI T6, 0x42C8
MTC1 T6, F4
ADD.S F2, F2, F4
SWC1 F2, 0xB1AC(T4)
LWC1 F2, 0x18(AT)
SWC1 F2, 0xB1B0(T4) ;set mario's xyz position to stored values
LWC1 F2, 0x1C(AT)
SWC1 F2, 0xB1B4(T4)

Branch4:
LW RA, 0x14(SP)
JR RA
ADDIU SP, SP, 0x18

code_end:
.definelabel code_end_copy, (code_end - (code_ram - code_rom))