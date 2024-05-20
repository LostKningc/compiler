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
void Visit(const koopa_raw_binary_t &binary);

int IRanalysis(std::string inputfile, std::string outputfile);