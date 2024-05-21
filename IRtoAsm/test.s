.text
.globl main
main:
li    t0, 1
li    t1, 2
li    t2, 3
xori  t3, t2, 0
seqz  t3, t3
li    t2, 4
xori  t4, t2, 0
seqz  t4, t4
xori  t2, t4, 0
seqz  t2, t2
xori  t4, t3, 0
seqz  t4, t4
xori  t3, t4, 0
seqz  t3, t3
or    t4, t3, t2
mul   t2, t1, t4
add   t4, t0, t2
li    t2, 5
slt   t0, t4, t2
li    t2, 6
xor   t4, t0, t2
snez  t4, t4
li    t2, 7
sub   t0, x0, t2
xori  t2, t0, 0
seqz  t2, t2
xori  t0, t2, 0
seqz  t0, t0
xori  t2, t4, 0
seqz  t2, t2
xori  t4, t2, 0
seqz  t4, t4
and   t2, t4, t0
mv    a0, t2
ret
