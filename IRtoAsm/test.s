.text
.globl main
main:
addi sp, sp, -32
entry:

li    t0, 2
sw    t0, 0(sp)

lw    t0, 0(sp)
sw    t0, 4(sp)

lw    t0, 4(sp)
beqz  t0, else
j     then

then:
lw    t0, 0(sp)
sw    t0, 8(sp)

lw    t1, 8(sp)
addi  t0, t1, 1
sw    t0, 12(sp)

lw    t0, 12(sp)
sw    t0, 0(sp)

j     end

else:
li    t0, 0
sw    t0, 0(sp)

j     end

end:
lw    t0, 0(sp)
sw    t0, 16(sp)

lw    a0, 16(sp)
addi sp, sp, 32
ret

