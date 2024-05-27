.data
.global var
var:
.zero 4

.global var1
var1:
.word 12

.text
.globl main
main:
addi sp, sp, -128
main_entry:
la    t0, var
lw    t0, 0(t0)
sw    t0, 0(sp)

lw    t1, 0(sp)
addi  t0, t1, 1
sw    t0, 4(sp)

la    t0, var1
lw    t0, 0(t0)
sw    t0, 8(sp)

lw    t1, 4(sp)
lw    t2, 8(sp)
add   t0, t1, t2
sw    t0, 12(sp)

lw    a0, 8(sp)
addi sp, sp, 128
ret

