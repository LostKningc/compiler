.data
.text
.globl main
init:
addi sp, sp, -240
init_entry:
li    t0, 4
add   t0, t0, sp
sw    t0, 0(sp)

li    t0, 0
lw    t1, 0(sp)
sw    t0, 0(t1)

j     init_while_entry0

init_while_entry0:
lw    t0, 0(sp)
lw    t0, 0(t0)
sw    t0, 8(sp)

lw    t1, 8(sp)
li    t2, 10
slt   t0, t1, t2
sw    t0, 12(sp)

lw    t0, 12(sp)
beqz  t0, init_while_end0
j     init_while_body0

init_while_body0:
li    t0, 20
add   t0, t0, sp
sw    t0, 16(sp)

li    t0, 0
lw    t1, 16(sp)
sw    t0, 0(t1)

j     init_while_entry1

init_while_end0:
addi sp, sp, 240
ret

init_while_entry1:
lw    t0, 16(sp)
lw    t0, 0(t0)
sw    t0, 24(sp)

lw    t1, 24(sp)
li    t2, 10
slt   t0, t1, t2
sw    t0, 28(sp)

lw    t0, 28(sp)
beqz  t0, init_while_end1
j     init_while_body1

init_while_body1:
li    t0, 36
add   t0, t0, sp
sw    t0, 32(sp)

li    t0, 0
lw    t1, 32(sp)
sw    t0, 0(t1)

j     init_while_entry2

init_while_end1:
lw    t0, 0(sp)
lw    t0, 0(t0)
sw    t0, 40(sp)

lw    t1, 40(sp)
addi  t0, t1, 1
sw    t0, 44(sp)

lw    t0, 44(sp)
lw    t1, 0(sp)
sw    t0, 0(t1)

j     init_while_entry0

init_while_entry2:
lw    t0, 32(sp)
lw    t0, 0(t0)
sw    t0, 48(sp)

lw    t1, 48(sp)
li    t2, 10
slt   t0, t1, t2
sw    t0, 52(sp)

lw    t0, 52(sp)
beqz  t0, init_while_end2
j     init_while_body2

init_while_body2:
lw    t0, 0(sp)
lw    t0, 0(t0)
sw    t0, 56(sp)

lw    t0, 16(sp)
lw    t0, 0(t0)
sw    t0, 60(sp)

lw    t0, 32(sp)
lw    t0, 0(t0)
sw    t0, 64(sp)

mv    t0, a0
lw    t1, 56(sp)
li    t2, 100
mul   t1, t1, t2
slli  t2, t1, 2
add   t0, t0, t2
sw    t0, 68(sp)

lw    t0, 68(sp)
lw    t1, 60(sp)
li    t2, 10
mul   t1, t1, t2
slli  t2, t1, 2
add   t0, t0, t2
sw    t0, 72(sp)

lw    t0, 72(sp)
lw    t1, 64(sp)
li    t2, 1
mul   t1, t1, t2
slli  t2, t1, 2
add   t0, t0, t2
sw    t0, 76(sp)

lw    t0, 0(sp)
lw    t0, 0(t0)
sw    t0, 80(sp)

lw    t1, 80(sp)
li    t2, 100
mul   t0, t1, t2
sw    t0, 84(sp)

lw    t0, 16(sp)
lw    t0, 0(t0)
sw    t0, 88(sp)

lw    t1, 88(sp)
li    t2, 10
mul   t0, t1, t2
sw    t0, 92(sp)

lw    t1, 84(sp)
lw    t2, 92(sp)
add   t0, t1, t2
sw    t0, 96(sp)

lw    t0, 32(sp)
lw    t0, 0(t0)
sw    t0, 100(sp)

lw    t2, 96(sp)
lw    t1, 100(sp)
add   t0, t2, t1
sw    t0, 104(sp)

lw    t0, 104(sp)
lw    t1, 76(sp)
sw    t0, 0(t1)

lw    t0, 32(sp)
lw    t0, 0(t0)
sw    t0, 108(sp)

lw    t1, 108(sp)
addi  t0, t1, 1
sw    t0, 112(sp)

lw    t0, 112(sp)
lw    t1, 32(sp)
sw    t0, 0(t1)

j     init_while_entry2

init_while_end2:
lw    t0, 16(sp)
lw    t0, 0(t0)
sw    t0, 116(sp)

lw    t1, 116(sp)
addi  t0, t1, 1
sw    t0, 120(sp)

lw    t0, 120(sp)
lw    t1, 16(sp)
sw    t0, 0(t1)

j     init_while_entry1

f1:
addi sp, sp, -240
f1_entry:
mv    t0, a0
li    t1, 0
slli  t2, t1, 2
add   t0, t0, t2
sw    t0, 0(sp)

lw    t0, 0(sp)
lw    t0, 0(t0)
sw    t0, 4(sp)

mv    t0, a1
li    t1, 1
slli  t2, t1, 2
add   t0, t0, t2
sw    t0, 8(sp)

lw    t0, 8(sp)
lw    t0, 0(t0)
sw    t0, 12(sp)

lw    t1, 4(sp)
lw    t2, 12(sp)
add   t0, t1, t2
sw    t0, 16(sp)

mv    t0, a2
li    t2, 2
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 20(sp)

lw    t0, 20(sp)
lw    t0, 0(t0)
sw    t0, 24(sp)

lw    t2, 16(sp)
lw    t1, 24(sp)
add   t0, t2, t1
sw    t0, 28(sp)

mv    t0, a3
li    t1, 3
slli  t2, t1, 2
add   t0, t0, t2
sw    t0, 32(sp)

lw    t0, 32(sp)
lw    t0, 0(t0)
sw    t0, 36(sp)

lw    t1, 28(sp)
lw    t2, 36(sp)
add   t0, t1, t2
sw    t0, 40(sp)

mv    t0, a4
li    t2, 4
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 44(sp)

lw    t0, 44(sp)
lw    t0, 0(t0)
sw    t0, 48(sp)

lw    t2, 40(sp)
lw    t1, 48(sp)
add   t0, t2, t1
sw    t0, 52(sp)

mv    t0, a5
li    t1, 5
slli  t2, t1, 2
add   t0, t0, t2
sw    t0, 56(sp)

lw    t0, 56(sp)
lw    t0, 0(t0)
sw    t0, 60(sp)

lw    t1, 52(sp)
lw    t2, 60(sp)
add   t0, t1, t2
sw    t0, 64(sp)

mv    t0, a6
li    t2, 6
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 68(sp)

lw    t0, 68(sp)
lw    t0, 0(t0)
sw    t0, 72(sp)

lw    t2, 64(sp)
lw    t1, 72(sp)
add   t0, t2, t1
sw    t0, 76(sp)

mv    t0, a7
li    t1, 7
slli  t2, t1, 2
add   t0, t0, t2
sw    t0, 80(sp)

lw    t0, 80(sp)
lw    t0, 0(t0)
sw    t0, 84(sp)

lw    t1, 76(sp)
lw    t2, 84(sp)
add   t0, t1, t2
sw    t0, 88(sp)

lw    t0, 240(sp)
li    t2, 8
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 92(sp)

lw    t0, 92(sp)
lw    t0, 0(t0)
sw    t0, 96(sp)

lw    t2, 88(sp)
lw    t1, 96(sp)
add   t0, t2, t1
sw    t0, 100(sp)

lw    t0, 244(sp)
li    t1, 9
slli  t2, t1, 2
add   t0, t0, t2
sw    t0, 104(sp)

lw    t0, 104(sp)
lw    t0, 0(t0)
sw    t0, 108(sp)

lw    t1, 100(sp)
lw    t2, 108(sp)
add   t0, t1, t2
sw    t0, 112(sp)

lw    a0, 112(sp)
addi sp, sp, 240
ret

f2:
addi sp, sp, -256
f2_entry:
li    t0, 4
add   t0, t0, sp
sw    t0, 0(sp)

lw    t0, 0(sp)
sw    a2, 0(t0)

li    t0, 12
add   t0, t0, sp
sw    t0, 8(sp)

lw    t0, 256(sp)
lw    t2, 8(sp)
sw    t0, 0(t2)

mv    t0, a0
li    t2, 0
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 16(sp)

lw    t0, 16(sp)
li    t2, 9
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 20(sp)

lw    t0, 20(sp)
lw    t0, 0(t0)
sw    t0, 24(sp)

mv    t0, a1
li    t2, 1
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 28(sp)

lw    t0, 28(sp)
lw    t0, 0(t0)
sw    t0, 32(sp)

lw    t2, 24(sp)
lw    t1, 32(sp)
add   t0, t2, t1
sw    t0, 36(sp)

lw    t0, 0(sp)
lw    t0, 0(t0)
sw    t0, 40(sp)

lw    t1, 36(sp)
lw    t2, 40(sp)
add   t0, t1, t2
sw    t0, 44(sp)

mv    t0, a3
li    t2, 3
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 48(sp)

lw    t0, 48(sp)
lw    t0, 0(t0)
sw    t0, 52(sp)

lw    t2, 44(sp)
lw    t1, 52(sp)
add   t0, t2, t1
sw    t0, 56(sp)

mv    t0, a4
li    t1, 4
slli  t2, t1, 2
add   t0, t0, t2
sw    t0, 60(sp)

lw    t0, 60(sp)
lw    t0, 0(t0)
sw    t0, 64(sp)

lw    t1, 56(sp)
lw    t2, 64(sp)
add   t0, t1, t2
sw    t0, 68(sp)

mv    t0, a5
li    t2, 500
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 72(sp)

lw    t0, 72(sp)
li    t2, 50
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 76(sp)

lw    t0, 76(sp)
li    t2, 5
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 80(sp)

lw    t0, 80(sp)
lw    t0, 0(t0)
sw    t0, 84(sp)

lw    t2, 68(sp)
lw    t1, 84(sp)
add   t0, t2, t1
sw    t0, 88(sp)

mv    t0, a6
li    t1, 6
slli  t2, t1, 2
add   t0, t0, t2
sw    t0, 92(sp)

lw    t0, 92(sp)
lw    t0, 0(t0)
sw    t0, 96(sp)

lw    t1, 88(sp)
lw    t2, 96(sp)
add   t0, t1, t2
sw    t0, 100(sp)

mv    t0, a7
li    t2, 7
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 104(sp)

lw    t0, 104(sp)
lw    t0, 0(t0)
sw    t0, 108(sp)

lw    t2, 100(sp)
lw    t1, 108(sp)
add   t0, t2, t1
sw    t0, 112(sp)

lw    t0, 8(sp)
lw    t0, 0(t0)
sw    t0, 116(sp)

lw    t1, 112(sp)
lw    t2, 116(sp)
add   t0, t1, t2
sw    t0, 120(sp)

lw    t0, 260(sp)
li    t2, 90
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 124(sp)

lw    t0, 124(sp)
li    t2, 8
slli  t1, t2, 2
add   t0, t0, t1
sw    t0, 128(sp)

lw    t0, 128(sp)
lw    t0, 0(t0)
sw    t0, 132(sp)

lw    t2, 120(sp)
lw    t1, 132(sp)
add   t0, t2, t1
sw    t0, 136(sp)

lw    a0, 136(sp)
addi sp, sp, 256
ret

main:
li t1, -4416
add sp, sp, t1
li t1, 4412
add t1, sp, t1
sw ra, 0(t1)
main_entry:
li    t0, 12
add   t0, t0, sp
sw    t0, 8(sp)

mv    t1, sp
sw    x0, 12(t1)
sw    x0, 16(t1)
sw    x0, 20(t1)
sw    x0, 24(t1)
sw    x0, 28(t1)
sw    x0, 32(t1)
sw    x0, 36(t1)
sw    x0, 40(t1)
sw    x0, 44(t1)
sw    x0, 48(t1)
sw    x0, 52(t1)
sw    x0, 56(t1)
sw    x0, 60(t1)
sw    x0, 64(t1)
sw    x0, 68(t1)
sw    x0, 72(t1)
sw    x0, 76(t1)
sw    x0, 80(t1)
sw    x0, 84(t1)
sw    x0, 88(t1)
sw    x0, 92(t1)
sw    x0, 96(t1)
sw    x0, 100(t1)
sw    x0, 104(t1)
sw    x0, 108(t1)
sw    x0, 112(t1)
sw    x0, 116(t1)
sw    x0, 120(t1)
sw    x0, 124(t1)
sw    x0, 128(t1)
sw    x0, 132(t1)
sw    x0, 136(t1)
sw    x0, 140(t1)
sw    x0, 144(t1)
sw    x0, 148(t1)
sw    x0, 152(t1)
sw    x0, 156(t1)
sw    x0, 160(t1)
sw    x0, 164(t1)
sw    x0, 168(t1)
sw    x0, 172(t1)
sw    x0, 176(t1)
sw    x0, 180(t1)
sw    x0, 184(t1)
sw    x0, 188(t1)
sw    x0, 192(t1)
sw    x0, 196(t1)
sw    x0, 200(t1)
sw    x0, 204(t1)
sw    x0, 208(t1)
sw    x0, 212(t1)
sw    x0, 216(t1)
sw    x0, 220(t1)
sw    x0, 224(t1)
sw    x0, 228(t1)
sw    x0, 232(t1)
sw    x0, 236(t1)
sw    x0, 240(t1)
sw    x0, 244(t1)
sw    x0, 248(t1)
sw    x0, 252(t1)
sw    x0, 256(t1)
sw    x0, 260(t1)
sw    x0, 264(t1)
sw    x0, 268(t1)
sw    x0, 272(t1)
sw    x0, 276(t1)
sw    x0, 280(t1)
sw    x0, 284(t1)
sw    x0, 288(t1)
sw    x0, 292(t1)
sw    x0, 296(t1)
sw    x0, 300(t1)
sw    x0, 304(t1)
sw    x0, 308(t1)
sw    x0, 312(t1)
sw    x0, 316(t1)
sw    x0, 320(t1)
sw    x0, 324(t1)
sw    x0, 328(t1)
sw    x0, 332(t1)
sw    x0, 336(t1)
sw    x0, 340(t1)
sw    x0, 344(t1)
sw    x0, 348(t1)
sw    x0, 352(t1)
sw    x0, 356(t1)
sw    x0, 360(t1)
sw    x0, 364(t1)
sw    x0, 368(t1)
sw    x0, 372(t1)
sw    x0, 376(t1)
sw    x0, 380(t1)
sw    x0, 384(t1)
sw    x0, 388(t1)
sw    x0, 392(t1)
sw    x0, 396(t1)
sw    x0, 400(t1)
sw    x0, 404(t1)
sw    x0, 408(t1)
sw    x0, 412(t1)
sw    x0, 416(t1)
sw    x0, 420(t1)
sw    x0, 424(t1)
sw    x0, 428(t1)
sw    x0, 432(t1)
sw    x0, 436(t1)
sw    x0, 440(t1)
sw    x0, 444(t1)
sw    x0, 448(t1)
sw    x0, 452(t1)
sw    x0, 456(t1)
sw    x0, 460(t1)
sw    x0, 464(t1)
sw    x0, 468(t1)
sw    x0, 472(t1)
sw    x0, 476(t1)
sw    x0, 480(t1)
sw    x0, 484(t1)
sw    x0, 488(t1)
sw    x0, 492(t1)
sw    x0, 496(t1)
sw    x0, 500(t1)
sw    x0, 504(t1)
sw    x0, 508(t1)
sw    x0, 512(t1)
sw    x0, 516(t1)
sw    x0, 520(t1)
sw    x0, 524(t1)
sw    x0, 528(t1)
sw    x0, 532(t1)
sw    x0, 536(t1)
sw    x0, 540(t1)
sw    x0, 544(t1)
sw    x0, 548(t1)
sw    x0, 552(t1)
sw    x0, 556(t1)
sw    x0, 560(t1)
sw    x0, 564(t1)
sw    x0, 568(t1)
sw    x0, 572(t1)
sw    x0, 576(t1)
sw    x0, 580(t1)
sw    x0, 584(t1)
sw    x0, 588(t1)
sw    x0, 592(t1)
sw    x0, 596(t1)
sw    x0, 600(t1)
sw    x0, 604(t1)
sw    x0, 608(t1)
sw    x0, 612(t1)
sw    x0, 616(t1)
sw    x0, 620(t1)
sw    x0, 624(t1)
sw    x0, 628(t1)
sw    x0, 632(t1)
sw    x0, 636(t1)
sw    x0, 640(t1)
sw    x0, 644(t1)
sw    x0, 648(t1)
sw    x0, 652(t1)
sw    x0, 656(t1)
sw    x0, 660(t1)
sw    x0, 664(t1)
sw    x0, 668(t1)
sw    x0, 672(t1)
sw    x0, 676(t1)
sw    x0, 680(t1)
sw    x0, 684(t1)
sw    x0, 688(t1)
sw    x0, 692(t1)
sw    x0, 696(t1)
sw    x0, 700(t1)
sw    x0, 704(t1)
sw    x0, 708(t1)
sw    x0, 712(t1)
sw    x0, 716(t1)
sw    x0, 720(t1)
sw    x0, 724(t1)
sw    x0, 728(t1)
sw    x0, 732(t1)
sw    x0, 736(t1)
sw    x0, 740(t1)
sw    x0, 744(t1)
sw    x0, 748(t1)
sw    x0, 752(t1)
sw    x0, 756(t1)
sw    x0, 760(t1)
sw    x0, 764(t1)
sw    x0, 768(t1)
sw    x0, 772(t1)
sw    x0, 776(t1)
sw    x0, 780(t1)
sw    x0, 784(t1)
sw    x0, 788(t1)
sw    x0, 792(t1)
sw    x0, 796(t1)
sw    x0, 800(t1)
sw    x0, 804(t1)
sw    x0, 808(t1)
sw    x0, 812(t1)
sw    x0, 816(t1)
sw    x0, 820(t1)
sw    x0, 824(t1)
sw    x0, 828(t1)
sw    x0, 832(t1)
sw    x0, 836(t1)
sw    x0, 840(t1)
sw    x0, 844(t1)
sw    x0, 848(t1)
sw    x0, 852(t1)
sw    x0, 856(t1)
sw    x0, 860(t1)
sw    x0, 864(t1)
sw    x0, 868(t1)
sw    x0, 872(t1)
sw    x0, 876(t1)
sw    x0, 880(t1)
sw    x0, 884(t1)
sw    x0, 888(t1)
sw    x0, 892(t1)
sw    x0, 896(t1)
sw    x0, 900(t1)
sw    x0, 904(t1)
sw    x0, 908(t1)
sw    x0, 912(t1)
sw    x0, 916(t1)
sw    x0, 920(t1)
sw    x0, 924(t1)
sw    x0, 928(t1)
sw    x0, 932(t1)
sw    x0, 936(t1)
sw    x0, 940(t1)
sw    x0, 944(t1)
sw    x0, 948(t1)
sw    x0, 952(t1)
sw    x0, 956(t1)
sw    x0, 960(t1)
sw    x0, 964(t1)
sw    x0, 968(t1)
sw    x0, 972(t1)
sw    x0, 976(t1)
sw    x0, 980(t1)
sw    x0, 984(t1)
sw    x0, 988(t1)
sw    x0, 992(t1)
sw    x0, 996(t1)
sw    x0, 1000(t1)
sw    x0, 1004(t1)
sw    x0, 1008(t1)
sw    x0, 1012(t1)
sw    x0, 1016(t1)
sw    x0, 1020(t1)
sw    x0, 1024(t1)
sw    x0, 1028(t1)
sw    x0, 1032(t1)
sw    x0, 1036(t1)
sw    x0, 1040(t1)
sw    x0, 1044(t1)
sw    x0, 1048(t1)
sw    x0, 1052(t1)
sw    x0, 1056(t1)
sw    x0, 1060(t1)
sw    x0, 1064(t1)
sw    x0, 1068(t1)
sw    x0, 1072(t1)
sw    x0, 1076(t1)
sw    x0, 1080(t1)
sw    x0, 1084(t1)
sw    x0, 1088(t1)
sw    x0, 1092(t1)
sw    x0, 1096(t1)
sw    x0, 1100(t1)
sw    x0, 1104(t1)
sw    x0, 1108(t1)
sw    x0, 1112(t1)
sw    x0, 1116(t1)
sw    x0, 1120(t1)
sw    x0, 1124(t1)
sw    x0, 1128(t1)
sw    x0, 1132(t1)
sw    x0, 1136(t1)
sw    x0, 1140(t1)
sw    x0, 1144(t1)
sw    x0, 1148(t1)
sw    x0, 1152(t1)
sw    x0, 1156(t1)
sw    x0, 1160(t1)
sw    x0, 1164(t1)
sw    x0, 1168(t1)
sw    x0, 1172(t1)
sw    x0, 1176(t1)
sw    x0, 1180(t1)
sw    x0, 1184(t1)
sw    x0, 1188(t1)
sw    x0, 1192(t1)
sw    x0, 1196(t1)
sw    x0, 1200(t1)
sw    x0, 1204(t1)
sw    x0, 1208(t1)
sw    x0, 1212(t1)
sw    x0, 1216(t1)
sw    x0, 1220(t1)
sw    x0, 1224(t1)
sw    x0, 1228(t1)
sw    x0, 1232(t1)
sw    x0, 1236(t1)
sw    x0, 1240(t1)
sw    x0, 1244(t1)
sw    x0, 1248(t1)
sw    x0, 1252(t1)
sw    x0, 1256(t1)
sw    x0, 1260(t1)
sw    x0, 1264(t1)
sw    x0, 1268(t1)
sw    x0, 1272(t1)
sw    x0, 1276(t1)
sw    x0, 1280(t1)
sw    x0, 1284(t1)
sw    x0, 1288(t1)
sw    x0, 1292(t1)
sw    x0, 1296(t1)
sw    x0, 1300(t1)
sw    x0, 1304(t1)
sw    x0, 1308(t1)
sw    x0, 1312(t1)
sw    x0, 1316(t1)
sw    x0, 1320(t1)
sw    x0, 1324(t1)
sw    x0, 1328(t1)
sw    x0, 1332(t1)
sw    x0, 1336(t1)
sw    x0, 1340(t1)
sw    x0, 1344(t1)
sw    x0, 1348(t1)
sw    x0, 1352(t1)
sw    x0, 1356(t1)
sw    x0, 1360(t1)
sw    x0, 1364(t1)
sw    x0, 1368(t1)
sw    x0, 1372(t1)
sw    x0, 1376(t1)
sw    x0, 1380(t1)
sw    x0, 1384(t1)
sw    x0, 1388(t1)
sw    x0, 1392(t1)
sw    x0, 1396(t1)
sw    x0, 1400(t1)
sw    x0, 1404(t1)
sw    x0, 1408(t1)
sw    x0, 1412(t1)
sw    x0, 1416(t1)
sw    x0, 1420(t1)
sw    x0, 1424(t1)
sw    x0, 1428(t1)
sw    x0, 1432(t1)
sw    x0, 1436(t1)
sw    x0, 1440(t1)
sw    x0, 1444(t1)
sw    x0, 1448(t1)
sw    x0, 1452(t1)
sw    x0, 1456(t1)
sw    x0, 1460(t1)
sw    x0, 1464(t1)
sw    x0, 1468(t1)
sw    x0, 1472(t1)
sw    x0, 1476(t1)
sw    x0, 1480(t1)
sw    x0, 1484(t1)
sw    x0, 1488(t1)
sw    x0, 1492(t1)
sw    x0, 1496(t1)
sw    x0, 1500(t1)
sw    x0, 1504(t1)
sw    x0, 1508(t1)
sw    x0, 1512(t1)
sw    x0, 1516(t1)
sw    x0, 1520(t1)
sw    x0, 1524(t1)
sw    x0, 1528(t1)
sw    x0, 1532(t1)
sw    x0, 1536(t1)
sw    x0, 1540(t1)
sw    x0, 1544(t1)
sw    x0, 1548(t1)
sw    x0, 1552(t1)
sw    x0, 1556(t1)
sw    x0, 1560(t1)
sw    x0, 1564(t1)
sw    x0, 1568(t1)
sw    x0, 1572(t1)
sw    x0, 1576(t1)
sw    x0, 1580(t1)
sw    x0, 1584(t1)
sw    x0, 1588(t1)
sw    x0, 1592(t1)
sw    x0, 1596(t1)
sw    x0, 1600(t1)
sw    x0, 1604(t1)
sw    x0, 1608(t1)
sw    x0, 1612(t1)
sw    x0, 1616(t1)
sw    x0, 1620(t1)
sw    x0, 1624(t1)
sw    x0, 1628(t1)
sw    x0, 1632(t1)
sw    x0, 1636(t1)
sw    x0, 1640(t1)
sw    x0, 1644(t1)
sw    x0, 1648(t1)
sw    x0, 1652(t1)
sw    x0, 1656(t1)
sw    x0, 1660(t1)
sw    x0, 1664(t1)
sw    x0, 1668(t1)
sw    x0, 1672(t1)
sw    x0, 1676(t1)
sw    x0, 1680(t1)
sw    x0, 1684(t1)
sw    x0, 1688(t1)
sw    x0, 1692(t1)
sw    x0, 1696(t1)
sw    x0, 1700(t1)
sw    x0, 1704(t1)
sw    x0, 1708(t1)
sw    x0, 1712(t1)
sw    x0, 1716(t1)
sw    x0, 1720(t1)
sw    x0, 1724(t1)
sw    x0, 1728(t1)
sw    x0, 1732(t1)
sw    x0, 1736(t1)
sw    x0, 1740(t1)
sw    x0, 1744(t1)
sw    x0, 1748(t1)
sw    x0, 1752(t1)
sw    x0, 1756(t1)
sw    x0, 1760(t1)
sw    x0, 1764(t1)
sw    x0, 1768(t1)
sw    x0, 1772(t1)
sw    x0, 1776(t1)
sw    x0, 1780(t1)
sw    x0, 1784(t1)
sw    x0, 1788(t1)
sw    x0, 1792(t1)
sw    x0, 1796(t1)
sw    x0, 1800(t1)
sw    x0, 1804(t1)
sw    x0, 1808(t1)
sw    x0, 1812(t1)
sw    x0, 1816(t1)
sw    x0, 1820(t1)
sw    x0, 1824(t1)
sw    x0, 1828(t1)
sw    x0, 1832(t1)
sw    x0, 1836(t1)
sw    x0, 1840(t1)
sw    x0, 1844(t1)
sw    x0, 1848(t1)
sw    x0, 1852(t1)
sw    x0, 1856(t1)
sw    x0, 1860(t1)
sw    x0, 1864(t1)
sw    x0, 1868(t1)
sw    x0, 1872(t1)
sw    x0, 1876(t1)
sw    x0, 1880(t1)
sw    x0, 1884(t1)
sw    x0, 1888(t1)
sw    x0, 1892(t1)
sw    x0, 1896(t1)
sw    x0, 1900(t1)
sw    x0, 1904(t1)
sw    x0, 1908(t1)
sw    x0, 1912(t1)
sw    x0, 1916(t1)
sw    x0, 1920(t1)
sw    x0, 1924(t1)
sw    x0, 1928(t1)
sw    x0, 1932(t1)
sw    x0, 1936(t1)
sw    x0, 1940(t1)
sw    x0, 1944(t1)
sw    x0, 1948(t1)
sw    x0, 1952(t1)
sw    x0, 1956(t1)
sw    x0, 1960(t1)
sw    x0, 1964(t1)
sw    x0, 1968(t1)
sw    x0, 1972(t1)
sw    x0, 1976(t1)
sw    x0, 1980(t1)
sw    x0, 1984(t1)
sw    x0, 1988(t1)
sw    x0, 1992(t1)
sw    x0, 1996(t1)
sw    x0, 2000(t1)
sw    x0, 2004(t1)
sw    x0, 2008(t1)
sw    x0, 2012(t1)
sw    x0, 2016(t1)
sw    x0, 2020(t1)
sw    x0, 2024(t1)
sw    x0, 2028(t1)
sw    x0, 2032(t1)
sw    x0, 2036(t1)
sw    x0, 2040(t1)
sw    x0, 2044(t1)
li    t2, 2048
add   t1, t1, t2
sw    x0, 0(t1)
sw    x0, 4(t1)
sw    x0, 8(t1)
sw    x0, 12(t1)
sw    x0, 16(t1)
sw    x0, 20(t1)
sw    x0, 24(t1)
sw    x0, 28(t1)
sw    x0, 32(t1)
sw    x0, 36(t1)
sw    x0, 40(t1)
sw    x0, 44(t1)
sw    x0, 48(t1)
sw    x0, 52(t1)
sw    x0, 56(t1)
sw    x0, 60(t1)
sw    x0, 64(t1)
sw    x0, 68(t1)
sw    x0, 72(t1)
sw    x0, 76(t1)
sw    x0, 80(t1)
sw    x0, 84(t1)
sw    x0, 88(t1)
sw    x0, 92(t1)
sw    x0, 96(t1)
sw    x0, 100(t1)
sw    x0, 104(t1)
sw    x0, 108(t1)
sw    x0, 112(t1)
sw    x0, 116(t1)
sw    x0, 120(t1)
sw    x0, 124(t1)
sw    x0, 128(t1)
sw    x0, 132(t1)
sw    x0, 136(t1)
sw    x0, 140(t1)
sw    x0, 144(t1)
sw    x0, 148(t1)
sw    x0, 152(t1)
sw    x0, 156(t1)
sw    x0, 160(t1)
sw    x0, 164(t1)
sw    x0, 168(t1)
sw    x0, 172(t1)
sw    x0, 176(t1)
sw    x0, 180(t1)
sw    x0, 184(t1)
sw    x0, 188(t1)
sw    x0, 192(t1)
sw    x0, 196(t1)
sw    x0, 200(t1)
sw    x0, 204(t1)
sw    x0, 208(t1)
sw    x0, 212(t1)
sw    x0, 216(t1)
sw    x0, 220(t1)
sw    x0, 224(t1)
sw    x0, 228(t1)
sw    x0, 232(t1)
sw    x0, 236(t1)
sw    x0, 240(t1)
sw    x0, 244(t1)
sw    x0, 248(t1)
sw    x0, 252(t1)
sw    x0, 256(t1)
sw    x0, 260(t1)
sw    x0, 264(t1)
sw    x0, 268(t1)
sw    x0, 272(t1)
sw    x0, 276(t1)
sw    x0, 280(t1)
sw    x0, 284(t1)
sw    x0, 288(t1)
sw    x0, 292(t1)
sw    x0, 296(t1)
sw    x0, 300(t1)
sw    x0, 304(t1)
sw    x0, 308(t1)
sw    x0, 312(t1)
sw    x0, 316(t1)
sw    x0, 320(t1)
sw    x0, 324(t1)
sw    x0, 328(t1)
sw    x0, 332(t1)
sw    x0, 336(t1)
sw    x0, 340(t1)
sw    x0, 344(t1)
sw    x0, 348(t1)
sw    x0, 352(t1)
sw    x0, 356(t1)
sw    x0, 360(t1)
sw    x0, 364(t1)
sw    x0, 368(t1)
sw    x0, 372(t1)
sw    x0, 376(t1)
sw    x0, 380(t1)
sw    x0, 384(t1)
sw    x0, 388(t1)
sw    x0, 392(t1)
sw    x0, 396(t1)
sw    x0, 400(t1)
sw    x0, 404(t1)
sw    x0, 408(t1)
sw    x0, 412(t1)
sw    x0, 416(t1)
sw    x0, 420(t1)
sw    x0, 424(t1)
sw    x0, 428(t1)
sw    x0, 432(t1)
sw    x0, 436(t1)
sw    x0, 440(t1)
sw    x0, 444(t1)
sw    x0, 448(t1)
sw    x0, 452(t1)
sw    x0, 456(t1)
sw    x0, 460(t1)
sw    x0, 464(t1)
sw    x0, 468(t1)
sw    x0, 472(t1)
sw    x0, 476(t1)
sw    x0, 480(t1)
sw    x0, 484(t1)
sw    x0, 488(t1)
sw    x0, 492(t1)
sw    x0, 496(t1)
sw    x0, 500(t1)
sw    x0, 504(t1)
sw    x0, 508(t1)
sw    x0, 512(t1)
sw    x0, 516(t1)
sw    x0, 520(t1)
sw    x0, 524(t1)
sw    x0, 528(t1)
sw    x0, 532(t1)
sw    x0, 536(t1)
sw    x0, 540(t1)
sw    x0, 544(t1)
sw    x0, 548(t1)
sw    x0, 552(t1)
sw    x0, 556(t1)
sw    x0, 560(t1)
sw    x0, 564(t1)
sw    x0, 568(t1)
sw    x0, 572(t1)
sw    x0, 576(t1)
sw    x0, 580(t1)
sw    x0, 584(t1)
sw    x0, 588(t1)
sw    x0, 592(t1)
sw    x0, 596(t1)
sw    x0, 600(t1)
sw    x0, 604(t1)
sw    x0, 608(t1)
sw    x0, 612(t1)
sw    x0, 616(t1)
sw    x0, 620(t1)
sw    x0, 624(t1)
sw    x0, 628(t1)
sw    x0, 632(t1)
sw    x0, 636(t1)
sw    x0, 640(t1)
sw    x0, 644(t1)
sw    x0, 648(t1)
sw    x0, 652(t1)
sw    x0, 656(t1)
sw    x0, 660(t1)
sw    x0, 664(t1)
sw    x0, 668(t1)
sw    x0, 672(t1)
sw    x0, 676(t1)
sw    x0, 680(t1)
sw    x0, 684(t1)
sw    x0, 688(t1)
sw    x0, 692(t1)
sw    x0, 696(t1)
sw    x0, 700(t1)
sw    x0, 704(t1)
sw    x0, 708(t1)
sw    x0, 712(t1)
sw    x0, 716(t1)
sw    x0, 720(t1)
sw    x0, 724(t1)
sw    x0, 728(t1)
sw    x0, 732(t1)
sw    x0, 736(t1)
sw    x0, 740(t1)
sw    x0, 744(t1)
sw    x0, 748(t1)
sw    x0, 752(t1)
sw    x0, 756(t1)
sw    x0, 760(t1)
sw    x0, 764(t1)
sw    x0, 768(t1)
sw    x0, 772(t1)
sw    x0, 776(t1)
sw    x0, 780(t1)
sw    x0, 784(t1)
sw    x0, 788(t1)
sw    x0, 792(t1)
sw    x0, 796(t1)
sw    x0, 800(t1)
sw    x0, 804(t1)
sw    x0, 808(t1)
sw    x0, 812(t1)
sw    x0, 816(t1)
sw    x0, 820(t1)
sw    x0, 824(t1)
sw    x0, 828(t1)
sw    x0, 832(t1)
sw    x0, 836(t1)
sw    x0, 840(t1)
sw    x0, 844(t1)
sw    x0, 848(t1)
sw    x0, 852(t1)
sw    x0, 856(t1)
sw    x0, 860(t1)
sw    x0, 864(t1)
sw    x0, 868(t1)
sw    x0, 872(t1)
sw    x0, 876(t1)
sw    x0, 880(t1)
sw    x0, 884(t1)
sw    x0, 888(t1)
sw    x0, 892(t1)
sw    x0, 896(t1)
sw    x0, 900(t1)
sw    x0, 904(t1)
sw    x0, 908(t1)
sw    x0, 912(t1)
sw    x0, 916(t1)
sw    x0, 920(t1)
sw    x0, 924(t1)
sw    x0, 928(t1)
sw    x0, 932(t1)
sw    x0, 936(t1)
sw    x0, 940(t1)
sw    x0, 944(t1)
sw    x0, 948(t1)
sw    x0, 952(t1)
sw    x0, 956(t1)
sw    x0, 960(t1)
sw    x0, 964(t1)
sw    x0, 968(t1)
sw    x0, 972(t1)
sw    x0, 976(t1)
sw    x0, 980(t1)
sw    x0, 984(t1)
sw    x0, 988(t1)
sw    x0, 992(t1)
sw    x0, 996(t1)
sw    x0, 1000(t1)
sw    x0, 1004(t1)
sw    x0, 1008(t1)
sw    x0, 1012(t1)
sw    x0, 1016(t1)
sw    x0, 1020(t1)
sw    x0, 1024(t1)
sw    x0, 1028(t1)
sw    x0, 1032(t1)
sw    x0, 1036(t1)
sw    x0, 1040(t1)
sw    x0, 1044(t1)
sw    x0, 1048(t1)
sw    x0, 1052(t1)
sw    x0, 1056(t1)
sw    x0, 1060(t1)
sw    x0, 1064(t1)
sw    x0, 1068(t1)
sw    x0, 1072(t1)
sw    x0, 1076(t1)
sw    x0, 1080(t1)
sw    x0, 1084(t1)
sw    x0, 1088(t1)
sw    x0, 1092(t1)
sw    x0, 1096(t1)
sw    x0, 1100(t1)
sw    x0, 1104(t1)
sw    x0, 1108(t1)
sw    x0, 1112(t1)
sw    x0, 1116(t1)
sw    x0, 1120(t1)
sw    x0, 1124(t1)
sw    x0, 1128(t1)
sw    x0, 1132(t1)
sw    x0, 1136(t1)
sw    x0, 1140(t1)
sw    x0, 1144(t1)
sw    x0, 1148(t1)
sw    x0, 1152(t1)
sw    x0, 1156(t1)
sw    x0, 1160(t1)
sw    x0, 1164(t1)
sw    x0, 1168(t1)
sw    x0, 1172(t1)
sw    x0, 1176(t1)
sw    x0, 1180(t1)
sw    x0, 1184(t1)
sw    x0, 1188(t1)
sw    x0, 1192(t1)
sw    x0, 1196(t1)
sw    x0, 1200(t1)
sw    x0, 1204(t1)
sw    x0, 1208(t1)
sw    x0, 1212(t1)
sw    x0, 1216(t1)
sw    x0, 1220(t1)
sw    x0, 1224(t1)
sw    x0, 1228(t1)
sw    x0, 1232(t1)
sw    x0, 1236(t1)
sw    x0, 1240(t1)
sw    x0, 1244(t1)
sw    x0, 1248(t1)
sw    x0, 1252(t1)
sw    x0, 1256(t1)
sw    x0, 1260(t1)
sw    x0, 1264(t1)
sw    x0, 1268(t1)
sw    x0, 1272(t1)
sw    x0, 1276(t1)
sw    x0, 1280(t1)
sw    x0, 1284(t1)
sw    x0, 1288(t1)
sw    x0, 1292(t1)
sw    x0, 1296(t1)
sw    x0, 1300(t1)
sw    x0, 1304(t1)
sw    x0, 1308(t1)
sw    x0, 1312(t1)
sw    x0, 1316(t1)
sw    x0, 1320(t1)
sw    x0, 1324(t1)
sw    x0, 1328(t1)
sw    x0, 1332(t1)
sw    x0, 1336(t1)
sw    x0, 1340(t1)
sw    x0, 1344(t1)
sw    x0, 1348(t1)
sw    x0, 1352(t1)
sw    x0, 1356(t1)
sw    x0, 1360(t1)
sw    x0, 1364(t1)
sw    x0, 1368(t1)
sw    x0, 1372(t1)
sw    x0, 1376(t1)
sw    x0, 1380(t1)
sw    x0, 1384(t1)
sw    x0, 1388(t1)
sw    x0, 1392(t1)
sw    x0, 1396(t1)
sw    x0, 1400(t1)
sw    x0, 1404(t1)
sw    x0, 1408(t1)
sw    x0, 1412(t1)
sw    x0, 1416(t1)
sw    x0, 1420(t1)
sw    x0, 1424(t1)
sw    x0, 1428(t1)
sw    x0, 1432(t1)
sw    x0, 1436(t1)
sw    x0, 1440(t1)
sw    x0, 1444(t1)
sw    x0, 1448(t1)
sw    x0, 1452(t1)
sw    x0, 1456(t1)
sw    x0, 1460(t1)
sw    x0, 1464(t1)
sw    x0, 1468(t1)
sw    x0, 1472(t1)
sw    x0, 1476(t1)
sw    x0, 1480(t1)
sw    x0, 1484(t1)
sw    x0, 1488(t1)
sw    x0, 1492(t1)
sw    x0, 1496(t1)
sw    x0, 1500(t1)
sw    x0, 1504(t1)
sw    x0, 1508(t1)
sw    x0, 1512(t1)
sw    x0, 1516(t1)
sw    x0, 1520(t1)
sw    x0, 1524(t1)
sw    x0, 1528(t1)
sw    x0, 1532(t1)
sw    x0, 1536(t1)
sw    x0, 1540(t1)
sw    x0, 1544(t1)
sw    x0, 1548(t1)
sw    x0, 1552(t1)
sw    x0, 1556(t1)
sw    x0, 1560(t1)
sw    x0, 1564(t1)
sw    x0, 1568(t1)
sw    x0, 1572(t1)
sw    x0, 1576(t1)
sw    x0, 1580(t1)
sw    x0, 1584(t1)
sw    x0, 1588(t1)
sw    x0, 1592(t1)
sw    x0, 1596(t1)
sw    x0, 1600(t1)
sw    x0, 1604(t1)
sw    x0, 1608(t1)
sw    x0, 1612(t1)
sw    x0, 1616(t1)
sw    x0, 1620(t1)
sw    x0, 1624(t1)
sw    x0, 1628(t1)
sw    x0, 1632(t1)
sw    x0, 1636(t1)
sw    x0, 1640(t1)
sw    x0, 1644(t1)
sw    x0, 1648(t1)
sw    x0, 1652(t1)
sw    x0, 1656(t1)
sw    x0, 1660(t1)
sw    x0, 1664(t1)
sw    x0, 1668(t1)
sw    x0, 1672(t1)
sw    x0, 1676(t1)
sw    x0, 1680(t1)
sw    x0, 1684(t1)
sw    x0, 1688(t1)
sw    x0, 1692(t1)
sw    x0, 1696(t1)
sw    x0, 1700(t1)
sw    x0, 1704(t1)
sw    x0, 1708(t1)
sw    x0, 1712(t1)
sw    x0, 1716(t1)
sw    x0, 1720(t1)
sw    x0, 1724(t1)
sw    x0, 1728(t1)
sw    x0, 1732(t1)
sw    x0, 1736(t1)
sw    x0, 1740(t1)
sw    x0, 1744(t1)
sw    x0, 1748(t1)
sw    x0, 1752(t1)
sw    x0, 1756(t1)
sw    x0, 1760(t1)
sw    x0, 1764(t1)
sw    x0, 1768(t1)
sw    x0, 1772(t1)
sw    x0, 1776(t1)
sw    x0, 1780(t1)
sw    x0, 1784(t1)
sw    x0, 1788(t1)
sw    x0, 1792(t1)
sw    x0, 1796(t1)
sw    x0, 1800(t1)
sw    x0, 1804(t1)
sw    x0, 1808(t1)
sw    x0, 1812(t1)
sw    x0, 1816(t1)
sw    x0, 1820(t1)
sw    x0, 1824(t1)
sw    x0, 1828(t1)
sw    x0, 1832(t1)
sw    x0, 1836(t1)
sw    x0, 1840(t1)
sw    x0, 1844(t1)
sw    x0, 1848(t1)
sw    x0, 1852(t1)
sw    x0, 1856(t1)
sw    x0, 1860(t1)
sw    x0, 1864(t1)
sw    x0, 1868(t1)
sw    x0, 1872(t1)
sw    x0, 1876(t1)
sw    x0, 1880(t1)
sw    x0, 1884(t1)
sw    x0, 1888(t1)
sw    x0, 1892(t1)
sw    x0, 1896(t1)
sw    x0, 1900(t1)
sw    x0, 1904(t1)
sw    x0, 1908(t1)
sw    x0, 1912(t1)
sw    x0, 1916(t1)
sw    x0, 1920(t1)
sw    x0, 1924(t1)
sw    x0, 1928(t1)
sw    x0, 1932(t1)
sw    x0, 1936(t1)
sw    x0, 1940(t1)
sw    x0, 1944(t1)
sw    x0, 1948(t1)
sw    x0, 1952(t1)
sw    x0, 1956(t1)
sw    x0, 1960(t1)

li    t1, 4016
add   t1, t1, sp
li    t2, 4012
add   t2, t2, sp
sw    t1, 0(t2)

li    t1, 0
li    t2, 4012
add   t2, t2, sp
lw    t2, 0(t2)
sw    t1, 0(t2)

lw    t1, 8(sp)
li    t2, 0
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4020
add   t3, t3, sp
sw    t1, 0(t3)

li    t1, 4332
add   t1, t1, sp
sw    a0, 0(t1)
li    t1, 4328
add   t1, t1, sp
sw    a1, 0(t1)
li    t1, 4324
add   t1, t1, sp
sw    a2, 0(t1)
li    t1, 4320
add   t1, t1, sp
sw    a3, 0(t1)
li    t1, 4316
add   t1, t1, sp
sw    a4, 0(t1)
li    t1, 4312
add   t1, t1, sp
sw    a5, 0(t1)
li    t1, 4308
add   t1, t1, sp
sw    a6, 0(t1)
li    t1, 4304
add   t1, t1, sp
sw    a7, 0(t1)
li    t1, 4020
add   t1, t1, sp
lw    a0, 0(t1)
call  init
li    t1, 4304
add   t1, t1, sp
lw    a7, 0(t1)
li    t1, 4308
add   t1, t1, sp
lw    a6, 0(t1)
li    t1, 4312
add   t1, t1, sp
lw    a5, 0(t1)
li    t1, 4316
add   t1, t1, sp
lw    a4, 0(t1)
li    t1, 4320
add   t1, t1, sp
lw    a3, 0(t1)
li    t1, 4324
add   t1, t1, sp
lw    a2, 0(t1)
li    t1, 4328
add   t1, t1, sp
lw    a1, 0(t1)
li    t1, 4332
add   t1, t1, sp
lw    a0, 0(t1)

li    t2, 4012
add   t2, t2, sp
lw    t1, 0(t2)
lw    t1, 0(t1)
li    t2, 4024
add   t2, t2, sp
sw    t1, 0(t2)

lw    t1, 8(sp)
li    t2, 0
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4028
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4028
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 0
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4032
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4032
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 0
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4036
add   t3, t3, sp
sw    t1, 0(t3)

lw    t1, 8(sp)
li    t2, 100
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4040
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4040
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 10
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4044
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4044
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 0
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4048
add   t3, t3, sp
sw    t1, 0(t3)

lw    t1, 8(sp)
li    t2, 200
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4052
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4052
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 20
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4056
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4056
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 0
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4060
add   t3, t3, sp
sw    t1, 0(t3)

lw    t1, 8(sp)
li    t2, 300
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4064
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4064
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 30
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4068
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4068
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 0
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4072
add   t3, t3, sp
sw    t1, 0(t3)

lw    t1, 8(sp)
li    t2, 400
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4076
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4076
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 40
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4080
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4080
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 0
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4084
add   t3, t3, sp
sw    t1, 0(t3)

lw    t1, 8(sp)
li    t2, 500
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4088
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4088
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 50
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4092
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4092
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 0
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4096
add   t3, t3, sp
sw    t1, 0(t3)

lw    t1, 8(sp)
li    t2, 600
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4100
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4100
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 60
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4104
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4104
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 0
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4108
add   t3, t3, sp
sw    t1, 0(t3)

lw    t1, 8(sp)
li    t2, 700
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4112
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4112
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 70
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4116
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4116
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 0
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4120
add   t3, t3, sp
sw    t1, 0(t3)

lw    t1, 8(sp)
li    t2, 800
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4124
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4124
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 80
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4128
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4128
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 0
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4132
add   t3, t3, sp
sw    t1, 0(t3)

lw    t1, 8(sp)
li    t2, 900
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4136
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4136
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 90
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4140
add   t3, t3, sp
sw    t1, 0(t3)

li    t3, 4140
add   t3, t3, sp
lw    t1, 0(t3)
li    t2, 0
slli  t3, t2, 2
add   t1, t1, t3
li    t3, 4144
add   t3, t3, sp
sw    t1, 0(t3)

li    t1, 4332
add   t1, t1, sp
sw    a0, 0(t1)
li    t1, 4328
add   t1, t1, sp
sw    a1, 0(t1)
li    t1, 4324
add   t1, t1, sp
sw    a2, 0(t1)
li    t1, 4320
add   t1, t1, sp
sw    a3, 0(t1)
li    t1, 4316
add   t1, t1, sp
sw    a4, 0(t1)
li    t1, 4312
add   t1, t1, sp
sw    a5, 0(t1)
li    t1, 4308
add   t1, t1, sp
sw    a6, 0(t1)
li    t1, 4304
add   t1, t1, sp
sw    a7, 0(t1)
li    t1, 4036
add   t1, t1, sp
lw    a0, 0(t1)
li    t1, 4048
add   t1, t1, sp
lw    a1, 0(t1)
li    t1, 4060
add   t1, t1, sp
lw    a2, 0(t1)
li    t1, 4072
add   t1, t1, sp
lw    a3, 0(t1)
li    t1, 4084
add   t1, t1, sp
lw    a4, 0(t1)
li    t1, 4096
add   t1, t1, sp
lw    a5, 0(t1)
li    t1, 4108
add   t1, t1, sp
lw    a6, 0(t1)
li    t1, 4120
add   t1, t1, sp
lw    a7, 0(t1)
li    t2, 4132
add   t2, t2, sp
lw    t1, 0(t2)
sw    t1, 0(sp)
li    t2, 4144
add   t2, t2, sp
lw    t1, 0(t2)
sw    t1, 4(sp)
call  f1
li    t1, 4148
add   t1, t1, sp
sw    a0, 0(t1)
li    t1, 4304
add   t1, t1, sp
lw    a7, 0(t1)
li    t1, 4308
add   t1, t1, sp
lw    a6, 0(t1)
li    t1, 4312
add   t1, t1, sp
lw    a5, 0(t1)
li    t1, 4316
add   t1, t1, sp
lw    a4, 0(t1)
li    t1, 4320
add   t1, t1, sp
lw    a3, 0(t1)
li    t1, 4324
add   t1, t1, sp
lw    a2, 0(t1)
li    t1, 4328
add   t1, t1, sp
lw    a1, 0(t1)
li    t1, 4332
add   t1, t1, sp
lw    a0, 0(t1)

li    t3, 4024
add   t3, t3, sp
lw    t2, 0(t3)
li    t4, 4148
add   t4, t4, sp
lw    t3, 0(t4)
add   t1, t2, t3
li    t4, 4152
add   t4, t4, sp
sw    t1, 0(t4)

li    t3, 4152
add   t3, t3, sp
lw    t1, 0(t3)
li    t3, 4012
add   t3, t3, sp
lw    t3, 0(t3)
sw    t1, 0(t3)

li    t3, 4012
add   t3, t3, sp
lw    t1, 0(t3)
lw    t1, 0(t1)
li    t3, 4156
add   t3, t3, sp
sw    t1, 0(t3)

li    t1, 4332
add   t1, t1, sp
sw    a0, 0(t1)
li    t1, 4328
add   t1, t1, sp
sw    a1, 0(t1)
li    t1, 4324
add   t1, t1, sp
sw    a2, 0(t1)
li    t1, 4320
add   t1, t1, sp
sw    a3, 0(t1)
li    t1, 4316
add   t1, t1, sp
sw    a4, 0(t1)
li    t1, 4312
add   t1, t1, sp
sw    a5, 0(t1)
li    t1, 4308
add   t1, t1, sp
sw    a6, 0(t1)
li    t1, 4304
add   t1, t1, sp
sw    a7, 0(t1)
li    t1, 4156
add   t1, t1, sp
lw    a0, 0(t1)
call  putint
li    t1, 4304
add   t1, t1, sp
lw    a7, 0(t1)
li    t1, 4308
add   t1, t1, sp
lw    a6, 0(t1)
li    t1, 4312
add   t1, t1, sp
lw    a5, 0(t1)
li    t1, 4316
add   t1, t1, sp
lw    a4, 0(t1)
li    t1, 4320
add   t1, t1, sp
lw    a3, 0(t1)
li    t1, 4324
add   t1, t1, sp
lw    a2, 0(t1)
li    t1, 4328
add   t1, t1, sp
lw    a1, 0(t1)
li    t1, 4332
add   t1, t1, sp
lw    a0, 0(t1)

li    t1, 10
li    t3, 4160
add   t3, t3, sp
sw    t1, 0(t3)

li    t1, 4332
add   t1, t1, sp
sw    a0, 0(t1)
li    t1, 4328
add   t1, t1, sp
sw    a1, 0(t1)
li    t1, 4324
add   t1, t1, sp
sw    a2, 0(t1)
li    t1, 4320
add   t1, t1, sp
sw    a3, 0(t1)
li    t1, 4316
add   t1, t1, sp
sw    a4, 0(t1)
li    t1, 4312
add   t1, t1, sp
sw    a5, 0(t1)
li    t1, 4308
add   t1, t1, sp
sw    a6, 0(t1)
li    t1, 4304
add   t1, t1, sp
sw    a7, 0(t1)
li    t1, 4160
add   t1, t1, sp
lw    a0, 0(t1)
call  putch
li    t1, 4304
add   t1, t1, sp
lw    a7, 0(t1)
li    t1, 4308
add   t1, t1, sp
lw    a6, 0(t1)
li    t1, 4312
add   t1, t1, sp
lw    a5, 0(t1)
li    t1, 4316
add   t1, t1, sp
lw    a4, 0(t1)
li    t1, 4320
add   t1, t1, sp
lw    a3, 0(t1)
li    t1, 4324
add   t1, t1, sp
lw    a2, 0(t1)
li    t1, 4328
add   t1, t1, sp
lw    a1, 0(t1)
li    t1, 4332
add   t1, t1, sp
lw    a0, 0(t1)

li    t3, 4012
add   t3, t3, sp
lw    t1, 0(t3)
lw    t1, 0(t1)
li    t3, 4164
add   t3, t3, sp
sw    t1, 0(t3)

lw    t1, 8(sp)
li    t3, 0
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4168
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4168
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 0
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4172
add   t2, t2, sp
sw    t1, 0(t2)

lw    t1, 8(sp)
li    t3, 100
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4176
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4176
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 10
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4180
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4180
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 0
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4184
add   t2, t2, sp
sw    t1, 0(t2)

lw    t1, 8(sp)
li    t3, 200
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4188
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4188
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 20
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4192
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4192
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 2
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4196
add   t2, t2, sp
sw    t1, 0(t2)

li    t3, 4196
add   t3, t3, sp
lw    t1, 0(t3)
lw    t1, 0(t1)
li    t3, 4200
add   t3, t3, sp
sw    t1, 0(t3)

lw    t1, 8(sp)
li    t3, 300
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4204
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4204
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 30
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4208
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4208
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 0
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4212
add   t2, t2, sp
sw    t1, 0(t2)

lw    t1, 8(sp)
li    t3, 400
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4216
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4216
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 40
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4220
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4220
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 0
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4224
add   t2, t2, sp
sw    t1, 0(t2)

lw    t1, 8(sp)
li    t3, 0
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4228
add   t2, t2, sp
sw    t1, 0(t2)

lw    t1, 8(sp)
li    t3, 600
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4232
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4232
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 60
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4236
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4236
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 0
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4240
add   t2, t2, sp
sw    t1, 0(t2)

lw    t1, 8(sp)
li    t3, 700
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4244
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4244
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 70
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4248
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4248
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 0
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4252
add   t2, t2, sp
sw    t1, 0(t2)

lw    t1, 8(sp)
li    t3, 800
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4256
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4256
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 80
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4260
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4260
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 8
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4264
add   t2, t2, sp
sw    t1, 0(t2)

li    t3, 4264
add   t3, t3, sp
lw    t1, 0(t3)
lw    t1, 0(t1)
li    t3, 4268
add   t3, t3, sp
sw    t1, 0(t3)

lw    t1, 8(sp)
li    t3, 900
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4272
add   t2, t2, sp
sw    t1, 0(t2)

li    t2, 4272
add   t2, t2, sp
lw    t1, 0(t2)
li    t3, 0
slli  t2, t3, 2
add   t1, t1, t2
li    t2, 4276
add   t2, t2, sp
sw    t1, 0(t2)

li    t1, 4332
add   t1, t1, sp
sw    a0, 0(t1)
li    t1, 4328
add   t1, t1, sp
sw    a1, 0(t1)
li    t1, 4324
add   t1, t1, sp
sw    a2, 0(t1)
li    t1, 4320
add   t1, t1, sp
sw    a3, 0(t1)
li    t1, 4316
add   t1, t1, sp
sw    a4, 0(t1)
li    t1, 4312
add   t1, t1, sp
sw    a5, 0(t1)
li    t1, 4308
add   t1, t1, sp
sw    a6, 0(t1)
li    t1, 4304
add   t1, t1, sp
sw    a7, 0(t1)
li    t1, 4172
add   t1, t1, sp
lw    a0, 0(t1)
li    t1, 4184
add   t1, t1, sp
lw    a1, 0(t1)
li    t1, 4200
add   t1, t1, sp
lw    a2, 0(t1)
li    t1, 4212
add   t1, t1, sp
lw    a3, 0(t1)
li    t1, 4224
add   t1, t1, sp
lw    a4, 0(t1)
li    t1, 4228
add   t1, t1, sp
lw    a5, 0(t1)
li    t1, 4240
add   t1, t1, sp
lw    a6, 0(t1)
li    t1, 4252
add   t1, t1, sp
lw    a7, 0(t1)
li    t3, 4268
add   t3, t3, sp
lw    t1, 0(t3)
sw    t1, 0(sp)
li    t3, 4276
add   t3, t3, sp
lw    t1, 0(t3)
sw    t1, 4(sp)
call  f2
li    t1, 4280
add   t1, t1, sp
sw    a0, 0(t1)
li    t1, 4304
add   t1, t1, sp
lw    a7, 0(t1)
li    t1, 4308
add   t1, t1, sp
lw    a6, 0(t1)
li    t1, 4312
add   t1, t1, sp
lw    a5, 0(t1)
li    t1, 4316
add   t1, t1, sp
lw    a4, 0(t1)
li    t1, 4320
add   t1, t1, sp
lw    a3, 0(t1)
li    t1, 4324
add   t1, t1, sp
lw    a2, 0(t1)
li    t1, 4328
add   t1, t1, sp
lw    a1, 0(t1)
li    t1, 4332
add   t1, t1, sp
lw    a0, 0(t1)

li    t2, 4164
add   t2, t2, sp
lw    t3, 0(t2)
li    t4, 4280
add   t4, t4, sp
lw    t2, 0(t4)
add   t1, t3, t2
li    t4, 4284
add   t4, t4, sp
sw    t1, 0(t4)

li    t2, 4284
add   t2, t2, sp
lw    t1, 0(t2)
li    t2, 4012
add   t2, t2, sp
lw    t2, 0(t2)
sw    t1, 0(t2)

li    t2, 4012
add   t2, t2, sp
lw    t1, 0(t2)
lw    t1, 0(t1)
li    t2, 4288
add   t2, t2, sp
sw    t1, 0(t2)

li    t1, 4332
add   t1, t1, sp
sw    a0, 0(t1)
li    t1, 4328
add   t1, t1, sp
sw    a1, 0(t1)
li    t1, 4324
add   t1, t1, sp
sw    a2, 0(t1)
li    t1, 4320
add   t1, t1, sp
sw    a3, 0(t1)
li    t1, 4316
add   t1, t1, sp
sw    a4, 0(t1)
li    t1, 4312
add   t1, t1, sp
sw    a5, 0(t1)
li    t1, 4308
add   t1, t1, sp
sw    a6, 0(t1)
li    t1, 4304
add   t1, t1, sp
sw    a7, 0(t1)
li    t1, 4288
add   t1, t1, sp
lw    a0, 0(t1)
call  putint
li    t1, 4304
add   t1, t1, sp
lw    a7, 0(t1)
li    t1, 4308
add   t1, t1, sp
lw    a6, 0(t1)
li    t1, 4312
add   t1, t1, sp
lw    a5, 0(t1)
li    t1, 4316
add   t1, t1, sp
lw    a4, 0(t1)
li    t1, 4320
add   t1, t1, sp
lw    a3, 0(t1)
li    t1, 4324
add   t1, t1, sp
lw    a2, 0(t1)
li    t1, 4328
add   t1, t1, sp
lw    a1, 0(t1)
li    t1, 4332
add   t1, t1, sp
lw    a0, 0(t1)

li    t1, 10
li    t2, 4292
add   t2, t2, sp
sw    t1, 0(t2)

li    t1, 4332
add   t1, t1, sp
sw    a0, 0(t1)
li    t1, 4328
add   t1, t1, sp
sw    a1, 0(t1)
li    t1, 4324
add   t1, t1, sp
sw    a2, 0(t1)
li    t1, 4320
add   t1, t1, sp
sw    a3, 0(t1)
li    t1, 4316
add   t1, t1, sp
sw    a4, 0(t1)
li    t1, 4312
add   t1, t1, sp
sw    a5, 0(t1)
li    t1, 4308
add   t1, t1, sp
sw    a6, 0(t1)
li    t1, 4304
add   t1, t1, sp
sw    a7, 0(t1)
li    t1, 4292
add   t1, t1, sp
lw    a0, 0(t1)
call  putch
li    t1, 4304
add   t1, t1, sp
lw    a7, 0(t1)
li    t1, 4308
add   t1, t1, sp
lw    a6, 0(t1)
li    t1, 4312
add   t1, t1, sp
lw    a5, 0(t1)
li    t1, 4316
add   t1, t1, sp
lw    a4, 0(t1)
li    t1, 4320
add   t1, t1, sp
lw    a3, 0(t1)
li    t1, 4324
add   t1, t1, sp
lw    a2, 0(t1)
li    t1, 4328
add   t1, t1, sp
lw    a1, 0(t1)
li    t1, 4332
add   t1, t1, sp
lw    a0, 0(t1)

li    a0, 0
li t1, 4412
add t1, sp, t1
lw ra, 0(t1)
li t1, 4416
add sp, sp, t1
ret

