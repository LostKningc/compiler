.data
.global __filed0__ga
__filed0__ga:
.zero 40

.global __filed0__gb
__filed0__gb:
.word 5
.word 6
.word 7
.word 8
.zero 8

.text
.globl main
main:
addi sp, sp, -352
main_entry:
li    t0, 4
add   t0, t0, sp
sw    t0, 0(sp)

lw    t0, 0(sp)
lw    t1, 0(sp)
sw    t0, 0(t1)

li    t0, 48
add   t0, t0, sp
sw    t0, 44(sp)

lw    t0, 0(sp)
lw    t1, 44(sp)
sw    t0, 0(t1)

li    t0, 76
add   t0, t0, sp
sw    t0, 72(sp)

li    t0, 0
lw    t1, 72(sp)
sw    t0, 0(t1)

li    t0, 84
add   t0, t0, sp
sw    t0, 80(sp)

li    t0, 0
lw    t1, 80(sp)
sw    t0, 0(t1)

j     main_while_entry0

main_while_entry0:
lw    t0, 80(sp)
lw    t0, 0(t0)
sw    t0, 88(sp)

lw    t1, 88(sp)
li    t2, 2
slt   t0, t1, t2
sw    t0, 92(sp)

lw    t0, 92(sp)
beqz  t0, main_while_end0
j     main_while_body0

main_while_body0:
li    t0, 100
add   t0, t0, sp
sw    t0, 96(sp)

li    t0, 0
lw    t1, 96(sp)
sw    t0, 0(t1)

j     main_while_entry1

main_while_end0:
li    t0, 0
lw    t1, 80(sp)
sw    t0, 0(t1)

j     main_while_entry2

main_while_entry1:
lw    t0, 96(sp)
lw    t0, 0(t0)
sw    t0, 104(sp)

lw    t1, 104(sp)
li    t2, 3
slt   t0, t1, t2
sw    t0, 108(sp)

lw    t0, 108(sp)
beqz  t0, main_while_end1
j     main_while_body1

main_while_entry2:
lw    t0, 80(sp)
lw    t0, 0(t0)
sw    t0, 112(sp)

lw    t1, 112(sp)
li    t2, 10
slt   t0, t1, t2
sw    t0, 116(sp)

lw    t0, 116(sp)
beqz  t0, main_while_end2
j     main_while_body2

main_while_body1:
lw    t0, 72(sp)
lw    t0, 0(t0)
sw    t0, 120(sp)

lw    t0, 80(sp)
lw    t0, 0(t0)
sw    t0, 124(sp)

lw    t0, 96(sp)
lw    t0, 0(t0)
sw    t0, 128(sp)

lw    t0, 44(sp)
lw    t1, 124(sp)
slli  t1, t1, 2
add   t0, t0, t1
sw    t0, 132(sp)

lw    t0, 132(sp)
lw    t1, 128(sp)
slli  t1, t1, 2
add   t0, t0, t1
sw    t0, 136(sp)

lw    t0, 136(sp)
lw    t0, 0(t0)
sw    t0, 140(sp)

lw    t1, 120(sp)
lw    t2, 140(sp)
add   t0, t1, t2
sw    t0, 144(sp)

lw    t0, 80(sp)
lw    t0, 0(t0)
sw    t0, 148(sp)

lw    t0, 96(sp)
lw    t0, 0(t0)
sw    t0, 152(sp)

la    t0, __filed0__gb
lw    t2, 148(sp)
slli  t2, t2, 2
add   t0, t0, t2
sw    t0, 156(sp)

lw    t0, 156(sp)
lw    t2, 152(sp)
slli  t2, t2, 2
add   t0, t0, t2
sw    t0, 160(sp)

lw    t0, 160(sp)
lw    t0, 0(t0)
sw    t0, 164(sp)

lw    t2, 144(sp)
lw    t1, 164(sp)
add   t0, t2, t1
sw    t0, 168(sp)

lw    t0, 168(sp)
lw    t1, 72(sp)
sw    t0, 0(t1)

lw    t0, 96(sp)
lw    t0, 0(t0)
sw    t0, 172(sp)

lw    t1, 172(sp)
addi  t0, t1, 1
sw    t0, 176(sp)

lw    t0, 176(sp)
lw    t1, 96(sp)
sw    t0, 0(t1)

j     main_while_entry1

main_while_end1:
lw    t0, 80(sp)
lw    t0, 0(t0)
sw    t0, 180(sp)

lw    t1, 180(sp)
addi  t0, t1, 1
sw    t0, 184(sp)

lw    t0, 184(sp)
lw    t1, 80(sp)
sw    t0, 0(t1)

j     main_while_entry0

main_while_body2:
lw    t0, 80(sp)
lw    t0, 0(t0)
sw    t0, 188(sp)

lw    t0, 0(sp)
lw    t1, 188(sp)
slli  t1, t1, 2
add   t0, t0, t1
sw    t0, 192(sp)

lw    t0, 72(sp)
lw    t0, 0(t0)
sw    t0, 196(sp)

lw    t0, 80(sp)
lw    t0, 0(t0)
sw    t0, 200(sp)

lw    t1, 196(sp)
lw    t2, 200(sp)
add   t0, t1, t2
sw    t0, 204(sp)

lw    t0, 204(sp)
lw    t2, 192(sp)
sw    t0, 0(t2)

lw    t0, 80(sp)
lw    t0, 0(t0)
sw    t0, 208(sp)

la    t0, __filed0__ga
lw    t2, 208(sp)
slli  t2, t2, 2
add   t0, t0, t2
sw    t0, 212(sp)

lw    t0, 72(sp)
lw    t0, 0(t0)
sw    t0, 216(sp)

lw    t0, 80(sp)
lw    t0, 0(t0)
sw    t0, 220(sp)

lw    t2, 216(sp)
lw    t1, 220(sp)
add   t0, t2, t1
sw    t0, 224(sp)

lw    t0, 224(sp)
lw    t1, 212(sp)
sw    t0, 0(t1)

lw    t0, 80(sp)
lw    t0, 0(t0)
sw    t0, 228(sp)

lw    t1, 228(sp)
addi  t0, t1, 1
sw    t0, 232(sp)

lw    t0, 232(sp)
lw    t1, 80(sp)
sw    t0, 0(t1)

j     main_while_entry2

main_while_end2:
lw    t0, 72(sp)
lw    t0, 0(t0)
sw    t0, 236(sp)

lw    a0, 236(sp)
addi sp, sp, 352
ret

