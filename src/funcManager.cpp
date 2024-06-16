#include"funcmanager.hpp"

void FuncManager::add_Func(string name, Btype type){
    decl_func_table[name] = type;
}

Btype FuncManager::get_Functype(string name){
    if(decl_func_table.find(name) != decl_func_table.end()){
        return decl_func_table[name];
    }
    else{
        throw std::runtime_error("error: function \"" + name + "\" is not declared");
    }
}

void FuncManager::EnterStack(string name){
    func_stack.push_back(name);
}

void FuncManager::PopStack(int num){
    auto it = func_stack.end()-num;
    auto i=it;
    for(;i!=func_stack.end();i++){
        if(i!=it)
            std::cout<<",";
        std::cout<<*i;
    }
    func_stack.erase(it,func_stack.end());
}

void FuncManager::printSysyDeclFunc(){
    std::cout<<"decl @getint():i32"<<std::endl;
    add_Func("getint", Btype::BINT);
    std::cout<<"decl @getch():i32"<<std::endl;
    add_Func("getch",Btype::BINT);
    std::cout<<"decl @getarray(*i32):i32"<<std::endl;
    add_Func("getarray",Btype::BINT);
    std::cout<<"decl @putint(i32)"<<std::endl;
    add_Func("putint",Btype::BVOID);
    std::cout<<"decl @putch(i32)"<<std::endl;
    add_Func("putch",Btype::BVOID);
    std::cout<<"decl @putarray(i32,*i32)"<<std::endl;
    add_Func("putarray",Btype::BVOID);
    std::cout<<"decl @starttime()"<<std::endl;
    add_Func("starttime",Btype::BVOID);
    std::cout<<"decl @stoptime()"<<std::endl;
    add_Func("stoptime",Btype::BVOID);

    std::cout<<std::endl;
}
