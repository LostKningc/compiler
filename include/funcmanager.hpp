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
    vector<bool> param_flag; 

    FuncManager(){
        param_flag.push_back(false);
    }
    void add_Func(string name, Btype type);
    Btype get_Functype(string name);
    void EnterStack(string name);
    void PopStack(int num);
    void printSysyDeclFunc();
    void startCall(){
        param_flag.push_back(true);
    }
    void endCall(){
        param_flag.pop_back();
    }

    bool isParam(){
        return param_flag.back();
    }
    
};


#endif  // FUNCMANAGER_HPP