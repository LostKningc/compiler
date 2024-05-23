#pragma once
#ifndef VARIABLE_HPP
#define VARIABLE_HPP
#include <string>
#include<unordered_map>
#include<vector>

struct Val_Map{
	int field_idx;
	std::unordered_map<std::string,std::pair<int,bool>> val_map;
	Val_Map()=default;
	Val_Map(int idx):field_idx(idx){}
};

class Val_Table{
	private:
		int map_counter;
	public:
		std::vector<Val_Map> t_stack;
		Val_Table();
		void EnterBlock();
		void ExitBlock();
		const std::pair<int,bool>& get(std::string name);
		void Record(std::string name,std::pair<int,bool> val);
		std::string Get_Name(std::string prim_name);
};

class sym_node {
  public:
	std::string name;
	int value;
	sym_node *prev, *next;
};



#endif  // VARIABLE_HPP