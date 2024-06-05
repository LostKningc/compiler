.data
.global x
x:
.word 1
.word 2
.zero 12
.word 1
.zero 8
.word 1

.text
.globl main
main:
addi sp, sp, -128
main_entry:
la    t0, x
li    t1, 3
slli  t1, t1, 2
add   t0, t0, t1
sw    t0, 0(sp)

lw    t0, 0(sp)
li    t1, 2
slli  t1, t1, 2
add   t0, t0, t1
sw    t0, 4(sp)

lw    t0, 4(sp)
lw    t0, 0(t0)
sw    t0, 8(sp)

lw    a0, 8(sp)
addi sp, sp, 128
ret

