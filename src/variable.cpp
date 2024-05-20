#include"variable.hpp"

int get_sym_val(sym_node* &sym_head,std::string name, int * value) {
	sym_node* sym_cur = sym_head;
	while(sym_cur!=nullptr) {
		if(name==sym_cur->name)
			break;
		sym_cur = sym_cur->next;
	}

	if(sym_cur!=nullptr) {
		*value = sym_cur->value;
		return 1;
	} else
		return 0; 	
}

int set_sym_val(sym_node* &sym_head,sym_node* &sym_tail,std::string name, int value) {
	sym_node* sym_cur = sym_head;
	while(sym_cur!=nullptr) {
		if(sym_cur->name==name)
			break;
		sym_cur = sym_cur->next;
	}

	if(sym_cur!=nullptr)
		sym_cur->value = value;
	else {
		sym_cur = new sym_node();
		sym_cur->name=name;
		sym_cur->value = value;
		sym_cur->prev = nullptr;
		sym_cur->next = nullptr;
		
		if(sym_head == nullptr) {
			sym_head = sym_cur;
			sym_tail = sym_cur;
		} else {
			sym_tail->next = sym_cur;
			sym_cur->prev = sym_tail;
			sym_tail = sym_cur;
		}
	}

	return 1; 	
}