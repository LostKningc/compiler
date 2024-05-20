.text
.globl main
main:
li    t0, 3
li    t2, 6
sgt   t1, t2, t0
seqz  t1, t1
li    t2, 8388607
xori  t3, t2, -1
seqz  t3, t3
xori  t4, t2, 0
snez  t4, t4
mv    a0, t3
ret
