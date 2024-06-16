#pragma once
#include "koopa.h"
#include <string>
#include <iostream>
#include <cassert>
#include <map>
#include <stack>
#include <iomanip> // for std::setw
#include <list>
void Visit(const koopa_raw_program_t &program);
void Visit(const koopa_raw_slice_t &slice);
void Visit(const koopa_raw_function_t &func);
void Visit(const koopa_raw_basic_block_t &bb);
void Visit(const koopa_raw_value_t &value);
void Visit(const koopa_raw_return_t &ret);
std::string Visit(const koopa_raw_integer_t &integer); // from void to string
void Visit(const koopa_raw_binary_t &binary, const koopa_raw_value_t &value, const uint32_t use_count);
void Visit(const koopa_raw_store_t &store);
void Visit(const koopa_raw_load_t &load, const koopa_raw_value_t &value);
void Visit(const koopa_raw_branch_t &branch);
void Visit(const koopa_raw_jump_t &jump);
void Visit(const koopa_raw_call_t &call, const koopa_raw_value_t &value);
void Visit(const koopa_raw_global_alloc_t &global_alloc, const koopa_raw_value_t &value);
void Visit(const koopa_raw_get_elem_ptr_t &get_elem_ptr, const koopa_raw_value_t &value);
void Visit(const koopa_raw_get_ptr_t &get_ptr, const koopa_raw_value_t &value);
void save_regs(std::string reg);
void restore_regs(std::string reg);
int cal_array_length(const koopa_raw_type_kind &value);
void analysis_aggregate(const koopa_raw_aggregate_t &aggregate, std::list<int32_t> &init_list );
void store_array(const koopa_raw_value_t &value, int offset);
int IRanalysis(std::string inputfile, std::string outputfile);