#pragma once
#include "koopa.h"
#include <string>
#include <iostream>
#include <cassert>
#include <map>
#include <stack>
#include <iomanip> // for std::setw
void Visit(const koopa_raw_program_t &program);
void Visit(const koopa_raw_slice_t &slice);
void Visit(const koopa_raw_function_t &func);
void Visit(const koopa_raw_basic_block_t &bb);
void Visit(const koopa_raw_value_t &value);
void Visit(const koopa_raw_return_t &ret);
std::string Visit(const koopa_raw_integer_t &integer); //from void to string
void Visit(const koopa_raw_binary_t &binary, const koopa_raw_value_t &value,const uint32_t use_count);
void Visit(const koopa_raw_store_t &store);
void Visit(const koopa_raw_load_t &load , const koopa_raw_value_t &value);
void Visit(const koopa_raw_branch_t &branch);
void Visit(const koopa_raw_jump_t &jump);

int IRanalysis(std::string inputfile, std::string outputfile);