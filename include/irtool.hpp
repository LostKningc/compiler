#pragma once
#ifndef _IRTOOL_HPP
#define _IRTOOL_HPP

#include "koopa.h"

void strir2asm(const char *str); 


//访问结构中的各处细节
void Visit(const koopa_raw_slice_t &slice);
//访问函数
void Visit(const koopa_raw_function_t &func);
//访问基本块
void Visit(const koopa_raw_basic_block_t &bb);
//访问值
void Visit(const koopa_raw_value_t &value);
//访问指令
void Visit(const koopa_raw_value_t &value);


//指令细节
//返回指令处理
void Visit(const koopa_raw_return_t
&ret);
//整数指令处理
void Visit(const koopa_raw_integer_t &integer);

#endif