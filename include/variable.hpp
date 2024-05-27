#pragma once
#ifndef VARIABLE_HPP
#define VARIABLE_HPP
#include <string>
#include<unordered_map>
#include<vector>
#include"ast.hpp"

struct Val_Map{
	int field_idx;
	std::unordered_map<std::string,std::pair<int,bool>> val_map;
	std::vector<std::string> param_stack;
	Val_Map()=default;
	Val_Map(int idx):field_idx(idx){}
};

class Val_Table{
	private:
		int map_counter;
	public:
		std::vector<Val_Map> t_stack;
		std::vector<std::string> params_tmp;
		Val_Table();
		void EnterBlock();
		void ExitBlock();
		const std::pair<int,bool>& get(std::string name);
		//将参数添加到作用域（定义函数阶段）
		void params2block();
		//添加参数(定义函数阶段)
		void add_Param(std::string name);
		void Record(std::string name,std::pair<int,bool> val);
		std::string Get_Name(std::string prim_name);
		void valuePlus1(std::string name);
		int get_field_idx();
};

class sym_node {
  public:
	std::string name;
	int value;
	sym_node *prev, *next;
};


void printType(Btype type);
#endif  // VARIABLE_HPP