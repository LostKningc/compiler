.data
.global __filed0__a
__filed0__a:
.word 10

.text
.globl main
inc:
addi sp, sp, -128
inc_entry:
la    t0, __filed0__a
lw    t0, 0(t0)
sw    t0, 0(sp)

lw    t1, 0(sp)
addi  t0, t1, 1
sw    t0, 4(sp)

lw    t0, 4(sp)
sw    t0, 0(sp)

la    t0, __filed0__a
lw    t0, 0(t0)
sw    t0, 8(sp)

lw    a0, 8(sp)
addi sp, sp, 128
ret

print_a:
addi sp, sp, -128
sw ra, 124(sp)
print_a_entry:
la    t0, __filed0__a
lw    t0, 0(t0)
sw    t0, 0(sp)

sw    a0, 44(sp)
lw    a0, 0(sp)
call  putint
lw    a0, 44(sp)

li    t0, 10
sw    t0, 4(sp)

sw    a0, 44(sp)
lw    a0, 4(sp)
call  putch
lw    a0, 44(sp)

lw ra, 124(sp)
addi sp, sp, 128
ret

main:
addi sp, sp, -160
sw ra, 156(sp)
main_entry:

li    t0, 0
sw    t0, 0(sp)

j     main_while_entry0

main_while_entry0:
lw    t0, 0(sp)
sw    t0, 4(sp)

lw    t1, 4(sp)
li    t2, 10
slt   t0, t1, t2
sw    t0, 8(sp)

lw    t0, 8(sp)
beqz  t0, main_while_end0
j     main_while_body0

main_while_body0:
call  inc
sw    a0, 12(sp)


li    t0, 1
sw    t0, 16(sp)

lw    t0, 16(sp)
sw    t0, 20(sp)

lw    t1, 20(sp)
addi  t0, t1, 2
sw    t0, 24(sp)

lw    t0, 24(sp)
sw    t0, 16(sp)

lw    t0, 16(sp)
sw    t0, 28(sp)

sw    a0, 76(sp)
lw    a0, 28(sp)
call  putint
lw    a0, 76(sp)

li    t0, 10
sw    t0, 32(sp)

sw    a0, 76(sp)
lw    a0, 32(sp)
call  putch
lw    a0, 76(sp)

call  print_a

lw    t0, 0(sp)
sw    t0, 36(sp)

lw    t1, 36(sp)
addi  t0, t1, 1
sw    t0, 40(sp)

lw    t0, 40(sp)
sw    t0, 0(sp)

j     main_while_entry0

main_while_end0:
li    a0, 0
lw ra, 156(sp)
addi sp, sp, 160
ret

