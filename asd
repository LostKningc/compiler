@__filed0__buf = global [2 x [100 x i32]] zeroinitializer

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @starttime()

declare void @stoptime()

define void @merge_sort(i32 %l, i32 %r) {
$entry:
  %j = alloca i32
  %k = alloca i32
  %i = alloca i32
  %$l = alloca i32
  %$and0 = alloca i32
  %mid = alloca i32
  %$0 = add i32 0, %l
  %$1 = add i32 %$0, 1
  %$2 = add i32 0, %r
  %$3 = icmp sge i32 %$1, %$2
  %$4 = zext i1 %$3 to i32
  %$5 = icmp ne i32 %$4, 0
  br i1 %$5, label %$then0, label %$merge0

$then0:
  ret void

$merge0:
  %$6 = add i32 0, %l
  %$7 = add i32 0, %r
  %$8 = add i32 %$6, %$7
  %$9 = sdiv i32 %$8, 2
  store i32 %$9, i32* %mid
  %$10 = add i32 0, %l
  %$11 = load i32, i32* %mid
  call void @merge_sort(i32 %$10, i32 %$11)
  %$12 = load i32, i32* %mid
  %$13 = add i32 0, %r
  call void @merge_sort(i32 %$12, i32 %$13)
  %$14 = add i32 0, %l
  store i32 %$14, i32* %i
  %$15 = load i32, i32* %mid
  store i32 %$15, i32* %j
  %$16 = add i32 0, %l
  store i32 %$16, i32* %k
  br label %$while_entry0

$while_entry0:
  %$17 = load i32, i32* %i
  %$18 = load i32, i32* %mid
  %$19 = icmp slt i32 %$17, %$18
  %$20 = zext i1 %$19 to i32
  %$21 = icmp eq i32 0, %$20
  %$22 = zext i1 %$21 to i32
  %$23 = icmp eq i32 0, %$22
  %$24 = zext i1 %$23 to i32
  store i32 %$24, i32* %$and0
  %$25 = icmp ne i32 %$24, 0
  br i1 %$25, label %$and1part0, label %$and2part0

$and1part0:
  %$26 = load i32, i32* %j
  %$27 = add i32 0, %r
  %$28 = icmp slt i32 %$26, %$27
  %$29 = zext i1 %$28 to i32
  %$30 = icmp eq i32 0, %$29
  %$31 = zext i1 %$30 to i32
  %$32 = icmp eq i32 0, %$31
  %$33 = zext i1 %$32 to i32
  %$34 = and i32 %$24, %$33
  store i32 %$34, i32* %$and0
  br label %$and2part0

$and2part0:
  %$35 = load i32, i32* %$and0
  %$36 = icmp ne i32 %$35, 0
  br i1 %$36, label %$while_body0, label %$while_end0

$while_body0:
  %$37 = load i32, i32* %i
  %$ptr0 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 0
  %$ptr1 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr0, i32 0, i32 %$37
  %$38 = load i32, i32* %$ptr1
  %$39 = load i32, i32* %j
  %$ptr2 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 0
  %$ptr3 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr2, i32 0, i32 %$39
  %$40 = load i32, i32* %$ptr3
  %$41 = icmp slt i32 %$38, %$40
  %$42 = zext i1 %$41 to i32
  %$43 = icmp ne i32 %$42, 0
  br i1 %$43, label %$then1, label %$else1

$while_end0:
  br label %$while_entry1

$then1:
  %$44 = load i32, i32* %k
  %$ptr4 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 1
  %$ptr5 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr4, i32 0, i32 %$44
  %$45 = load i32, i32* %i
  %$ptr6 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 0
  %$ptr7 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr6, i32 0, i32 %$45
  %$46 = load i32, i32* %$ptr7
  store i32 %$46, i32* %$ptr5
  %$47 = load i32, i32* %i
  %$48 = add i32 %$47, 1
  store i32 %$48, i32* %i
  br label %$merge1

$else1:
  %$49 = load i32, i32* %k
  %$ptr8 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 1
  %$ptr9 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr8, i32 0, i32 %$49
  %$50 = load i32, i32* %j
  %$ptr10 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 0
  %$ptr11 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr10, i32 0, i32 %$50
  %$51 = load i32, i32* %$ptr11
  store i32 %$51, i32* %$ptr9
  %$52 = load i32, i32* %j
  %$53 = add i32 %$52, 1
  store i32 %$53, i32* %j
  br label %$merge1

$while_entry1:
  %$54 = load i32, i32* %i
  %$55 = load i32, i32* %mid
  %$56 = icmp slt i32 %$54, %$55
  %$57 = zext i1 %$56 to i32
  %$58 = icmp ne i32 %$57, 0
  br i1 %$58, label %$while_body1, label %$while_end1

$merge1:
  %$59 = load i32, i32* %k
  %$60 = add i32 %$59, 1
  store i32 %$60, i32* %k
  br label %$while_entry0

$while_body1:
  %$61 = load i32, i32* %k
  %$ptr12 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 1
  %$ptr13 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr12, i32 0, i32 %$61
  %$62 = load i32, i32* %i
  %$ptr14 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 0
  %$ptr15 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr14, i32 0, i32 %$62
  %$63 = load i32, i32* %$ptr15
  store i32 %$63, i32* %$ptr13
  %$64 = load i32, i32* %i
  %$65 = add i32 %$64, 1
  store i32 %$65, i32* %i
  %$66 = load i32, i32* %k
  %$67 = add i32 %$66, 1
  store i32 %$67, i32* %k
  br label %$while_entry1

$while_end1:
  br label %$while_entry2

$while_entry2:
  %$68 = load i32, i32* %j
  %$69 = add i32 0, %r
  %$70 = icmp slt i32 %$68, %$69
  %$71 = zext i1 %$70 to i32
  %$72 = icmp ne i32 %$71, 0
  br i1 %$72, label %$while_body2, label %$while_end2

$while_body2:
  %$73 = load i32, i32* %k
  %$ptr16 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 1
  %$ptr17 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr16, i32 0, i32 %$73
  %$74 = load i32, i32* %j
  %$ptr18 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 0
  %$ptr19 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr18, i32 0, i32 %$74
  %$75 = load i32, i32* %$ptr19
  store i32 %$75, i32* %$ptr17
  %$76 = load i32, i32* %j
  %$77 = add i32 %$76, 1
  store i32 %$77, i32* %j
  %$78 = load i32, i32* %k
  %$79 = add i32 %$78, 1
  store i32 %$79, i32* %k
  br label %$while_entry2

$while_end2:
  br label %$while_entry3

$while_entry3:
  %$80 = add i32 0, %l
  %$81 = add i32 0, %r
  %$82 = icmp slt i32 %$80, %$81
  %$83 = zext i1 %$82 to i32
  %$84 = icmp ne i32 %$83, 0
  br i1 %$84, label %$while_body3, label %$while_end3

$while_body3:
  DEBUG(llvm::dbgs() << "This is debug message.")
  %$85 = add i32 0, %l
  %$ptr20 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 0
  %$ptr21 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr20, i32 0, i32 %$85
  %$86 = add i32 0, %l
  %$ptr22 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 1
  %$ptr23 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr22, i32 0, i32 %$86
  %$87 = load i32, i32* %$ptr23
  store i32 %$87, i32* %$ptr21
  store i32 %l, i32* %$l
  %$88 = load i32, i32* %$l
  %$89 = add i32 %$88, 1
  store i32 %$89, i32* %$l
  br label %$while_entry3

$while_end3:
  ret void
}

define i32 @main() {
$entry:
  %n = alloca i32
  %$ptr24 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 0
  %$90 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr24, i32 0, i32 0
  %$91 = call i32 @getarray(i32* %$90)
  store i32 %$91, i32* %n
  %$92 = add i32 0, 0
  %$93 = load i32, i32* %n
  call void @merge_sort(i32 %$92, i32 %$93)
  %$94 = load i32, i32* %n
  %$ptr25 = getelementptr inbounds [2 x [100 x i32]], [2 x [100 x i32]]* @__filed0__buf, i32 0, i32 0
  %$95 = getelementptr inbounds [100 x i32], [100 x i32]* %$ptr25, i32 0, i32 0
  call void @putarray(i32 %$94, i32* %$95)
  ret i32 0
}
