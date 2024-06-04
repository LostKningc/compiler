#pragma once
#ifndef VARIABLE_HPP
#define VARIABLE_HPP
#include <string>
#include<unordered_map>
#include<vector>
#include"ast.hpp"


class Val_Info{
public:
	int first;
	bool second;
	bool array_const=false;
	int array_size=0;
	Val_Info(int f,bool s):first(f),second(s){array_size=0;};
	Val_Info()=default;
	Val_Info(int f,bool s,bool a):first(f),second(s),array_const(a){array_size=0;};
	Val_Info(int f,bool s,bool a,int az):first(f),second(s),array_const(a),array_size(az){};
};


struct Val_Map{
	int field_idx;
	std::unordered_map<std::string,Val_Info> val_map;
	std::vector<std::string> param_stack;
	Val_Map()=default;
	Val_Map(int idx):field_idx(idx){}
};

class Param_Info{
public:
	std::string name;
	int dimon_size;
	Param_Info(std::string n,int d):name(n),dimon_size(d){};
	Param_Info()=default;
};

class Val_Table{
	private:
		int map_counter;
	public:
		std::vector<Val_Map> t_stack;
		std::vector<Param_Info> params_tmp;
		Val_Table();
		void EnterBlock();
		void ExitBlock();
		const Val_Info& get(std::string name);
		//将参数添加到作用域（定义函数阶段）
		void params2block();
		//添加参数(定义函数阶段)
		void add_Param(std::string name);
		void add_Param(std::string name,int dimon);
		void Record(std::string name,std::pair<int,bool> val);
		void Record(std::string name,int value,bool const_flag,bool array_const);
		void Record(std::string name,int value,bool const_flag,bool array_const,int array_size);
		std::string Get_Name(std::string prim_name);
		void valuePlus1(std::string name);
		int get_field_idx();
};

class ArrayInfo{
public:

	std::vector<int> array_dimon;
	std::vector<std::string> larray_dimon;
	std::string name="";
	int filled_sum=0;
	Btype type;
	bool const_flag=false;

	ArrayInfo(std::string n,Btype t):name(n),type(t){};
	ArrayInfo(std::string n,Btype t,bool c):name(n),type(t),const_flag(c){};
};

class ArrayManager{
	private:
		int ptr_counter=0;
	public:
	// std::vector<int> array_dimon;
	// std::vector<std::string> larray_dimon;
	// int filled_sum=0;
	// bool const_flag=false;
	// std::string name;
	// Btype type;
	std::vector<ArrayInfo> array_stack;
	
	std::vector<std::string> ConstParseArray(const std::unique_ptr<BaseAST> &ast, int depth = 0); 
	std::vector<std::string> VarParseArray(const std::unique_ptr<BaseAST> & ast, int depth = 0);
	//TODO:需要实现
	std::string formatArray(const std::vector<std::string>& data, const std::vector <int>& array_dim, int depth, int& index);
	void printArray(const std::vector<std::string> &data);
	void addArray(const std::unique_ptr<BaseAST> &arraydef );
	std::string generateArrayType(int depth = 0);
	std::string generateAllocStatement(const std::string& var_name);
	void addLArray(const std::unique_ptr<BaseAST> &arraydef);
	void addParamArray(const std::unique_ptr<BaseAST> &arraydef);
	//要给管理器的数组的类型
	void InitializeManager(Btype ntype);
	void InitializeManager(Btype ntype,bool const_f);
	void KillManager();

	void LArrayLoad();
	void ParamArrayLoad();
	std::string get_current_ptr();
	std::string get_name();
	bool get_const_flag();
	Btype get_type();
	const std::vector<int>& get_dimon();
	const std::vector<std::string>& get_ldimon();
	int get_filled_sum();
	void Plus1FilledSum();
};

void printType(Btype type);
#endif  // VARIABLE_HPP