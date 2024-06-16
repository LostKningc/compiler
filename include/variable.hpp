#pragma once
#ifndef VARIABLE_HPP
#define VARIABLE_HPP
#include <string>
#include<unordered_map>
#include<vector>
#include"ast.hpp"


class Val_Info{
public:
	int value;//变量的值（对于常量，可直接取用）（对于变量，这个值用来区别参数与变量）
	bool const_var;//是否为常量
	//下两条属性用于数组
	bool array_const=false;//是否为数组常量
	int array_size=0;//数组大小
	Val_Info(int f,bool s):value(f),const_var(s){array_size=0;};
	Val_Info()=default;
	Val_Info(int f,bool s,bool a):value(f),const_var(s),array_const(a){array_size=0;};
	Val_Info(int f,bool s,bool a,int az):value(f),const_var(s),array_const(a),array_size(az){};
};


struct Val_Map{
	int field_idx;//当前符号表所处作用域序号
	std::unordered_map<std::string,Val_Info> val_map;//管理符号表用的hashmap
	std::vector<std::string> param_stack;//参数栈（函数调用的时候涉及）
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
		void EnterBlock();//会压入一张符号表，计数器加1
		void ExitBlock();//会弹出符号表
		const Val_Info& get(std::string name);//获取变量信息
		//将参数添加到作用域（定义函数阶段）
		void params2block();
		//添加参数(定义函数阶段)
		void add_Param(std::string name);//将参数添加到参数栈
		void add_Param(std::string name,int dimon);//将参数添加到参数栈
		void Record(std::string name,std::pair<int,bool> val);//将符号及其信息加入当前层的hashmap
		void Record(std::string name,int value,bool const_flag,bool array_const);//将符号及其信息加入当前层的hashmap
		void Record(std::string name,int value,bool const_flag,bool array_const,int array_size);//将符号及其信息加入当前层的hashmap
		std::string Get_Name(std::string prim_name);//加上前缀，定位到正确的变量
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