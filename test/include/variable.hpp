#pragma once
#ifndef VARIABLE_HPP
#define VARIABLE_HPP
#include <string>

class sym_node {
  public:
	std::string name;
	int value;
	sym_node *prev, *next;
};


int get_sym_val(sym_node* &sym_head,std::string name, int * value);
int set_sym_val(sym_node* &sym_head,sym_node* &sym_tail,std::string name, int value) ;

#endif  // VARIABLE_HPP