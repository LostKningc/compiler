#include"variable.hpp"
#include<iostream>

void Val_Table::EnterBlock(){
	map_counter++;
	t_stack.push_back(Val_Map(map_counter));
}

void Val_Table::ExitBlock(){
	t_stack.pop_back();
}

const std::pair<int,bool>& Val_Table::get(std::string name) {
	auto beg=t_stack.rbegin(),end=t_stack.rend();
	for(auto it=beg;it!=end;++it){
		auto& table=*it;
		auto val=table.val_map.find(name);
		if(val!=table.val_map.end())return val->second;
	}
	throw std::runtime_error("error: symbol \"" + name + "\" is not declared");
}

void Val_Table::Record(std::string name,std::pair<int,bool> val){
	t_stack.back().val_map[name]=val;
}

Val_Table::Val_Table(){
	map_counter=0;
	t_stack.push_back(Val_Map(map_counter));
}

std::string Val_Table::Get_Name(std::string prim_name){
	auto beg=t_stack.rbegin(),end=t_stack.rend();
	for(auto it=beg;it!=end;++it){
		auto& table=*it;
		auto val=table.val_map.find(prim_name);
		if(val!=table.val_map.end())return "__filed"+std::to_string(table.field_idx)+"__"+prim_name;
	}
	throw std::runtime_error("error: symbol \"" + prim_name + "\" is not declared");
}