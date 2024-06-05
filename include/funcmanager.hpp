#pragma once
#ifndef FUNCMANAGER_HPP
#define FUNCMANAGER_HPP
#include <unordered_map>
#include "ast.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class FuncManager{
public:
    unordered_map<string, Btype> decl_func_table;
    vector<string> func_stack;

    void add_Func(string name, Btype type);
    Btype get_Functype(string name);
    void EnterStack(string name);
    void PopStack(int num);
    void printSysyDeclFunc();
};


#endif  // FUNCMANAGER_HPP